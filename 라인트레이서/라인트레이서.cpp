#define CAR_DIR_FW 0
#define CAR_DIR_BK 1
#define CAR_DIR_LF 2
#define CAR_DIR_RF 3
#define CAR_DIR_ST 4
int g_carDirection = CAR_DIR_ST;
int g_carSpeed = 250;
int g_carSpeed1 = 200;
int x = 0;
//left motor
#define ENA 6
#define EN1 7
#define EN2 3
//right motor
#define EN3 4
#define EN4 2
#define ENB 5
void init_car_controller_board()
{
  pinMode(ENA, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
}
void car_forward()
{
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, g_carSpeed);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, g_carSpeed);
}
void car_backward()
{
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, g_carSpeed);
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, g_carSpeed);
}
void car_left()
{
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, g_carSpeed1);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, g_carSpeed);
}
void car_right()
{
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, g_carSpeed);
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, g_carSpeed1);
}
void car_stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void car_update()
{
  if(g_carDirection == CAR_DIR_FW)
  {  
    car_forward();
  }
  
  else if(g_carDirection == CAR_DIR_BK)
  {  
    car_backward();
  }
  
  else if(g_carDirection == CAR_DIR_LF)
  {  
    car_left();
  }
  
  else if(g_carDirection == CAR_DIR_RF)
  {  
    car_right();
  }
  
   else if(g_carDirection == CAR_DIR_ST)
  {  
    car_stop();
  }
}
void print_car_info()
{
  Serial.println("direction value"  + g_carDirection);
  Serial.println("speed pwn value"  + g_carSpeed);
}
#define LT_MODULE_L A0
#define LT_MODULE_F A1
#define LT_MODULE_R A2
void init_line_tracer_modules()
{
  pinMode(LT_MODULE_L, INPUT);
  pinMode(LT_MODULE_F, INPUT);
  pinMode(LT_MODULE_R, INPUT);
}
bool it_isLeft()
{
  int ret = digitalRead(LT_MODULE_L);
  return ret == 1 ? true : false;
}
bool it_isForward()
{
  int ret = digitalRead(LT_MODULE_F);
  return ret == 1 ? true : false;
}
bool it_isRight()
{
  int ret = digitalRead(LT_MODULE_R);
  return ret == 1 ? true : false;
}
void it_mode_update()
{
  int ll = it_isLeft();
  int ff = it_isForward();
  int rr = it_isRight();
  
  if(ll&&ff&&rr)
  {
    x++;
    if(x % 2 == 0)
    {
      g_carDirection = CAR_DIR_LF;
    }
    
    else if(x % 2 == 1)
    {
      g_carDirection = CAR_DIR_RF;
    }
  }
  
  else if(!ll&&!ff&&!rr)
  {
    g_carDirection = CAR_DIR_BK;
  }
  
  else if(ll)
  {
    g_carDirection = CAR_DIR_LF;
  }
  
  else if(ll&&ff)
  {
    g_carDirection = CAR_DIR_LF;
  }
  
  else if(rr)
  {
    g_carDirection = CAR_DIR_RF;
  }
  
  else if(rr&&ff)
  {
    g_carDirection = CAR_DIR_RF;
  }
  
  else if(ff)
  {
    g_carDirection = CAR_DIR_FW;
  }
}
void setup()
{
  Serial.begin(9600);
  init_car_controller_board();
  print_car_info();
}
void loop()
{
  car_update();
  it_mode_update();
} 