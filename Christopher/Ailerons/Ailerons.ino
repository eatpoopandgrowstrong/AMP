//Include Libraries

#include <Servo.h>

Servo LeftAileron;
Servo RightAileron;
Servo Elevator;



const int JoystickYAxis = A15;
const int JoystickXAxis = A14;


int YAxisRaw;
int YAxisMapped;

int XAxisRaw;
int XAxisMapped;


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

LeftAileron.attach(2);
RightAileron.attach(3);
Elevator.attach(4);


}

void loop() {
  // put your main code here, to run repeatedly:

  YAxisRaw = analogRead(JoystickYAxis);
  YAxisMapped = map(YAxisRaw, 0, 1023, 35, 145);
  
  LeftAileron.write(YAxisMapped);
  RightAileron.write(YAxisMapped);

  XAxisRaw = analogRead(JoystickXAxis);
  XAxisMapped = map(XAxisRaw, 0 ,1023, 0, 180);

  Elevator.write(XAxisMapped);
  /*
  delay(1000);
  LeftAileron.write(180);qa
  RightAileron.write(200);
  delay(1000);
  */
  
}
