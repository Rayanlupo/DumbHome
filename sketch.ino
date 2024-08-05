#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>


Servo servo1;
int EchoPin = 5;
int TrigPin = 4; 
int ServoPin = 18;
int Green = 12;
int Red = 13;
int locked = 0;
int unlocked = 90;
String secretCode = "1234";
int distance;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {27, 26, 25, 33};
byte colPins[KEYPAD_COLS] = {32, 35, 34, 19};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);





void setup() {
  servo1.attach(ServoPin);
  pinMode(ServoPin, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT),
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(18, 15);
  Serial.begin(115200);
}

void loop() {
  servo1.write(locked);
 digitalWrite(TrigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(TrigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(TrigPin, LOW);
 int duration = pulseIn(EchoPin, HIGH);
 distance = (duration * 0.034 / 2);
 if (distance <= 40){
  display.display();
display.print("Welcome, please insert the PIN");
Serial.print("start");
String PIN = pin();
  if (PIN == secretCode){
    Serial.print("acces allowed");
    display.display();
    display.print("access allowed");
    servo1.write(unlocked);
    delay(5000);
    servo1.write(locked);
  }
  else{
    display.display();
    display.print("Access denied");
  }
 } 
}


String pin(){
  String code = "";
 
  while (code.length() < 4){
    char key = keypad.getKey();
     if (key >= '0' && key <= '9') {
      code += key;
    }
  }
  return code;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
