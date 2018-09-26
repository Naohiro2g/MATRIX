# if ARDUINO >= 100
  #include "Arduino.h"
# else
  # include "WProgram.h"
# endif
#include "MaxMatrix.h"
#include "Servo.h"
#include "ottoM.h"
#define NumMatrix 1
int angleHL=0;
int angleHR=0;
MaxMatrix ledmatrix=MaxMatrix(PIN_DIN,PIN_CS,PIN_CLK, NumMatrix); //PIN  12=DIN, PIN 10=CS, PIN 11=CLK //点阵引脚设置
Servo HLservo;//左手电机设置
Servo HRservo;//右手电机设置
Servo LLservo;//左脚电机设置
Servo LRservo;//右脚电机设置
Servo FLservo;//左脚掌电机设置
Servo FRservo;//右脚掌机设置
void ottoM::home()  //回原点程序
{
  // put your setup code here, to run once:
  HLservo.attach(PIN_HL);
  HRservo.attach(PIN_HR);
  LLservo.attach(PIN_LL);
  LRservo.attach(PIN_LR);
  FLservo.attach(PIN_FL);
  FRservo.attach(PIN_FR);
  pinMode(BUZZER_PIN,OUTPUT);
  digitalWrite(BUZZER_PIN,LOW);
  for (char i=0; i< NumMatrix ; i++)
    {
       ledmatrix.init();
       ledmatrix.setIntensity(1);    // Poner el brillo a un valor intermedio
     }
   for (char i=0;i<8;i++)
    {
      ledmatrix.setColumn(i,B11111111);
      delay(100);
    }
    delay(50);
    ledmatrix.clearMatrix(); 
    HLservo.write(posHL);
    HRservo.write(posHR);
    delay(100);
    LLservo.write(posLL);
    LRservo.write(posLR);
    delay(100);
    FLservo.write(posFL);
    FRservo.write(posFR);
    delay(100);
  }
  void ottoM::action(char *b,unsigned int T) //电机动作
  {
    //HLservo.write(posHL+b[0]);
    //HRservo.write(posHR+b[1]);
    LLservo.write(posLL+b[0]);
    LRservo.write(posLR+b[1]);
    FLservo.write(posFL+b[2]); 
    FRservo.write(posFR+b[3]);
    delay(T);
    }
  void ottoM::leftHand()
  {   
    angleHL+=10;
    if(angleHL>=171)
      angleHL=0;
    HLservo.write(posHL+angleHL);         
  } 
  void ottoM::rightHand()
  {   
    angleHR+=10;
    if(angleHR>=181)
      angleHR=0;
    HRservo.write(posHR-angleHR);         
  }   
  void ottoM::walk(char i) //步行动作
  { 
    switch(i)
    {
      case 1://前
    mouth(forward_code);
    action(servoFB1_code,300);
    action(servoFB2_code,300);  
    action(servoFB3_code,300);     
    action(servoFB4_code,300);      
    break;
       case -1://后
    mouth(backward_code);
    action(servoFB1_code,300);
    action(servoFB4_code,300);  
    action(servoFB3_code,300);     
    action(servoFB2_code,300);    
    break;
    case 2:
    mouth(left_code);//左
    action(servoLR4_code,300);
    action(servoLR5_code,300);  
    action(servoLR3_code,300); 

    break;
    case -2:
    mouth(right_code);//右
    action(servoLR1_code,250);
    action(servoLR2_code,250);  
    action(servoLR3_code,250);  

    break;    
      }
    
   }
  
 void ottoM::mouth(char *a) //嘴巴表情
  { 
    char i=0;
    for(i=0;i<8;i++)
      ledmatrix.setColumn(i,a[i]);
  }

 void ottoM::music(char c[][6],int *tune,float *duration,int length) //音乐播放及动作
 {
  char i=0;
  char group;
  char col=0;
  for(int x=0;x<length;x++)
  {
   // Serial.begin(9600);
    tone(BUZZER_PIN,tune[x]);
    delay(500*duration[x]);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
    noTone(BUZZER_PIN);   
   //Serial.print(length);   
    if(x==elysiumjiepai[i])
    {
        HLservo.write(posHL+c[i][0]);
        HRservo.write(posHR+c[i][1]);
        LLservo.write(posLL+c[i][2]);
        LRservo.write(posLR+c[i][3]);
        FLservo.write(posFL+c[i][4]); 
        FRservo.write(posFR+c[i][5]);  
        i++;
    }   
     group=i%15;
     for(char m=0;m<8;m++)
    {
    ledmatrix.setColumn(m,musicmouth[group][m]);
    }
    delay(1);
    while(Serial.available())
 {
    col = Serial.read();
  } 
  if(col==0x03)
  {
    break;
    }
  }
  
}
void ottoM::TRY()
{
  for(char i=0;i<16;i++)
  {
 for(char m=0;m<8;m++)
    {
    ledmatrix.setColumn(m,musicmouth[i][m]);
    }
     delay(1000);
  }

}
  
