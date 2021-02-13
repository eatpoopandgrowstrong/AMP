#include<Servo.h>

const int AxisX = A0;
const int AxisY = A1;
const int RudderAxis = A2;

Servo ElevatorServo;
Servo AileronServoLeft;
Servo AileronServoRight;
Servo RudderServo;

int MappedY;
int MappedX;
int MappedRudder;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(AxisX,INPUT);
  pinMode(AxisY,INPUT);
  pinMode(RudderAxis,INPUT);
  
  ElevatorServo.attach(10);
  AileronServoLeft.attach(11);
  AileronServoRight.attach(9);
  RudderServo.attach(6);

}

void loop() {
  // put your main code here, to run repeatedly:

//Serial.println(analogRead(AxisX));
//Serial.println(analogRead(AxisY));

MappedY = map(analogRead(AxisY),0,1023,20,160);
//Serial.println(MappedY);

MappedX = map(analogRead(AxisX),0,1023,20,160);
//Serial.println(MappedX);

ElevatorServo.write(MappedY);

AileronServoLeft.write(180-MappedX);
AileronServoRight.write(180-MappedX);
/*
MappedRudder = analogRead(RudderAxis);
Serial.println(MappedRudder);
*/
}
