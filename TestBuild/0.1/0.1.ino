//LIBRARIES

#include <IRremote.h>
#include <Servo.h>
#include<Wire.h>




//FUNCTIONS

void Decoder();
void Spoilers();
void LandingGear();



//DEFINING IR BUTTONS

#define IRButton1 0xC
#define IRButton2 0x18
#define IRButton3 0x5E
#define IRButton4 0x8
#define IRButton5 0x1C
#define IRButton6 0x5A
#define IRButton7 0x42
#define IRButton8 0x52
#define IRButton9 0x4A


//Buttons

int button1=0;
int button2=0;
int button3=0;
int button4=0;
int button5=0;
int button6=0;
int button7=0;
int button8=0;
int button9=0;

/*PINS SET UP

List of Pins



*/

//millis

unsigned long CurrentMillis;

//IR Pin
const int IR_RECEIVE_PIN = 10;





//LANDING GEAR
Servo LandingGearServo;
Servo LandingGearCoverServo;


int LandingGearCoverStatus = 0;
unsigned long PreviousGearCoverMillis = 0;
unsigned long GearCoverInterval = 1000;       //interval between cover and the landing gear and vice versa

int LandingGearStatus = 1;

int landing = 0;


void setup() {
  // put your setup code here, to run once:


  //Basic Serial Setup
  Serial.begin(9600);

  //IR SetUp
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definitiona

  //Landing Gear
  
  LandingGearServo.attach(7);
  LandingGearServo.attach(8);
  


  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  CurrentMillis = millis();

  Decoder();


   //TBD

  

  Spoilers(); 
  LandingGear();

}

void Decoder(){
  if(IrReceiver.decode()){
    
    if(IrReceiver.decodedIRData.command == IRButton1){
      Serial.println("Button 1 was pressed");
      button1=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton2){
      Serial.println("Button 2 was pressed");
      button2=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton3){
      Serial.println("Button 3 was pressed");
      button3=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton4){
      Serial.println("Button 4 was pressed");
      button4=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton5){
      Serial.println("Button 5 was pressed");
      button5=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton6){
      Serial.println("Button 6 was pressed");
      button6=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton7){
      Serial.println("Button 7 was pressed");
      button7=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton8){
      Serial.println("Button 8 was pressed");
      button8=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton9){
      Serial.println("Button 9 was pressed");
      button9=1;
    }
    IrReceiver.resume(); // Continue receiving
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

      The reverse happens when the landing gear is brought up:

      Gear cover down, wait
      Landing gear goes up, wait
      Gear cover up, wait

      Perhaps reuse the same gear cover up/down sequence, but manipulate a variable for the position/sequencing of the landing gear.

      Once this is tested, we can move onto doing multiple, such as the nose and the fuselage landing gears.

    */


    switch (LandingGearStatus) {

      case 1:

        LandingGearCoverServo.write(0);
        PreviousGearCoverMillis = CurrentMillis;
        LandingGearStatus = 2;

        break;

      case 2:

        if (CurrentMillis - PreviousGearCoverMillis >= GearCoverInterval) {


          if (landing == 0) {

            LandingGearServo.write(0);
            landing = 1;

          }
          else {

            LandingGearServo.write(90);
            landing = 0;

          }

          PreviousGearCoverMillis = CurrentMillis;
          LandingGearStatus = 3;

        }

        break;

      case 3:

        if (CurrentMillis - PreviousGearCoverMillis >= GearCoverInterval) {

          LandingGearCoverServo.write(90);
          button2 = 0;
          LandingGearStatus = 1;

        }


        break;
    }





    /*

      if (landing == 0) {

      if (LandingGearCoverStatus == 0) {

        LandingGearCoverServo.write(0);             //Landing gear cover is being brought down
        PreviousGearCoverMillis = CurrentMillis;    //start the timer
        LandingGearCoverStatus = 1;

      }
      else {

        if (CurrentMillis - PreviousGearCoverMillis >= GearCoverInterval) {



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

    */
  }

}

void Spoilers(){
  
}
void Navlight(){
  if(button6 ==1){
  digitalwrite(7,HIGH);
  button6 = 0;}
  else{
    digitalwrite(7,LOW);
    
  }
  
}
