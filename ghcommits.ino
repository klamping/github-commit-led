#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <stdlib.h>

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

const int colors[3] = { LED_GREEN, LED_YELLOW, LED_RED };

int count = 0;

int commits[56];

boolean hasNewData = false;

void setup() {
  Serial.begin(9600);
  
  matrix.begin(0x70);  // pass in the address
  
  matrix.setBrightness(5);
  
  matrix.clear();

  matrix.writeDisplay();
}

void showHistory() {
  int count = 0;
  int numCommits;

  int consecDays = 0;
 
  int tempCommit = 0;
  boolean isConsecutive = true;
 
  matrix.clear();
    
  for(int x = 0; x < 8; x++) {
    for(int y = 1; y < 8; y++) {
      tempCommit = commits[count];

      if(tempCommit > 0) {
        if(tempCommit > 6) {
          numCommits = 0;
        } else if (tempCommit > 3) {
          numCommits = 1;
        } else {
          numCommits = 2;
        }
        if (isConsecutive) {
          consecDays++;
        }
        
        matrix.drawPixel(x, y, colors[numCommits]);
      } else {
        isConsecutive = false;
      }
      
      count++;
    }
  }

  int colorConsec = 2;
  if (consecDays > 14) {
    colorConsec = 0;
  } else if (consecDays > 7) {
    colorConsec = 1;
  }
  int modWeek = consecDays % 7;

  for (int z = 0; z < 8; z++) {
    // TODO what if modWeek == 0? (so consecDays == 7 || 14)
    if (modWeek > 0 && z == modWeek) {
      colorConsec = colorConsec + 1;
    }
    
    matrix.drawPixel(z, 0, colors[colorConsec]);
  }

  // reset data flag to false
  hasNewData = false;

  matrix.writeDisplay();
}

int i = 0;
int tempCount = 0;
char incoming;

void loop() {
  if (Serial.available() > 0) {
    while(Serial.available() > 0) {
      incoming = Serial.read();
      if(incoming == ',') {
        commits[i] = tempCount;
        tempCount = 0;
        i++;
      } else {
        // store for next round
        tempCount = (tempCount * 10) + (incoming - 48);
      }
    }

    if (i == 56) {
       hasNewData = true;
       i = 0;
    }
  }
  
  if (hasNewData) {
    showHistory();
  }
}
