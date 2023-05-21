#include <Arduino.h>
#include <Servo.h>
#include <avr/io.h>
#include <TM1638.h>

#define CLK_PIN 7
#define DIO_PIN 8
#define STB0_PIN 9
#define POT_PIN A6
#define SERVO_1 10
#define SERVO_2 11
#define SERVO_3 13

Servo servo;
TM1638 module = TM1638(DIO_PIN, CLK_PIN, STB0_PIN);
int buttons;
int potVal;
int selectedServo = SERVO_1;
const int numReadings = 10;
int readings[numReadings];
int index = 0;
long total = 0;
int average = 0;

void printServoPosition(int pos, TM1638 module)
{
  module.setDisplayToDecNumber(pos, 0, false);
}

void sweep(int servoNum)
{
  int pos = 0;
  servo.attach(servoNum);

  for (pos = 0; pos <= 180; pos += 1)
  {
    servo.write(pos);
    printServoPosition(pos, module);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1)
  {
    servo.write(pos);
    printServoPosition(pos, module);
    delay(15);
  }
}

void setServoToPos(int servoNum, int pos)
{
  servo.attach(servoNum);
  servo.write(pos);
  printServoPosition(pos, module);
}

int averageAnalogRead(int pinToRead)
{
  total -= readings[index];
  readings[index] = analogRead(pinToRead);
  total += readings[index];
  index = (index + 1) % numReadings;
  average = total / numReadings;
  delay(10);

  return average;
}

void setup()
{
  // Serial monitor
  Serial.begin(9600);
  // TM1638 setup
  DDRB |= (1 << 7) | (1 << 8) | (1 << 9);
  module.clearDisplay();
  module.setupDisplay(true, 7);
  // set potentiometer pin as input
  pinMode(POT_PIN, INPUT);
}

void loop()
{
  buttons = module.getButtons();
  switch (buttons)
  {
  case 1:
    Serial.println("Servo 1 active");
    selectedServo = SERVO_1;
    break;
  case 2:
    Serial.println("Servo 2 active");
    selectedServo = SERVO_2;
    break;
  case 4:
    Serial.println("Servo 3 active");
    selectedServo = SERVO_3;
  case 8:
    Serial.println("Button 4 pressed");
    break;
  case 16:
    Serial.println("Button 5 pressed");
    break;
  case 32:
    Serial.println("Button 6 pressed");
    break;
  case 64:
    Serial.println("Button 7 pressed");
    break;
  case 128:
    Serial.println("Button 8 pressed");
    break;
  }
  int val = map(averageAnalogRead(POT_PIN), 0, 1023, 0, 180);
  setServoToPos(selectedServo, val);

  delay(100);
}
