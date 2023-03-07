#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); // RX | TX
int motorPin1 = 5; // Arduino pin for motor direction control
int motorPin2 = 6; // Arduino pin for motor direction control
int motorPin3 = 9; // PWM pin for motor speed control
int motorPin4 = 10; // PWM pin for motor speed control
int maxSpeed = 3000; // Maximum speed in RPM
int speed = 0; // Initial speed

void setup() {
  BTserial.begin(9600); // Bluetooth serial communication speed
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);
}

void loop() {
  if (BTserial.available()) {
    char command = BTserial.read();
    if (command == 'F') { // Forward
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      speed += 50;
      if (speed > maxSpeed) {
        speed = maxSpeed;
      }
    } else if (command == 'B') { // Backward
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      speed -= 50;
      if (speed < -maxSpeed) {
        speed = -maxSpeed;
      }
    } else if (command == 'S') { // Stop
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      speed = 0;
    }
    analogWrite(motorPin3, abs(speed));
    analogWrite(motorPin4, abs(speed));
  }
}

/*This code uses the SoftwareSerial library to establish a Bluetooth serial communication between the Arduino Uno and a smartphone or other Bluetooth device.
 It controls the direction of the motor using digital output pins, and controls the speed using PWM output pins. The maxSpeed variable sets the maximum speed in RPM, 
 and the speed variable keeps track of the current speed. The loop() function reads incoming Bluetooth commands and adjusts the motor speed and direction accordingly. 
 The analogWrite() function sets the PWM duty cycle based on the absolute value of the speed variable. The if statements ensure that the speed variable does not exceed 
 the maximum speed or go below the negative maximum speed. The commands used in this example are 'F' for forward, 'B' for backward, and 'S' for stop, but you can modify them to suit your needs.*/

