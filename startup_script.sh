#! /bin/sh
echo "Exporting ROS_MASTER_URI"
export ROS_MASTER_URI=http://hugo-MacBookPro:11311/

echo "Git Pull from SpiderCam_Raspi"
cd /home/pi/catkin_ws/src && git pull origin master

echo "Uploading Arduino Sketch"
cd /home/pi/catkin_ws/src/arduino_sketch && arduino --upload ax-12w_driver/ax-12w_driver.ino

echo "Starting Rosserial"
rosrun rosserial_python serial_node.py /dev/ttyUSB0 _baud:=1000000
sleep 15

echo "Starting Safety Node"
rosrun cmd_vel_controller safety_check.py
