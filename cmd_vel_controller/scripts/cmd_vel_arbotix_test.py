from pypose.driver import Driver

driver = Driver(port='/dev/ttyUSB0', verbose=True)

# Import AX-12 register constants
from pypose.ax12 import *

# Get "moving" register for servo with ID 1
is_moving = driver.getReg(1, P_MOVING, 1)
print(driver.getReg(1,P_PRESENT_TEMPERATURE,1))

# Set the "moving speed" register for servo with ID 1
speed = 888 # A number between 0 and 1023
driver.setReg(1, P_GOAL_SPEED_L, [speed%256, speed>>8])
