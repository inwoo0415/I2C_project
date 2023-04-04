#include <Wire.h>
#include <MsTimer2.h>



#define SLAVE 4   // 슬레이브 주소
#define start_chack   4

volatile int stm1 = 0;
volatile int stm2 = 0;
volatile int stm3 = 0;
volatile int stm4 = 0;

volatile int rfm1 = 1 ;
volatile int rfm2 = 2 ;
volatile int rfm3 = 4 ;
volatile int rfm4 = 8 ;

int flag = 0;



void setup()
{
  Wire.begin(); 
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  MsTimer2::set(1, onTimer);   //1.25
  MsTimer2::start(); 
}


void onTimer()
{
  digitalWrite(start_chack, HIGH);
  flag = 1;
  digitalWrite(start_chack, LOW);
   
}

void loop()
{
  if(flag ==1)
  {
  Wire.requestFrom(SLAVE, 4);
  stm1 = Wire.read();
  stm2 = Wire.read();
  stm3 = Wire.read();
  stm4 = Wire.read();
  Wire.beginTransmission(SLAVE);
  Wire.write(rfm1);
  Wire.write(rfm2);
  Wire.write(rfm3);
  Wire.write(rfm4);
  Wire.endTransmission();
  Serial.println(stm1);
  Serial.println(stm2);
  flag =0;
  }
}
