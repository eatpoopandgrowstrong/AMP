#include <Servo.h>

void LandingGear();

Servo LandingGearServo;
Servo LandingGearCoverServo;

int LandingGearStatus = 1;

unsigned long CurrentMillis;
unsigned long GearCoverInterval = 2000;
unsigned long PreviousGearCoverMillis;

int landing = 0;

int button2 = 0;

void setup(){

    Serial.begin(9600);
    LandingGearServo.attach(6);
    LandingGearCoverServo.attach(7);

}

void loop(){

    CurrentMillis = millis();
    LandingGear();

}

void LandingGear(){

    switch (LandingGearStatus) {

      case 1:

        LandingGearCoverServo.write(0);
        PreviousGearCoverMillis = CurrentMillis;
        LandingGearStatus = 2;

        Serial.println(LandingGearStatus);
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
        Serial.println(LandingGearStatus);
        break;

      case 3:

        if (CurrentMillis - PreviousGearCoverMillis >= GearCoverInterval) {

          LandingGearCoverServo.write(90);
          button2 = 0;
          LandingGearStatus = 1;

        }

        Serial.println(LandingGearStatus);
        break;
    }

    
}
