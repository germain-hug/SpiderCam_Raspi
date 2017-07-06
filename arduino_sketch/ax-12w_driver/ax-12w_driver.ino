/*
----------------------------------
Generates motor velocity commands
----------------------------------
*/


#include <ArduinoHardware.h>
#include <ros.h>
#include <Esp8266Hardware.h>
#include <geometry_msgs/Point32.h>
#include <std_msgs/String.h>

#include "FS.h"

// Dynamixel + Arbotix Driver
#include <ax12.h>
#include <BioloidController.h>

// JSON Libraries
#include <ArduinoJson.h>

// Motor Driver - Baud Rate 1Mbps
BioloidController bioloid = BioloidController(1000000);

// ROS Handle
ros::NodeHandle nh;

// Callback function
void callback( const geometry_msgs::Point32& vel){
      // ---- Message Description ----
      // vel.x : Velocity Value (must be between 0 and 1023)
      // vel.y : 0 for Clockwise | 1 for CounterClockwise
      ax12SetRegister2(1, AX_GOAL_SPEED_L, (int(vel.x)&0x03FF) | (int(vel.y)<<10));    
      delay(33);

}

// Read ID from JSON file
char json[150];
File dataFile = FileSystem.open("/home/pi/catkin_ws/specs.json", FILE_READ);
dataFile.readBytes(json, size(json));
dataFile.close(); 
StaticJsonBuffer<JSON_OBJECT_SIZE(1)> jsonBuffer;
JsonObject& specs = jsonBuffer.parseObject(json);

// Initialize Subscriber
String topic_in = "cmd_vel_approved_" + specs["ID"];
ros::Subscriber<geometry_msgs::Point32> sub(topic_in, &callback );

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

