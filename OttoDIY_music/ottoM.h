#ifndef ottoM_h
#define ottoM_h
# if ARDUINO >= 100
  #include "Arduino.h"
# else
  # include "WProgram.h"
# endif
#include "MaxMatrix1.h"
#include"music.h"
#define PIN_HL 6   //servo[0]
#define PIN_HR 7   //servo[1]
#define PIN_LL 2   //servo[2]
#define PIN_LR 3   //servo[3]
#define PIN_FL 4   //servo[4]
#define PIN_FR 5   //servo[5] 
#define forward 1
#define backward -1
#define left 2
#define right -2
//{0,0,-20,-20,-10,-40},{0,0,20,20,-10,-40},{0,0,20,20,40,10},{0,0,-20,-20,40,10}
//前进后退动作数组
const char servoFB1_code[]={0,0,-10,-40};
const char servoFB2_code[]={20,20,0,0};
const char servoFB3_code[]={0,0,40,10};
const char servoFB4_code[]={-20,-20,0,0};
//左右动作数组
const char servoLR1_code[]={0,0,-10,-40};
const char servoLR2_code[]={0,0,-10,0};
const char servoLR3_code[]={0,0,0,0};
const char servoLR4_code[]={0,0,40,10};
const char servoLR5_code[]={0,0,0,10};

 class ottoM{
  public:
      void home();
      void walk(char i);
      void mouth(char *a);
      void action(char *b,unsigned int T);
      void calabashbaby();
      void music(char c[][6],int *tune,float *duration,int length);     
      //void ottoM::musicaction0(char data0,unsigned int T); 
      //void ottoM::musicaction1(char data1,unsigned int T); 
      //void ottoM::musicaction2(char data2,unsigned int T); 
      //void ottoM::musicaction3(char data3,unsigned int T); 
      //void ottoM::musicaction4(char data4,unsigned int T); 
     //void ottoM::musicaction5(char data5,unsigned int T); 
      void ottoM::TRY();
      void ottoM::leftHand();
      void ottoM::rightHand();
  private:
       unsigned int posHL=10;
       unsigned int posHR=180;
       unsigned int posLL=82;
       unsigned int posLR=68;
       unsigned int posFL=70;
       unsigned int posFR=88;
      
  };
  # endif
