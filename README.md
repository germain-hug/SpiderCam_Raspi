# SpiderCam_Raspi
Raspberry Pi Controls for the Arbotix-M & AX-12W Dynamixel ServoMotor
#### `arduino_sketch` : 
Arbotix Driver, receives velocity commands from ROS (`/cmd_vel_approved`)  
#### `cmd_vel_controller` : 
Receives main velocity commands (`/cmd_vel`), extracts correct velocity, applies safety checks and publishes to `/cmd_vel_approved`
