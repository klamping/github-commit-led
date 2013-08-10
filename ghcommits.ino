#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

const int colors[3] = { LED_GREEN, LED_YELLOW, LED_RED };

int count = 0;

int commits[] = { 0,0,0,8,10,3,0,0,1,2,2,6,1,0,0,2,1,1,4,5,0,13,4,0,0,2,3,0,8,3,7,3,6,7,2,1,9,4,1,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 };

boolean hasNewData = false;

const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);

  matrix.begin(0x70);  // pass in the address
  
  matrix.setBrightness(5);
  
  matrix.setRotation(3);
}

void showHistory() {
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
    matrix.drawPixel(x, 7, colors[0]);
  }

  // reset data flag to false
  hasNewData = false;

  matrix.writeDisplay();
}

String content = "";
int i = 0;

void loop() {
  if (Serial.available() > 0) {
      digitalWrite(ledPin, HIGH);
      delay(5);
      digitalWrite(ledPin, LOW);
      delay(5);

    int tempCommit = 0;
    while(Serial.available()) {
      
      char incoming = Serial.read();
      if (incoming != ',') {
        tempCommit = (tempCommit * 10) + incoming;
        if (tempCommit > 0) {
          tempCommit = 10;
        }
        else { 
          tempCommit = int(incoming);
        }
      } else {
        commits[i] = tempCommit;
        Serial.write(tempCommit);
        tempCommit = 0;
        i++;
      }
    }

    if (i > 55) {
       hasNewData = true;
       i = 0;
    }
  }
  
  if (hasNewData) {
    showHistory();
  }

//  delay(2000);
}
