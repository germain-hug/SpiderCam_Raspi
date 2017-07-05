#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/Float32.h>
//#include <Esp8266Hardware.h>
#include <std_msgs/String.h>

#include <ax12.h>
#include <BioloidController.h>

// Motor Driver - Baud Rate 1Mbps
BioloidController bioloid = BioloidController(1000000);

// ROS Handle
ros::NodeHandle nh;

// Callback function
void callback( const std_msgs::Float32& vel){
      // vel : Velocity Value (must be between 0 and 1023)
      // dir : 0 for Clockwise | 1 for CounterClockwise
      int dir = 0;
      ax12SetRegister2(1, AX_GOAL_SPEED_L, (int(vel.data)&0x03FF) | (dir<<10));
}

ros::Subscriber<std_msgs::Float32> sub("cmd_vel_approved", &callback );

void setup(){

    // Initialize Serial Connection for feedback
    Serial.begin(9600);

    // Set motor to Wheel Mode
    ax12SetRegister2(1,AX_CW_ANGLE_LIMIT_L,0);
    delay(33);
    ax12SetRegister2(1,AX_CCW_ANGLE_LIMIT_L,0);
    delay(33);
  
    // Speed at startup is zero
    ax12SetRegister2(1, AX_GOAL_SPEED_L, 0);

    // Initialize ROS Subscriber
    nh.getHardware()->setBaud(1000000);
    nh.initNode();
    nh.subscribe(sub);
}

void loop(){
   nh.spinOnce();
   delay(1);
}

