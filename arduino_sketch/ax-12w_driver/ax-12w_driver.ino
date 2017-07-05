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
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<std_msgs::Float32> sub("cmd_vel_approved", &callback );
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

void setup(){

    // Initialize Serial Connection for feedback
    Serial.begin(9600);

    // Set motor to Wheel Mode
    ax12SetRegister2(1,AX_CW_ANGLE_LIMIT_L,0);
    delay(33);
    ax12SetRegister2(1,AX_CCW_ANGLE_LIMIT_L,0);
    delay(33);

    // Initialize ROS Subscriber
    nh.getHardware()->setBaud(1000000);
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(chatter);
}

void loop(){
   str_msg.data = "hello";
   chatter.publish( &str_msg );
   nh.spinOnce();
   delay(1000);
    /*
    ax12SetRegister2(1, AX_GOAL_SPEED_L, 0);
    delay(80);
    ax12SetRegister2(1, AX_GOAL_SPEED_L, 0);
    delay(10000);
    */
}

