//LIBRARIES

#include <IRremote.h>                 //IRremote for the remote
#include <Servo.h>                    //Servo for the servomotors
#include <DHT.h>                      //DHT library for the temperature/humidity sensor
#include <DHT_U.h>
#include <Wire.h>                     //I2C LIBRARY
#include <LiquidCrystal_I2C.h>        //LCD Library

LiquidCrystal_I2C lcd(0x3F,16,2);     //I2C address is 0x3F, the LCD has 2 rows of 16 columns or characters

//FUNCTIONS
void Decoder();
void NavLights();
void LandingGear();
void Elevator();
void Ailerons();
void Spoilers();
void TemperatureHumidity();

//DEFINING IR NUMBERS
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

const int JoystickXAxis = A14;
const int JoystickYAxis = A15;


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

//LANDING GEAR
Servo LandingGearServo;
Servo LandingGearCoverServo;

int LandingGearCoverStatus = 0;
unsigned long PreviousGearCoverMillis = 0;
unsigned long GearCoverInterval = 1000;       //interval between cover and the landing gear and vice versa

int LandingGearStatus = 1;

int landing = 0;

//ELEVATOR
Servo ElevatorServo;

int XAxisRaw;
int XAxisMapped;


//AILERONS
Servo LeftAileronServo;
Servo RightAileronServo;

int YAxisRaw;
int YAxisMapped;

//TEMPERATURE AND HUMIDITY

#define DHTPIN 3
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  // put your setup code here, to run once:

  //DEBUG
  Serial.begin(9600);

  //LED
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  //IR
  irrecv.enableIRIn();


  //LANDING GEAR SERVO
  LandingGearServo.attach(6);
  LandingGearCoverServo.attach(7);

  pinMode(GearUp, OUTPUT);
  pinMode(GearDown, OUTPUT);
  LandingGearServo.write(0);
  LandingGearCoverServo.write(0);

  digitalWrite(GearUp, HIGH);
  digitalWrite(GearDown, LOW);

  //ELEVATOR SERVO
  ElevatorServo.attach(8);

  //AILERON SERVOS
  LeftAileronServo.attach(9);
  RightAileronServo.attach(10);

  //LCD
  lcd.init();                           //Initialise the LCD
  lcd.backlight();                      //Switch on the backlight

}

void loop() {
  // put your main code here, to run repeatedly:

  CurrentMillis = millis();

  //If there end up being too many functions and the rate at which the MCU processes slows down, perhaps split the latency important functions such as control surfaces to another board?
  //Run two at once?

  //Time sensitive: (Would prefer to be as close to the millis?)
  //To test individually, simply comment out the other functions
  LandingGear();


  Decoder();
  NavLights();
  Elevator();
  Ailerons();
  Spoilers();
  TemperatureHumidity();
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

  //if (button2 == 1) {
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
  //}

}

void Elevator (void) {

  XAxisRaw = analogRead(JoystickXAxis);
  XAxisMapped = map(XAxisRaw, 0 , 1023, 25, 155);

  ElevatorServo.write(XAxisMapped);

}

void Ailerons (void) {

  YAxisRaw = analogRead(JoystickYAxis);
  YAxisMapped = map(YAxisRaw, 0, 1023, 35, 145);

  LeftAileronServo.write(YAxisMapped);
  RightAileronServo.write(YAxisMapped);

}

void Spoilers (void){

  
  
}

void TemperatureHumidity (void){

}



/*
    What we can do:
    Flaps
    Slats
    Turbofans
    Noah DHT11 sensor, heat or humidity
    Engine fire extinguishing system
    
    LCD systems display
    Ultrasonic distance sensor, anti-collision system

    Military shit:
    Mid air refueling 
    
    
*/
