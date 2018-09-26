#include "MaxMatrix.h"
#include "Servo.h"
#include "ottoM.h"
#include "music.h"
#include "SR04.h"
#define NumMatrix 1
String inString = "";
int z;
SR04 sr04 = SR04(8,9);
ottoM otto;
void setup()
   {
   Serial.begin(115200);  //串口 蓝牙波特率
   otto.home(); //回原点程序
   delay(50);
   }
void loop() 
{
  char col;
  float distance;
  switch(z) 
   {
    case 0x02:
    otto.walk(1); //向前
    break;
    case 0x08:
    otto.walk(-1);//向后
    break;    
    case 0x06:
    otto.walk(2);//向左
    break; 
    case 0x07:
    otto.walk(-2);//向右
    break;   
    case 0x03:
    otto.home();//回原点
    break;  
    case 0x21:
    otto.leftHand();//左手运动
    break; 
    case 0x20:
    otto.rightHand();//右手运动
    break;    
    case 0x24:
    otto.home();
    int l;
    l=sizeof(elysiumtune)/sizeof(elysiumtune[0]);//歌曲字符数
    otto.music(elysiumaction,elysiumtune,elysiumduration,l); //唱歌，跳舞程序
    break;         
    }
  if(z==0x23)
  {   
      do
      {
      distance =sr04.Get()/58;
      otto.walk(1);
      while(Serial.available())
 {
      col = Serial.read();
  } 
      if(col==0x03)
  {
    break;
    }
      }
      while(distance>3);
//        otto.walk(-1);
        otto.walk(-1);
 //       Serial.print(distance);
        otto.home();
    }
  z=0;
  }
 void serialEvent()
{
  char sign;
  while(Serial.available())
{
  sign = Serial.read();
  } 
  z=sign;
// Serial.write(z);
//int l;
//l=sizeof(elysiumtune)/sizeof(elysiumtune[0]);
//otto.music(elysiumaction,elysiumtune,elysiumduration,l); 
}
