/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

static uint8_t __attribute__ ((progmem)) smile_bmp[]={0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C};
static uint8_t __attribute__ ((progmem)) frown_bmp[]={0x3C, 0x42, 0xA5, 0x91, 0x91, 0xA5, 0x42, 0x3C};
static uint8_t __attribute__ ((progmem)) neutral_bmp[]={0x3C, 0x42, 0x95, 0x91, 0x91, 0x95, 0x42, 0x3C};

const int colors[3] = { LED_GREEN, LED_YELLOW, LED_RED };

int count = 0;

int commits[] = { 0,0,0,8,10,3,0,0,1,2,2,6,1,0,0,2,1,1,4,5,0,13,4,0,0,2,3,0,8,3,7,3,6,7,2,1,9,4,1,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 };

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address
  
  matrix.setBrightness(5);
  
  matrix.setRotation(3);
  
  int count = 0;
  int numCommits = 0;
  
  matrix.clear();
    
  for(int x = 0; x < 8; x++) {
    for(int y = 0; y < 7; y++) {
      if(commits[count] > 0) {
        if(commits[count] > 6) {
          numCommits = 0;
        } else if (commits[count] > 3) {
          numCommits = 1;
        } else {
          numCommits = 2;
        }
        
        matrix.drawPixel(x, y, colors[numCommits]);
      }
      
      count++;
    }
  }

  matrix.writeDisplay();
}

void loop() {
  // nothing to do here
}
