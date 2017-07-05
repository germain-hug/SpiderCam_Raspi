#!/usr/bin/env python
import rospy
import json
from cmd_vel_controller.msg import cmd_vel_motors
from std_msgs.msg import Float32

"""
--------------------------------------------------
Performs a safety check on new velocity command,
transmits velocity to cmd_vel_controller node
--------------------------------------------------
"""

def callback(data, args):
	
	this_vel = 0
	
	pub = args[0]
	self_ID = args[1]

	# Retrieve 
	if(self_ID==1):
		this_vel = data.vel_1
	elif(self_ID==2):
		this_vel = data.vel_2
	elif(self_ID==3):
		this_vel = data.vel_3
	elif(self_ID==4):
		this_vel = data.vel_4

  	# TODO : SAFETY CHECKS (on position as well ?)	
	print(this_vel)
	pub.publish(this_vel)

def cmd_vel_publisher(self_ID):
	rospy.init_node('safety_check', anonymous=True)
	pub = rospy.Publisher('cmd_vel_approved', Float32, queue_size=10)
    	rospy.Subscriber('cmd_vel_out', cmd_vel_motors, callback, (pub, self_ID))
    	rospy.spin()

if __name__ == '__main__':
	with open('/home/pi/catkin_ws/specs.json') as data_file:    
    		data = json.load(data_file)
		self_ID = data["ID"]
		print("self_ID", self_ID)
	cmd_vel_publisher(self_ID)
