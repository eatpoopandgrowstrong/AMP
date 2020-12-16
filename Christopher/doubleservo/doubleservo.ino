#include <Servo.h>

Servo ServoLeft;
Servo ServoRight;


void setup() {
  // put your setup code here, to run once:

  ServoLeft.attach(2);
  ServoRight.attach(3);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  ServoLeft.write(180);
  ServoRight.write(180);

  delay(2000);

  //ServoLeft.write(115);
  //ServoRight.write(115);
  
  //delay(2000);

  //ServoLeft.write(180);
  //ServoRight.write(180);
  //delay(500);
  
  //ServoLeft.write(270);
  //ServoRight.write(270);

  //delay(500);
  
  

}
