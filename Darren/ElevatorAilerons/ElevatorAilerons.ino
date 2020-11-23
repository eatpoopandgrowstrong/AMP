// include Arduino stepper motor library
#include <Stepper.h>
#include <Servo.h>


// define number of steps per revolution
#define STEPS 32
 
// define stepper motor control pins
#define IN1  11
#define IN2  10
#define IN3   9
#define IN4   8
 
// initialize stepper library
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
Servo myservo;
// joystick pot output is connected to Arduino A0
#define joystick  A0

int potpin = 1;
int val;

void setup()
{
  Serial.begin(9600);
   myservo.attach(7);
}
 
void loop()
{
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
 
  // read analog value from the potentiometer
  int val = analogRead(joystick);
 
  // if the joystic is in the middle ===> stop the motor
  if(  (val > 500) && (val < 523) )
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
 
  else
  {
    // move the motor in the first direction
    if(val >= 523)
    {
      Serial.println(val);                            //PRINT THE VALUE OF 'VAL'
      
      // map the speed between 5 and 500 rpm
      int speed_ = map(val, 523, 1023, 5, 500);
      // set motor speed
      stepper.setSpeed(speed_);
 
      // move the motor (1 step)
      stepper.step(5);
 
      val = analogRead(joystick);
      Serial.println(val);                            //PRINT THE VALUE OF 'VAL'
    }
 
    // move the motor in the other direction
    if (val <= 500)
    {
      Serial.println(val);                            //PRINT THE VALUE OF 'VAL'
      // map the speed between 5 and 500 rpm
      int speed_ = map(val, 500, 0, 5, 500);
      // set motor speed
      stepper.setSpeed(speed_);
 
      // move the motor (1 step)
      stepper.step(-5);
 
      val = analogRead(joystick);
      Serial.println(val);
    }
 
  }
 
}
