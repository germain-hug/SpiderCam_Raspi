#! /bin/sh

#echo "---- Exporting ROS_MASTER_URI ----"
export ROS_MASTER_URI=http://hugo-MacBookPro:11311/
#export ROS_MASTER_URI=http://172.20.10.2:11311
#export ROS_HOSTNAME=172.20.10.2
=======
#nb : change /etc/environment as well 

echo  "---------------------------------------"
echo  "---- Git Pull from SpiderCam_Raspi ----"
echo  "---------------------------------------"
echo " "
cd /home/pi/catkin_ws/src && git pull origin master
echo " "
echo "----------------------------------"
echo "---- Uploading Arduino Sketch ----"
echo "----------------------------------"
echo " "
cd /home/pi/catkin_ws/src/arduino_sketch && arduino --upload ax-12w_driver/ax-12w_driver.ino
echo " "
echo "------------------------------"
echo "---- Starting Safety Node ----"
echo "------------------------------"
echo " "
rosrun cmd_vel_controller safety_check.py &
sleep 5
echo " Done "
echo " "
echo "----------------------------"
echo "---- Starting Rosserial ----"
echo "----------------------------"
echo " "
rosrun rosserial_python serial_node.py /dev/ttyUSB0 _baud:=1000000
sleep 15
