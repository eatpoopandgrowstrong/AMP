#include <Servo.h>


const int pushbutton = 3;

const int GearUp=8;
const int GearDown=9;

Servo myservo;

int x=0;
void setup() {
  // put your setup code here, to run once:

myservo.attach(6);
pinMode(pushbutton,INPUT_PULLUP);
pinMode(GearUp,OUTPUT);
pinMode(GearDown,OUTPUT);
myservo.write(153);

digitalWrite(GearUp,HIGH);
digitalWrite(GearDown,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:


if(digitalRead(pushbutton)==LOW){

  if(x==0){
    myservo.write(63);
    x=1;
    digitalWrite(GearUp,LOW);
    digitalWrite(GearDown,HIGH);
  }
  
  else{
    myservo.write(153);
    x=0;
    digitalWrite(GearUp,HIGH);
    digitalWrite(GearDown,LOW);
  }

}

delay(250);

}
