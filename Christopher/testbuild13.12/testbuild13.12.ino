//LIBRARIES

#include <IRremote.h>//IRremote for the remote
#include <Servo.h>   //Servo for the servomotors

//FUNCTIONS
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
const int LED = 2;
const int button = 3;
const int GearUp = 8;
const int GearDown = 9;
const int IRpin = 10;

//millis

unsigned long CurrentMillis = 0;

//LED
int x = 0;

//buttons
int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;
int button5 = 0;
int button6 = 0;
int button7 = 0;

//IR
IRrecv irrecv(IRpin);
decode_results results;

//SERVOMOTOR
Servo LandingGearServo;
Servo LandingGearCoverServo;

int LandingGearCoverStatus = 0;
unsigned long PreviousGearCoverMillis = 0;
unsigned long GearCoverInterval = 1000;       //interval between cover and the landing gear and vice versa


int LandingGearStatus;

int landing = 0;


void setup() {
  // put your setup code here, to run once:

  //DEBUG
  Serial.begin(9600);

  //LED
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  //IR
  irrecv.enableIRIn();


  //SERVO
  LandingGearServo.attach(6);
  LandingGearCoverServo.attach(7);

  pinMode(GearUp, OUTPUT);
  pinMode(GearDown, OUTPUT);
  LandingGearServo.write(153);
  LandingGearCoverServo.write(90);

  digitalWrite(GearUp, HIGH);
  digitalWrite(GearDown, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  CurrentMillis = millis();

  Decoder();
  NavLights();
  LandingGear();

}





void Decoder() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value,DEC);
    if (results.value == IR1) {
      Serial.println("Button 1 was pressed");     
      button1 = 1;
    }
    if (results.value == IR2) {
      Serial.println("Button 2 was pressed");
      button2 = 1;
    }
    if (results.value == IR3) {
      Serial.println("Button 3 was pressed");
      button3 = 1;
    }
    if (results.value == IR4) {
      Serial.println("Button 4 was pressed");
      button4 = 1;
    }
    if (results.value == IR5) {
      Serial.println("Button 5 was pressed");
      button5 = 1;
    }
    if (results.value == IR6) {
      Serial.println("Button 6 was pressed");
      button6 = 1;
    }

    irrecv.resume();

  }
}

void NavLights() {
  if (button1 == 1) {

    if (x == 0) {
      digitalWrite(LED, HIGH);
      x = 1;

    }
    else {
      digitalWrite(LED, LOW);
      x = 0;

    }
    //RESET
    button1 = 0;
  }
}

void LandingGear() {

  if (button2 == 1) {
    /*
    Landing Gear is being extended down
    Note: this blob of spaghetti code is in need of some serious refactoring, consider using switch?
    There are 3 parts to the gear landing sequence:
    
    Gear cover is brought down and some time is given for it to be brought down
    Landing gear cover is brought down and some time is given for it to be brought down
    Gear Cover is brought up and some time is given for it to be brought up
 
    The reverse happens for when the landing gear is brought up:

    Gear cover down, wait
    Landing gear goes up, wait
    Gear cover up, wait

    Perhaps reuse the same gear cover up/down sequence, but manipulate a variable for the position/sequencing of the landing gear.
    
    */

    
    switch (LandingGearStatus){
      
      case 1:
      
        LandingGearCoverServo.write(0);
        PreviousGearCoverMillis = CurrentMillis;
        LandingGearStatus = 2;
      
      break;

      case 2:

        if(CurrentMillis-PreviousGearCoverMillis >= GearCoverInterval){


          if(landing==0){

            LandingGearServo.write(0);
            
          }
          else{

            LandingGearServo.write(90);
            
          }
          
          PreviousGearCoverMillis = CurrentMillis;
          LandingGearStatus = 3;
          
        }
      
      break;

      case 3:
      
        if(CurrentMillis-PreviousGearCoverMillis >= GearCoverInterval){
  
            LandingGearCoverServo.write(0);
            button2=0;
            LandingGearStatus = 1;
            
        }

      
      break;
    }






    
    if (landing == 0) {

      if(LandingGearCoverStatus==0){
        
        LandingGearCoverServo.write(0);             //Landing gear cover is being brought down
        PreviousGearCoverMillis = CurrentMillis;    //start the timer
        LandingGearCoverStatus = 1;
        
      }
      else{

        if(CurrentMillis-PreviousGearCoverMillis >= GearCoverInterval){


          
        }
      //insert timer code here, TBD
      
      LandingGearServo.write(63);             //Landing gear is brought down
      landing = 1;
      digitalWrite(GearUp, LOW);
      digitalWrite(GearDown, HIGH);

      //insert timer code here, TBD

      LandingGearCoverServo.write(90);        //Landing gear cover is being brought up once the landing gear has been deployed
    
      //reset the button
      button2 = 0;
        
      }

     
    }


    //Landing Gear is being retracted up
    else {

      LandingGearCoverServo.write(0);        //Landing gear cover is being brought down

      //insert timer code here, TBD
      LandingGearServo.write(153);            //Landing gear is brought down
      landing = 0;
      digitalWrite(GearUp, HIGH);
      digitalWrite(GearDown, LOW);

      //insert timer code here, TBD

      LandingGearCoverServo.write(90);        //Landing gear cover is being brought up once the landing gear has been retracted


      //reset the button
      button2 = 0;

    }


  }

}
