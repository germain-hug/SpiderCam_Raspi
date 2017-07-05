from pypose.driver import Driver
import time

driver = Driver(port='/dev/ttyUSB0', baud=38400, verbose=True)

# Import AX-12 register constants
from pypose.ax12 import *

# Get "moving" register for servo with ID 1
print(driver.getReg(1,36,1))

# Set the "moving speed" register for servo with ID 1
speed = 888 # A number between 0 and 1023
driver.setReg(1, 6, [0%256,0>>8])
time.sleep(0.033)
driver.setReg(1, 8, [0%256,0>>8])
time.sleep(0.033)
driver.setReg(1, P_GOAL_SPEED_L, [speed%256, speed>>8])
time.sleep(0.033)
