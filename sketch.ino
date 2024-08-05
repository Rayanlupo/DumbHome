#include <Servo.h>
#include "SafeState.h"

int EchoPin = 0;
int TrigPin = 1; 
int ServoPin = 18;
int Green = 12;
int Red = 13;
int locked = 0;
int unlocked = 90;


const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {27, 26, 25, 33};
byte colPins[KEYPAD_COLS] = {32, 35, 34, 9};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);





void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
