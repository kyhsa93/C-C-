// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section
 
#ifndef Auto_Move_H_
#define Auto_Move_H_
#include "Arduino.h"
//add your includes for the project Auto_Move here
 
#define FORWARD 0x09
#define BACKWARD 0x06
#define LEFT_U 0x0A
#define RIGHT_U 0x05
#define LEFT 0x01
#define RIGHT 0x08
#define STOP 0x00
 
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif
 
//add your function definitions for the project Auto_Move here
void Motor_mode(int da);
void Motor_Control(char da, unsigned int OC_value);
 
//Do not add code below this line
#endif /* Auto_Move_H_ */






