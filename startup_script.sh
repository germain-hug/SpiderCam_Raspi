#! /bin/sh
echo "Exporting ROS_MASTER_URI"
export ROS_MASTER_URI=http://hugo-MacBookPro:11311/

#echo "Sourcing ROS"
#source /opt/ros/kinetic/setup.bash
#source /home/pi/catkin_ws/devel/setup.bash

echo "Git Pull from SpiderCam_Raspi"
cd /home/pi/catkin_ws/src && git pull origin master

