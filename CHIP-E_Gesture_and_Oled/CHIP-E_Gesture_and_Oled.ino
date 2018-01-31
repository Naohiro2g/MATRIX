/****************************************************************
  CHIP-E walking robot
  10 April 2017
  Added the HC-05 master bluetooth unit
  
  GestureTest.ino
  APDS-9960 RGB and Gesture Sensor
  Shawn Hymel @ SparkFun Electronics
  May 30, 2014
  https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor

  Tests the gesture sensing abilities of the APDS-9960. Configures
  APDS-9960 over I2C and waits for gesture events. Calculates the
  direction of the swipe (up, down, left, right) and displays it
  on a serial console.

  To perform a NEAR gesture, hold your hand
  far above the sensor and move it close to the sensor (within 2
  inches). Hold your hand there for at least 1 second and move it
  away.

  To perform a FAR gesture, hold your hand within 2 inches of the
  sensor for at least 1 second and then move it above (out of
  range) of the sensor.

  Hardware Connections:

  IMPORTANT: The APDS-9960 can only accept 3.3V!

  Arduino Pin  APDS-9960 Board  Function

  3.3V         VCC              Power
  GND          GND              Ground
  A4           SDA              I2C Data
  A5           SCL              I2C Clock
  2            INT              Interrupt

  Resources:
  Include Wire.h and SparkFun_APDS-9960.h

  Development environment specifics:
  Written in Arduino 1.0.5
  Tested with SparkFun Arduino Pro Mini 3.3V

  This code is beerware; if you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful, please
  buy us a round!

  Distributed as-is; no warranty is given.
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

/*********************************************************************
  This example is for a 128x64 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Basic Bluetooth sketch HC-05_03_9600
// Connect the HC-05 module and communicate using the serial monitor
//
// HC-05 IS THE MASTER UNIT
//
// THIS SKETCH SENDS A 0 AND A 1 TO THE SLAVE - WHICH IS RUNNING A
// SKETCH THAT TURNS ON AND OFF AN LED
//
// The HC-05 defaults to commincation mode when first powered on.
//
//
//  Pins
//  BT VCC to Arduino 5V out.
//  BT GND to GND
//  BT RX to Arduino pin 3 (through a voltage divider) - runs on 3.3 vdc
//  BT TX to Arduino pin 2 (no need voltage divider)


//--------------------------LIBRARIES----------------------------------------------------------------
// set up the HC-05 Bluetooth module
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(6, 7); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX.
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// Instead on the Mega - we'll use pins 18=RX1 and 19=TX1 and run them
// through the logic level board on input 3 and 4
char c = ' ';     //use this for Serial1 output to bluetooth module
//
/*********************************************************************
 *********************************************************************/

void setup() {

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));
  Serial1.begin(9600);  //USED FOR THE HC-O5 BLUETOOTH UNIT
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
}
/*********************************************************************
 *********************************************************************/
void loop() {
  if ( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
}
/*********************************************************************
 *********************************************************************/
void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
  if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        c = 'U';
        Serial1.write(c);
        // Clear the buffer.
        display.clearDisplay();
        upArrow();
        break;

      case DIR_DOWN:
        Serial.println("DOWN");
        c = 'D';
        Serial1.write(c);
        // Clear the buffer.
        display.clearDisplay();
        downArrow();
        break;

      case DIR_LEFT:
        Serial.println("LEFT");
        c = 'L';
        Serial1.write(c);
        // Clear the buffer.
        display.clearDisplay();
        leftArrow();
        break;

      case DIR_RIGHT:
        Serial.println("RIGHT");
        c = 'R';
        Serial1.write(c);
        // Clear the buffer.
        display.clearDisplay();
        rightArrow();
        break;

      case DIR_NEAR:
        Serial.println("NEAR");
        c = 'N';
        Serial1.write(c);
        // Clear the buffer.
        display.clearDisplay();
        halt();
        break;

      case DIR_FAR:
        Serial.println("FAR");
        c = 'F';
        Serial1.write(c);
        // Clear the buffer.
        display.clearDisplay();
        dance();
        break;

      default:
        Serial.println("NONE");
    }
  }
}

void leftArrow()     {
  uint8_t color = WHITE;
  //for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
  display.fillTriangle(10, 32,
                       60, 2,
                       60, 60, WHITE);
  //if (color == WHITE) color = BLACK;
  //else color = WHITE;
  //display.display();
  display.fillRect(60, 18, 80, 30, WHITE);
  display.display();
}

void rightArrow()     {
  uint8_t color = WHITE;
  //for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
  display.fillTriangle(80, 2,
                       125, 32,
                       80, 60, WHITE);
  //if (color == WHITE) color = BLACK;
  //else color = WHITE;
  //display.display();
  display.fillRect(0, 18, 80, 30, WHITE);
  display.display();
}

void upArrow()     {
  uint8_t color = WHITE;
  //for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
  display.fillTriangle(60, 2,
                       100, 32,
                       20, 32, WHITE);
  display.fillRect(40, 32, 40, 60, WHITE);
  display.display();
}


void downArrow()     {
  uint8_t color = WHITE;
  //for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
  display.fillTriangle(60, 60,
                       100, 32,
                       20, 32, WHITE);
  display.fillRect(40, 0, 40, 32, WHITE);
  display.display();
}

void dance()   {
  // text display tests
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println("DANCE!");
  display.display();
}

void halt()    {
  // text display tests
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.println("STOP!");
  display.display();
}

