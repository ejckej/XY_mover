#include <Servo.h>

Servo servo_X;  // create servo object to control a servo
Servo servo_Y;

const int ledPin = 13;  // pin the LED is attached to
int incomingByte;       // variable stores serial data

int pos = 0;  // variable to store the servo position
int num = 0;

void setup() {
  servo_X.attach(9);  // attaches the servo on pin 9 to the servo object
  servo_Y.attach(10);
  servo_X.write(90);
  servo_Y.write(90);
  // initialize serial communication:
  Serial.begin(9600);
  Serial.println("Welcome!");
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer (not a number):
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
      Serial.println("Getting H");  //print out to serial monitor to check state
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
      Serial.println("Getting L");  //print out to serial monitor to check state
    }

    if (incomingByte == 'X') {  // && pos < 180) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      num = Serial.parseInt();
      //Serial.println(num);
      pos += num;
      Serial.println(num);
      servo_X.writeMicroseconds(10);  // tell servo to go to position in variable 'pos'
      delay(40);           // waits for the servo to reach the position
      servo_X.write(0);
    }
    if (incomingByte == 'Y') {  //&& pos > 0) {
      num = Serial.parseInt();
      pos += num;
      Serial.println(num);
      servo_Y.write(180);
      delay(num);
      servo_Y.write(90);
    }
  }
}
