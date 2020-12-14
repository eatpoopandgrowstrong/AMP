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

  ServoLeft.write(90);
  ServoRight.write(90);

  delay(500);

  ServoLeft.write(0);
  ServoRight.write(0);

  delay(500);

  delay(500);
  
  

}
