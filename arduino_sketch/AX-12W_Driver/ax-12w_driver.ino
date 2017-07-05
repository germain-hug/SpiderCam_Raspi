#include <ArduinoHardware.h>
#include <ros.h>
//#include <Esp8266Hardware.h>

// include the library itself
#include <ax12.h>
#include <BioloidController.h>

// now, create a connection called "bioloid" -- you should always call it bioloid
//  so that our macros work. Our baud rate is 1Mbps = 1000000
BioloidController bioloid = BioloidController(1000000);

void setup(){
    // this is a simple macro to move servo ID #1 to the center position (512)
    Serial.begin(1000000);

    // Set to Wheel Mode
    ax12SetRegister2(1,6,0);
    delay(33);
    ax12SetRegister2(1,8,0);
    delay(33);

    // Set goal speed
    int goal_speed = 800;
    ax12SetRegister2(1, 32, 0);
    delay(33);
    //Serial.print(ax12GetRegister(1,32,1));
    delay(1000);
    ax12SetRegister2(1, 32, 0);
    delay(10000);
}

void loop(){
    ax12SetRegister2(1, 32, 0);
    delay(80);
    ax12SetRegister2(1, 32, 0);
    delay(10000);
}
