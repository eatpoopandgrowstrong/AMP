#include <IRremote.h>
#include <Servo.h>

void Decoder();
void NavLights();
void LandingGear();

#define IR1 16724175  //IR1 is for NavLights
#define IR2 16718055  //IR2 is to toggle the landing gear
#define IR3 16743045  //IR3 is for 
#define IR4 16716015
#define IR5 16726215
#define IR6 16734885

//PINS SETUP
const int LED=2;
const int button=3;
const int GearUp=8;
const int GearDown=9;
const int IRpin = 10;

//LED
int x=0;

//buttons
int button1=0;
int button2=0;
int button3=0;
int button4=0;
int button5=0;
int button6=0;
int button7=0;

//IR
IRrecv irrecv(IRpin);
decode_results results;

//SERVOMOTOR
Servo myservo;

int landing=0;


void setup() {
  // put your setup code here, to run once:
  //LED
  pinMode(LED,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  //IR
  Serial.begin(9600);
  irrecv.enableIRIn();


  //SERVO
  myservo.attach(6);

  pinMode(GearUp,OUTPUT);
  pinMode(GearDown,OUTPUT);
  myservo.write(153);
  
  digitalWrite(GearUp,HIGH);
  digitalWrite(GearDown,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Decoder();
  NavLights();
  LandingGear();

}

  



void Decoder(){
    if(irrecv.decode(&results)){
    //Serial.println(results.value,DEC);
      if(results.value==IR1){
      Serial.println("Button 1 was pressed");
      button1=1;
      }
      if(results.value==IR2){
      Serial.println("Button 2 was pressed");
      button2=1;
      }
      if(results.value==IR3){
      Serial.println("Button 3 was pressed");
      button3=1;
      }
      if(results.value==IR4){
      Serial.println("Button 4 was pressed");
      button4=1;
      }
      if(results.value==IR5){
      Serial.println("Button 5 was pressed");
      button5=1;
      }
      if(results.value==IR6){
      Serial.println("Button 6 was pressed");
      button6=1;
      }
      
      irrecv.resume();
  
    }
}

void NavLights(){
    if(button1==1){
  
    if(x==0){
      digitalWrite(LED,HIGH);
      x=1;
      
    }
    else{
      digitalWrite(LED,LOW);
      x=0;
      
    }
    button1=0;
  }
}

void LandingGear(){
  
  if(button2==1){

    if(landing==0){
      myservo.write(63);
      landing=1;
      digitalWrite(GearUp,LOW);
      digitalWrite(GearDown,HIGH);
    }
    else{
      myservo.write(153);
      landing=0;
      digitalWrite(GearUp,HIGH);
      digitalWrite(GearDown,LOW);
    }
    button2=0;

  }
  
}
