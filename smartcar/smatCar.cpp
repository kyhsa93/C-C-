#include "test1.h"
char rxb[17];
unsigned char rxb2[7];
unsigned char txb0[5] = {0x76, 0x00, 0xAF, 0xE0, 0x8F};
unsigned char txbs[5] = {0x76, 0x00, 0x0F, 0x00, 0x0F};
int m[6] = {22,23,24,25,4,5};
int data = 0, flag = 0;
int dt = 400, rxf = 1, mf = 0;
int pwmv1 = 120;
int pwmv2 = 60;
//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
 int z;
 delay(1000);
 Serial1.begin(115200);
 Serial.begin(115200);
 Serial3.begin(115200);
 for(z=0; z<6; z++){
  pinMode(m[z], OUTPUT);
  digitalWrite(m[z], LOW);
 }
 Serial1.write(txb0,5);
 mc('A', pwmv2);
 mm(f);
 mf = 1;
}
// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
 if(flag)
 {
  mm(s);
  Serial.println("Stop!");
  switch(data & 0x63)
  {
   case 0x01:
   case 0x02:
   case 0x03:
    mc('A', pwmv1);
    mm(ru);
    Serial.println("Right!");
    delay(dt);
    Serial3.write('r');
    break;
   case 0x20:
   case 0x40:
   case 0x60:
    mc('A', pwmv1);
    mm(lu);
    Serial.println("Left!");
    delay(dt);
    Serial3.write('l');
    break;
   default:
    mc('A', pwmv1);
    mm(lu);
    Serial.println("Left!");
    delay(dt);
    Serial3.write('l');
    break;
  }
  mm(s);
  Serial1.write(txb0, 5);
  Serial.println("Stop!");
  delay(dt);
  Serial3.write('s');
  mc('A', pwmv2);
  mm(f);
  Serial.println("Forward!");
  delay(dt);
  Serial3.write('f');
  flag = 0;
 }
}
void serialEvent1()
{
 unsigned char z, tmp=0;
 Serial1.readBytes(rxb, 17);
 if((rxb[0] == 0x76) && (rxb[1] == 0))
 {
  if(mf)
  {
   for(z=2; z<16; z++)
    tmp += (unsigned char)rxb[z];
   tmp = tmp & 0xFF;
   if((unsigned char)rxb[16] == tmp)
   {
    for (z=0; z<7; z++)
     rxb2[z] = (unsigned char)rxb[z+4];
    data = 0;
    for (z=0; z<7; z++)
    {
     if(rxb2[z] < 40)
      data |= 0x01 << z;
    }
    if ((data & 0x1C) != 0)
    {
     if(rxf ==4)
     {
      flag = 1;
      Serial1.write(txbs, 5);
      rxf = 0;
     }
    }
    if(rxf != 4)
    {
     rxf++;
     }
    }
   }
  }
 else
 {
  for(z=1; z<17; z++)
  {
   if(rxb[z] == 0x76)
   {
    if(z!= 16)
    {
     if(rxb[z+1] == 0)
     {
      tmp = z;
      break;
     }
    }
    else {
     tmp = z;
    }
   }
  }
  Serial1.readBytes(rxb, tmp);
 }
}
void serialEvent()
{
 int i;
 unsigned char da= Serial.read();
 Serial.write(da);
 Serial3.write(da);
 switch(da)
 {
  case 't' :
   Serial1.write(txb0, 5);
   for(i=0; i<5; i++)
    Serial.print(txb0[i], HEX);
   mc('A', pwmv2);
   mm(f);
   Serial.print("Forward!");
   mf = 1;
   Serial.write('t');
   break;
  case 's' :
   Serial1.write(txbs, 5);
   for(i=0; i<5; i++)
    Serial.print(txbs[i], HEX);
   mm(s);
   Serial.print("Stop!");
   flag = 0;
   mf = 0;
   Serial.write('s');
   break;

  case 'y' :
   mc('A', pwmv1);
   mm(ru);
   Serial.println("Right!");
   delay(dt);
   Serial3.write('n');
   break;
  case 'r' :
   mc('A', pwmv1);
   mm(lu);
   Serial.println("Left!");
   delay(dt);
   Serial3.write('v');
   break;

  case 'c' :
   mc('A', pwmv1);
   mm(ru);
   Serial.println("Right!");
   delay(dt);
   break;
  case 'z' :
   mc('A', pwmv1);
   mm(lu);
   Serial.println("Left!");
   delay(dt);
   break;
  case 'd' :
   mc('A', pwmv2);
   mm(f);
   Serial.println("Forward!");
   delay(dt);
   break;

 }
 Serial.print("\n\r");
}
void mm(int da)
{
 int z;
 for(z=0; z<4; z++)
  digitalWrite(m[z], (da>>z)&0x01);
}
void mc(char da, unsigned int ocv)
{
 switch(da)
 {
 case'L':
  analogWrite(m[4], ocv);
  break;
 case'R':
  analogWrite(m[5], ocv);
  break;
 case'A':
  analogWrite(m[4], ocv);
  analogWrite(m[5], ocv);
  break;
 }
}




