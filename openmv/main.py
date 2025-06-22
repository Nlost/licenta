import sensor
import time
import image
import pyb
from machine import LED

led = LED("LED_RED")

class spi_slave:
    def __init__(self, cs_pin="P3", clk_polarity=1, clk_phase=0, spi_bus=2):  # private
        import pyb
        self.__pin = pyb.Pin(cs_pin, pyb.Pin.IN)
        self.__polarity = clk_polarity
        self.__clk_phase = clk_phase
        self._put_short_timeout_reset = 50
        self.__spi = pyb.SPI(spi_bus)

    def put_bytes(self, data, timeout_ms):  # protected
        import pyb
        start = pyb.millis()
        while self.__pin.value():
            if pyb.elapsed_millis(start) >= self._put_short_timeout_reset:
                return
        self.__spi.init(pyb.SPI.SLAVE, polarity=self.__polarity, phase=self.__clk_phase)
        try:
            self.__spi.send(data, timeout=timeout_ms)
        except OSError:
            pass
        self.__spi.deinit()

# Initialize the sensor
sensor.reset()
sensor.set_contrast(3)
sensor.set_auto_gain(True)      # Enable automatic gain
sensor.set_auto_exposure(True)  # Enable automatic exposure
sensor.set_gainceiling(16)
sensor.set_framesize(sensor.VGA)
sensor.set_pixformat(sensor.GRAYSCALE)
face_cascade = image.HaarCascade("frontalface", stages=25)
clock = time.clock()

# SPI Slave interface
interface = spi_slave(cs_pin="P3", clk_polarity=1, clk_phase=0, spi_bus=2)

# Shared state
ready_to_send = False
send_buffer = bytearray(7)

# Interrupt sets the flag
def nss_callback(line):
    global ready_to_send
    ready_to_send = True

pyb.ExtInt(pyb.Pin("P3"), pyb.ExtInt.IRQ_FALLING, pyb.Pin.PULL_UP, nss_callback)

# Main loop
while True:
    clock.tick()
    img = sensor.snapshot()

    # Detect faces
    objects = img.find_features(face_cascade, threshold=0.75, scale_factor=1.25)
    for r in objects:
        img.draw_rectangle(r)

    # Example data packing based on face count
    num_faces = min(len(objects), 255)
    if(num_faces == 1): #Data frame
        led.toggle()
        x = objects[0][0]
        y = objects[0][1]
        h = objects[0][2]
        send_buffer[0] = 85 # Header byte
        send_buffer[1] = x & 0xFF
        send_buffer[2] = (x >> 8) & 0xFF
        send_buffer[3] = y & 0xFF
        send_buffer[4] = (y >> 8) & 0xFF
        send_buffer[5] = h & 0xFF
        send_buffer[6] = (h >> 8) & 0xFF
    else: #Error frame
        send_buffer[0] = 86  # Header byte
        send_buffer[1] = 0xAA
        send_buffer[2] = 0xFF  
        send_buffer[3] = 0x10
        send_buffer[4] = 0xAA
        send_buffer[5] = 0xFF
        send_buffer[6] = 0x10
    # SPI send logic (non-blocking during interrupt)
    if ready_to_send:
        try:
            interface.put_bytes(send_buffer, 1000)
        except Exception as e:
            continue
        ready_to_send = False
