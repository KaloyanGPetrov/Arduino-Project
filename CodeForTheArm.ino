#include <Servo.h>

Servo base;
Servo joint1;
Servo joint2;
Servo joint3;
Servo claw;

const int basePin = 2;
const int joint1Pin = 4;
const int joint2Pin = 6;
const int joint3Pin = 8;
const int clawPin = 10;

void setup() {
  Serial.begin(9600);
  
  base.attach(basePin);
  joint1.attach(joint1Pin);
  joint2.attach(joint2Pin);
  joint3.attach(joint3Pin);
  claw.attach(clawPin);

  base.write(90);
  joint1.write(90);
  joint2.write(90);
  joint3.write(90);
  claw.write(0);

  Serial.println("Robot Arm Ready");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read until newline character
    command.trim();  // Remove any leading or trailing whitespace

    if (command.length() < 2) {
      Serial.println("Invalid command length");
      return;
    }

    char joint = command.charAt(0);
    String params = command.substring(2);

    switch (joint) {
      case 'b':
        handleBase(params);
        break;
      case '1':
        joint1.write(params.toInt());
        Serial.print("Joint 1 Position: ");
        Serial.println(params);
        break;
      case '2':
        joint2.write(params.toInt());
        Serial.print("Joint 2 Position: ");
        Serial.println(params);
        break;
      case '3':
        joint3.write(params.toInt());
        Serial.print("Joint 3 Position: ");
        Serial.println(params);
        break;
      case 'c':
        claw.write(params.toInt());
        Serial.print("Claw Position: ");
        Serial.println(params);
        break;
      default:
        Serial.println("Unknown command");
        break;
    }
  }
}

void handleBase(String params) {
  if (params.length() < 3) {
    Serial.println("Invalid base command length");
    return;
  }

  char direction = params.charAt(0);
  int milliseconds = params.substring(1).toInt();

  switch (direction) {
    case 'r':
      base.write(80);
      Serial.println("Base turning right");
      break;
    case 'l':
      base.write(100);
      Serial.println("Base turning left");
      break;
    default:
      Serial.println("Unknown direction");
      break;
  }

  delay(milliseconds);
  base.write(90);  
}
