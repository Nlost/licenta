import time
from pyb import SPI
from machine import LED, Pin

def SPI_init():
    # Initialize the SPI bus
    spi = SPI(2, SPI.SLAVE, baudrate=24000000, polarity=0, phase=0)
    return spi


# Main function
def main():
    spi = SPI_init()
    cs = Pin("P3", Pin.IN, Pin.PULL_UP)
    led = LED("LED_BLUE")
    led1 = LED("LED_RED")
    buf_8 = bytearray(1)
    buf_16 = bytearray(2)
    while True:
        if cs.value() == 0:
            led.on()
            spi.recv(buf_8)
            if buf_8 == "A":
                spi.send(b'AB', timeout=300)
                spi.send(b'BB', timeout=300)
                spi.send(b'ZZ', timeout=300)
                spi.send(b'SS', timeout=300)
                spi.send(b'P', timeout=300)
            led.off()
        else:
            # ML Continues #
            led1.on()
            time.sleep(1000)
            led1.off()

# Run the main function
main()
