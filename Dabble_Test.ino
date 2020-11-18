#include <Dabble.h>
#include <SoftwareSerial.h>
#include "pitches.h"

#define CUSTOM_SETTINGS

#define INCLUDE_GAMEPAD_MODULE

// set Motor A to Arduino Pins
int motor_A = 12; // official Arduino Motor Shield uses D12
int motor_B = 13; // official Arduino Motor Shield uses D13
int buzzer = 4;

// set the Motor Speed using the Arduino Pins
int motor_A_speed = 10; // official Arduino Motor Shield uses D3
int motor_B_speed = 11; // official Arduino Motor Shield uses D11

// set the time between motor on and motor off
int wait_in_milliseconds = 100;

void setup() {
  // put your setup code here, to run once:
  Dabble.begin(9600);
  Serial.begin(9600);

    // set the Arduino pin to OUTPUT mode
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

// notes in the melody:
int melody[] = {
  F3, D3, AS2, AS2, AS2, C3, D3, DS3, F3, F3, F3 ,D3 
};

int noteDurations[] = {
  8,  8,   4,   4,   8,  8,  8,  8,  4,  4,   4,  8 
};

struct Note {
 int key;
 int duraiton;
};

void playMelody() {
for (int thisNote = 0; thisNote < 12 ; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(4, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Dabble.processInput();
  if (GamePad.isUpPressed()) 
    forward();
  if (GamePad.isDownPressed()) 
    backward();
  
  if (GamePad.isLeftPressed()) turnLeft();
  if (GamePad.isRightPressed()) turnRight();
  if (GamePad.isTrianglePressed()) beep();
  if (GamePad.isSquarePressed()) playMelody();
}
