#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

const int colors[3] = { LED_GREEN, LED_YELLOW, LED_RED };

int count = 0;

char commits[56];

boolean hasNewData = false;

const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);

  matrix.begin(0x70);  // pass in the address
  
  matrix.setBrightness(5);
  
  matrix.setRotation(1);
  
  matrix.clear();

  matrix.writeDisplay();
}

void showHistory() {
  Serial.write("new");
  int count = 0;
  int numCommits = 0;
  
  matrix.clear();
    
  for(int x = 0; x < 8; x++) {
    for(int y = 0; y < 7; y++) {
      Serial.print(commits[count]);

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
    matrix.drawPixel(x, 7, colors[0]);
  }

  // reset data flag to false
  hasNewData = false;

  matrix.writeDisplay();
  Serial.write("end");
}

int i = 0;
String inData;

void loop() {
  if (Serial.available() > 0) {
    while(Serial.available() > 0) {
      char incoming = Serial.read();
      Serial.write(incoming);
      commits[i] = incoming;
      i++;
    }

    if (i > 55) {
       hasNewData = true;
       i = 0;
    }
  }
  
  if (hasNewData) {
    Serial.write("Has New Data");
    showHistory();
  }
}
