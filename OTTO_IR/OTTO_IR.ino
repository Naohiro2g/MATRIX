//----------------------------------------------------------------
//-- Otto basic firmware v2 adapted from Zowi (ottobot.org)
//-- CC BY SA
//-- 04 December 2016
//-----------------------------------------------------------------
//-- Otto will avoid obstacles with this code!
//-----------------------------------------------------------------
#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
#include <motoIRremote.h>
decode_results   ir_results;
Otto Otto;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]
///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
//-- Movement parameters
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements
//---------------------------------------------------------

void IRkeyUnsetFunction( ) {  Serial.println("unknow!"); }

struct _Object {
   void (* functionPointer)()=IRkeyUnsetFunction;
 };

IRrecv ir_receiv(7);

String IR1keycode[17]={"ff4ab5","ff6897","ff9867","ffb04f","ff30cf","ff18e7","ff7a85","ff10ef","ff38c7","ff5aa5","ff52ad","ff42bd","ff629d","ff22dd","ff02fd","ffc23d","ffa857"};

struct _Object IR1key0, IR1key1, IR1key2, IR1key3, IR1key4, IR1key5, IR1key6, IR1key7, IR1key8, IR1key9, IR1key10;
struct _Object IR1key11, IR1key12, IR1key13, IR1key14, IR1key15, IR1key16, IR1key17, IR1key18, IR1key19, IR1key20, IR1key21;

void checkIRcode( ) {
  if(ir_receiv.decode(&ir_results))
  {
     String keycode = String(ir_results.value, HEX);
      Serial.print("keycode=");
      Serial.println(keycode);
      if(keycode == IR1keycode[0])
        IR1key0.functionPointer();
      else if(keycode == IR1keycode[1])
        IR1key1.functionPointer();
      else if(keycode == IR1keycode[2])
        IR1key2.functionPointer();
      else if(keycode == IR1keycode[3])
        IR1key3.functionPointer();
      else if(keycode == IR1keycode[4])
        IR1key4.functionPointer();
      else if(keycode == IR1keycode[5])
        IR1key5.functionPointer();
      else if(keycode == IR1keycode[6])
        IR1key6.functionPointer();
      else if(keycode == IR1keycode[7])
        IR1key7.functionPointer();
      else if(keycode == IR1keycode[8])
        IR1key8.functionPointer();
      else if(keycode == IR1keycode[9])
        IR1key9.functionPointer();
      else if(keycode == IR1keycode[10])
        IR1key10.functionPointer();
      else if(keycode == IR1keycode[11])
        IR1key11.functionPointer();
      else if(keycode == IR1keycode[12])
        IR1key12.functionPointer();
      else if(keycode == IR1keycode[13])
        IR1key13.functionPointer();
      else if(keycode == IR1keycode[14])
        IR1key14.functionPointer();
      else if(keycode == IR1keycode[15])
        IR1key15.functionPointer();
      else if(keycode == IR1keycode[16])
        IR1key16.functionPointer();
     ir_receiv.resume();
  }
}

void IR1key12Function( ) {
  Otto.walk(1,1000,1);//前進  //此行改成要按向上鍵時要執行的指令
}

void IR1key16Function( ) {
 Otto.walk(1,1000,-1);//後退   //此行改成要按向下鍵時要執行的指令
}

void IR1key13Function( ) {
  Otto.turn(1,1000,1);//左轉    //此行改成要按向左鍵時要執行的指令
}

void IR1key15Function( ) {
  Otto.turn(1,1000,-1);//右轉   //此行改成要按向右鍵時要執行的指令
}

void IR1key14Function( ) {
  Otto.home();//歸位   //此行改成要按OK鍵時要執行的指令
}

void IR1key1Function( ) {
  Otto.updown(1,1000,30);//大上升   //此行改成要按1鍵時要執行的指令
}

void IR1key2Function( ) {
 Otto.moonwalker(1,1000,30,1); //月球漫步向左走   //此行改成要按2鍵時要執行的指令
}

void IR1key3Function( ) {
  Otto.moonwalker(1,1000,30,-1);   //月球漫步向右走  //此行改成要按3鍵時要執行的指令
}

void IR1key4Function( ) {
  Otto.swing(1,1000,30);//搖擺    //此行改成要按4鍵時要執行的指令
}

void IR1key5Function( ) {
 Otto.flapping(1,1000,30,1);  //左撲  //此行改成要按5鍵時要執行的指令
}

void IR1key6Function( ) {
  Otto.flapping(1,1000,30,-1);    //此行改成要按6鍵時要執行的指令
}

void IR1key7Function( ) {
 Otto.tiptoeSwing(1,1000,30);  //墊腳尖  //此行改成要按7鍵時要執行的指令
}

void IR1key8Function( ) {
  Otto.bend(1,1000,1);   //向左彎曲 //此行改成要按8鍵時要執行的指令
}

void IR1key9Function( ) {
  Otto.bend(1,1000,-1);   //向右彎曲  //此行改成要按9鍵時要執行的指令
}

void IR1key0Function( ) {
 Otto.shakeLeg(1,1000,1);  //搖右腳  //此行改成要按0鍵時要執行的指令
}

void IR1key10Function( ) {
 Otto.shakeLeg(1,1000,-1);  //搖左腳  //此行改成要按*鍵時要執行的指令
}

void IR1key11Function( ) {
  Otto.jitter(1,1000,30);  //雙腳抖動  //此行改成要按#鍵時要執行的指令
}

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
 ir_receiv.enableIRIn();
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
 // Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
 // Otto.sing(S_happy); // a happy Otto :)
}
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
    checkIRcode();
    IR1key12.functionPointer = IR1key12Function;
    IR1key16.functionPointer = IR1key16Function;
    IR1key13.functionPointer = IR1key13Function;
    IR1key15.functionPointer = IR1key15Function;
    IR1key14.functionPointer = IR1key14Function;
    IR1key1.functionPointer = IR1key1Function;
    IR1key2.functionPointer = IR1key2Function;
    IR1key3.functionPointer = IR1key3Function;
    IR1key4.functionPointer = IR1key4Function;
    IR1key5.functionPointer = IR1key5Function;
    IR1key6.functionPointer = IR1key6Function;
    IR1key7.functionPointer = IR1key7Function;
    IR1key8.functionPointer = IR1key8Function;
    IR1key9.functionPointer = IR1key9Function;
    IR1key0.functionPointer = IR1key0Function;
    IR1key10.functionPointer = IR1key10Function;
    IR1key11.functionPointer = IR1key11Function;

  }  

