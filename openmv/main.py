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
    while True:
        if cs.value() == 0:
            led.on()
            time.sleep(500)
            led.off()
            time.sleep(500)
        else:
            # ML Continues #
            led1.on()
            time.sleep(1000)
            led1.off()
            time.sleep(1000)

# Run the main function
main()
