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
byte rowPins[KEYPAD_ROWS] = {14, 27, 26, 25};
byte colPins[KEYPAD_COLS] = {33, 32, 19, 34};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

void setup() {
  
  
  servo1.attach(ServoPin);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(18, 15);
  
  servo1.write(locked);
}

void loop() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  int duration = pulseIn(EchoPin, HIGH);
  distance = (duration * 0.034 / 2);
  
  if (distance <= 40) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Welcome, please insert the PIN");
    display.display();
    String PIN = pin();
    
    if (PIN == secretCode) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Access allowed");
      display.display();
      servo1.write(unlocked);
      delay(5000); 
      servo1.write(locked);
    } else {
      Serial.println("Access denied");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Access denied");
      display.display();
    }
  }
  
  delay(500); 
}

String pin() {
  String code = "";
  
  while (code.length() < 4) {
    char key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        code += key;
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Enter PIN: ");
        display.print(code);
        display.display();
      }
    }
  }
  return code;
}
