/***********************************************************************************
 *   ___________          ArbotiX Servo Scan -  All
 *  *|  /    \  |*
 *  *| |      | |*
 *  *|  \ __ /  |*
 *  *|          |*
 *  *|  AX-12A  |*
 *  *|          |*
 *  *|__________|*
 *
 *
 *  Code Functionality:    
 *    This code will scan the DYNAMIXEL chain for servo IDs in SERVO_LIST and then 
 *    return an array showing if the servo is present or not. Array[0] = SERVO_LIST[0], [1] = SERVO_LIST[2] ,etc
 *     -1 = no servo present
 *     0 = servo present with no error
 *      > 0 = servo present with error
 *    
 *  Physical Build / Instructions:
 *    Connect your servo(s) to the ArbotiX-M with a 3-pin cable. Power the ArbotiX-M
 *    with a 12v power supply (make sure each DYNAMIXEL blinks once when power
 *    is applied). The power jumper on the ArbotiX should be set to 'VIN'
 *    This Sketch will display data to the Serial() port. Open your Serial Monitor
 *    and set your baud rate to 9600
 *    
 * Compatible Servos:
 *    AX-12A / AX-12+
 *    AX-18A / AX-18F
 *    MX-28T / MX-28AT (previously known as RX-28M)
 *    MX-64T / MX-64AT
 *    MX-106T
 *
 *  Other Servos:   
 *    RX, EX and MX-R servos are code compatible but need additional circuitry to function
 *
 ********************************************************************************/

#include <ax12.h> //include the ArbotiX DYNAMIXEL library

const int NUMBER_OF_SERVOS = 3;
int servoReturnArray[NUMBER_OF_SERVOS];
const int SERVO_LIST[] = {3, 4 ,5};

void setup()
{
  dxlInit(1000000);  //start dynamixel library at 1mbps to communicate with the servos
  Serial.begin(9600); //start serial at 9600bps  
  dxlScanServos(NUMBER_OF_SERVOS,SERVO_LIST, servoReturnArray); //scan for all servos

  Serial.println("Servo ID : Error Bit");
  for(int i = 0; i<NUMBER_OF_SERVOS; i++)
  {
    if(servoReturnArray[i] > -1)
    {
      Serial.print(SERVO_LIST[i]); //array i = servo ID i + 1
      Serial.print(":");
      Serial.println(servoReturnArray[i]);
    }
    else
    {
      //no servo at this ID 
      Serial.print(SERVO_LIST[i]); //array i = servo ID i + 1
      Serial.print(":");
      Serial.println("No Servo Found");
    }
  }
}
void loop()
{
   
}



