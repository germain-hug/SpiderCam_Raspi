#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32

"""
--------------------------------------------------
Operates on motor from approved velocity command
--------------------------------------------------
"""

def callback(data):
	print(data)
  	# TODO : write motor command

def cmd_vel_publisher():
    rospy.init_node('cmd_vel_publisher', anonymous=True)
    rospy.Subscriber('cmd_vel_approved', Float32, callback)
    rospy.spin()

if __name__ == '__main__':
	cmd_vel_publisher()
