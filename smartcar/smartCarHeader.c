#ifndef test1_H_
#define test1_H_
#include "Arduino.h"
//add your includes for the project test1 here
#define f 0x09
#define b 0x06
#define lu 0x0A
#define ru 0x05
#define l 0x01
#define r 0x08
#define s 0x00
 
//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif
//add your function definitions for the project test1 here
void mm(int da);
void mc(char da, unsigned int ocv);
//Do not add code below this line
#endif /* test1_H_ */