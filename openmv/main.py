import time, random
from pyb import SPI
from machine import LED, Pin

def SPI_init():
    # Initialize the SPI bus
    spi = SPI(2)
    spi.init(SPI.SLAVE, baudrate=24000000, polarity=0, phase=0, bits=8)
    return spi


# Main function
def main():
    spi = SPI_init()
    cs = Pin("P3", Pin.IN, Pin.PULL_UP)
    led = LED("LED_BLUE")
    led1 = LED("LED_RED")
    buf_8 = bytearray(1)
    send_buf = bytearray(1)
    send_buf[0] = random.randint(0, 65)
    while True:
        send_buf[0] = 33
        if cs.value() == 0:
            try:
                led.value(1)
                spi.send_recv(send_buf, buf_8, timeout=1000)
                print("Data Sent camera_x(1)", buf_8[0])
                time.sleep_ms(50)
                send_buf[0] = 30
                spi.send_recv(send_buf, buf_8, timeout=1000)
                print("Data Sent camera_x(2)", buf_8[0])
                time.sleep_ms(100)

                send_buf[0] = 35
                spi.send_recv(send_buf, buf_8, timeout=1000)
                print("Data Sent camera_y(1)", buf_8[0])
                time.sleep_ms(20)
                send_buf[0] = 40
                spi.send_recv(send_buf, buf_8, timeout=1000)
                print("Data Sent camera_y(2)", buf_8[0])
                led.value(0)
                time.sleep_ms(20)
            except Exception as e:
                print("Error: ", e)
                led.value(0)


        else:
            # ML Continues #
            led1.value(1)
            time.sleep_ms(100)
            led1.value(0)


# Run the main function
main()
