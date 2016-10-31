// Do not remove the include below
#include "Auto_Move.h"

char RX_buf[17];
unsigned char RX_buf2[7];
unsigned char TX_buf0[5]={0x76, 0x00, 0xAF, 0xE0, 0x8F};
unsigned char TX_bufs[5]={0x76, 0x00, 0x0F, 0x00, 0x0F};

int Motor[6]={22, 23, 24, 25, 4, 5};
int data = 0, flag=0;
int delay_time = 400, RX_flag = 1, Move_flag = 0;

int PWM_value1 = 120;
int PWM_value2 = 60;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
 int z;
 delay(1000);
 Serial1.begin(115200);
 Serial.begin(115200);
 for(z=0; z<6; z++){
  pinMode(Motor[z], OUTPUT);
  digitalWrite(Motor[z], LOW);
 }
 Serial1.write(TX_buf0, 5);
 Motor_Control('A', PWM_value2);
 Motor_mode(FORWARD);
 Move_flag = 1;
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
 /*if(flag){
  Motor_mode(STOP);
  Serial.println("Motor Stop");
  switch(data&0x63){
   case 0x01:
   case 0x02:
   case 0x03:
    Motor_Control('A', PWM_value1);
    Motor_mode(RIGHT_U);
    Serial.println("Motor RIGHT_U");
    delay(delay_time);
    break;
   case 0x20:
   case 0x40:
   case 0x60:
    Motor_Control('A', PWM_value1);
    Motor_mode(LEFT_U);
    Serial.println("Motor LEFT_U");
    delay(delay_time);
    break;
   default:
    Serial1.write(TX_bufs, 5);
       for(int i=0; i<5; i++)
        Serial.print(TX_bufs[i], HEX);
       Motor_mode(STOP);
       Serial.print("Motor Stop");
       flag = 0;
       Move_flag = 0;
       break;
  }
  Motor_mode(STOP);
  Serial1.write(TX_buf0, 5);
  Serial.println("Motor Stop");
  Motor_Control('A', PWM_value2);
  Motor_mode(FORWARD);
  Serial.println("Motor Forward");
  flag = 0;
 }*/
}

void serialEvent1(){
 /*unsigned char z, tmp=0;
 Serial1.readBytes(RX_buf, 17);
 if((RX_buf[0] == 0x76)&&(RX_buf[1] == 0)){
  if(Move_flag){
   for(z=2; z<16; z++)
    tmp += (unsigned char)RX_buf[z];
   tmp = tmp & 0xFF;
   if((unsigned char)RX_buf[16] == tmp){
    for(z=0; z<7; z++)
     RX_buf2[z] = (unsigned char)RX_buf[z+4];
    data = 0;
    for(z=0; z<7; z++){
     if(RX_buf2[z] < 30)
      data |= 0x01 << z;
    }
    if((data & 0x1C) != 0){
     if(RX_flag == 4){
      flag = 1;
      Serial1.write(TX_bufs, 5);
      RX_flag = 0;
     }
    }
    if(RX_flag != 4)
     RX_flag++;
   }
  }
 }
 else{
  for(z=1; z<17; z++){
   if(RX_buf[z] == 0x76){
    if(z!=16){
     if(RX_buf[z+1] == 0){
      tmp = z;
      break;
     }
    }
    else
     tmp = z;
   }
  }
  Serial1.readBytes(RX_buf, tmp);
 }*/
}

void serialEvent(){
 int i;
 unsigned char da = Serial.read();
 switch(da){
  case 't':
   Serial1.write(TX_buf0, 5);
   for(i=0; i<5; i++)
    Serial.print(TX_buf0[i], HEX);
   Motor_Control('A', PWM_value2);
   Motor_mode(FORWARD);
   Serial.print("Motor Forward");
   Move_flag = 1;
   da = 'x';
   break;
  case 's':
    // delay(delay_time);
   Serial1.write(TX_bufs, 5);
   for(i=0; i<5; i++)
    Serial.print(TX_bufs[i], HEX);
   Motor_mode(STOP);
   Serial.print("Motor Stop");
   flag = 0;
   Move_flag = 0;
   da = 'x';
   break;

  case 'h':
     delay(delay_time);
   Serial1.write(TX_buf0, 5);
   for(i=0; i<5; i++)
    Serial.print(TX_buf0[i], HEX);
   Motor_Control('A', PWM_value2);
   Motor_mode(FORWARD);
   Serial.print("Motor Forward");
   Move_flag = 1;
   da = 'x';
   break;
  case 'v':
     delay(delay_time);
   Motor_Control('A', PWM_value1);
   Motor_mode(LEFT_U);
   Serial.println("Motor LEFT_U");
   delay(delay_time);
   da = 'x';
   break;
  case 'n':
     delay(delay_time);
   Motor_Control('A', PWM_value1);
   Motor_mode(RIGHT_U);
   Serial.println("Motor RIGHT_U");
   delay(delay_time);
   da = 'x';
   break;
 }
 Serial.print("\n\r");
}

void Motor_mode(int da){
 int z;
 for(z=0; z<4; z++)
  digitalWrite(Motor[z], (da>>z) & 0x01);
}

void Motor_Control(char da, unsigned int OC_value){
 switch(da){
  case 'L':
   analogWrite(Motor[4], OC_value);
   break;
  case 'R':
   analogWrite(Motor[5], OC_value);
   break;
  case 'A':
   analogWrite(Motor[4], OC_value);
   analogWrite(Motor[5], OC_value);
   break;
 }
}