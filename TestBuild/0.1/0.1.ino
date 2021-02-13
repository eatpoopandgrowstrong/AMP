//LIBRARIES

#include <IRremote.h>
#include <Servo.h>
#include<Wire.h>
//#include <LiquidCrystal_I2C.h>
//#include <DHT.h>
//#include <Adafruit_Sensor.h>

#define DHTPIN 6
#define DHTTYPE DHT11
//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
//DHT dht(DHTPIN, DHTTYPE);

//FUNCTIONS

void Decoder();
void Spoilers();
void LandingGear();
void Navlights();
void LogoLights();
void LandingLights();
void StrobeLightDecoder();
void StrobeLightAction();
void Temp();
void LCD();
void Potentiometer();
void Rudder();




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


//LightsLED
const int NavLED=22;
const int StrobeLEDs=21;
const int LogoLED=20;
const int LandingLED=19;


//Rudder Pin
const int RudderAxis = A10;//Placeholder


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

//Rudder
Servo RudderServo1;


int LandingGearCoverStatus = 0;
unsigned long PreviousGearCoverMillis = 0;
unsigned long GearCoverInterval = 1000;       //interval between cover and the landing gear and vice versa

int LandingGearStatus = 1;

int landing = 0;

//Navlights

//LogoLights

//LandingLights

//StrobeLights

int StrobeOnOff = 0;
unsigned long PreviousStrobeMillis=0;
unsigned long StrobeInterval=1000;

int StrobeStatus=0;


//DHT11
unsigned long TempInterval = 500;
unsigned long PreviousTempMillis;
double h;
double t;

//LCD
unsigned long LCDInterval = 1000;
unsigned long PreviousLCDMillis;
int LCDPage;
int PreviousPage;
int outputValue=0;

//Potentiometer
int sensorPin = A0;


void setup() {
  // put your setup code here, to run once:


  //Basic Serial Setup
  Serial.begin(9600);

  //IR SetUp
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definitiona

  //Landing Gear
  
  LandingGearServo.attach(7);
  LandingGearServo.attach(8);

  //LCD Backlight
  //lcd.init(); //INITIALISE THE LCD
  //lcd.backlight(); //SWITCH ON THE BACKLIGHT

  //Initialise Potentiometer  
  pinMode(sensorPin,INPUT);

  //Initialise DHT11
  //dht.begin();

  //Rudder
  RudderServo1.attach(13);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  CurrentMillis = millis();

  Decoder();


   //TBD

  

  Spoilers(); 
  LandingGear();
  Navlights();
  LogoLights();
  LandingLights();
  StrobeLightDecoder();
  StrobeLightAction();
  LCD();
  Temp();
  Potentiometer();
  Rudder();

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

void Navlights(){
  if(button6 ==1){
  digitalWrite(NavLED,HIGH);
  button6 = 0;}
  else{
    digitalWrite(NavLED,LOW);
   button6 = 0;
  }
}
  void LogoLights(){
  if(button8 ==1){
  digitalWrite(LogoLED,HIGH);
  button8 = 0;}
  else{
    digitalWrite(LogoLED,LOW);
   button8 = 0;
  }
  }

  void LandingLights(){
  if(button8 ==1){
  digitalWrite(LandingLED,HIGH);
  button9 = 0;}
  else{
    digitalWrite(LandingLED,LOW);
   button9 = 0;
  }

}
 void StrobeLightDecoder(){
  if(button7 ==1){
    if(StrobeStatus==0){
      StrobeStatus=1;
    }
  else if(button7 ==0){
      if(StrobeStatus==1){
        StrobeStatus=0;}
      }
          }
    
    
 }
  
void StrobeLightAction(){
  if(CurrentMillis - PreviousStrobeMillis >= StrobeInterval){
    PreviousStrobeMillis = CurrentMillis;
  if(StrobeStatus == 1){

    if(StrobeOnOff==0){
      digitalWrite(StrobeLEDs,HIGH);
      StrobeOnOff = 1;
    }
    else if (StrobeOnOff == 1){
      digitalWrite(StrobeLEDs, LOW);
      StrobeOnOff = 0;
    
    
  }

  }  
  }
}
/*
void LCD(){

  if(CurrentMillis-PreviousLCDMillis>=LCDInterval){
  }  
  /*if(button5 == 1){
    LCDPage=1;
  }
  if(button6 == 1){
    LCDPage=2;
  } */
  LCDPage = 1;
    //if(temperature<15)
      //LCDPage=1;
      switch(LCDPage){
      case 1:
      //if(PreviousPage!=1){
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temp:");
      lcd.print(t);
      //Serial.println(t);
      lcd.setCursor(0,1);
      lcd.print("Humidity:");
      lcd.print(h);
      //LCDPage++;
      Serial.println(LCDPage);
      PreviousPage=1;
      //}
      break;

      case 2:
      //if(PreviousPage!=2){
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Engine Temp:");
      lcd.print(outputValue);
      lcd.print("C");
      lcd.setCursor(0,1);
      lcd.print("             ");
      //LCDPage++;
      //Serial.println(LCDPage);
      PreviousPage=2;
      //}
      break;
*/
      /*case 3:
      if(PreviousPage!=3){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hot Temp");
      lcd.setCursor(0,1);
      lcd.print("Caution, fire!!");
      //LCDPage=1;
      Serial.println(LCDPage);
      PreviousPage=3;
      }
      break; */
    }
}
/*
void Temp(){
  if(CurrentMillis-PreviousTempMillis>=TempInterval){
  h = dht.readHumidity();
  t = dht.readTemperature();
  }
}
*/
/*
void Potentiometer(){
  int analogValue = analogRead(sensorPin);
  //Serial.println(analogValue);
  outputValue = map (analogValue, 0, 1023, 300, 800);
  //Serial.println(outputValue);
  }
/*
void Rudder(){

RudderAxisRaw=analogRead(RudderAxis);
RudderAxisMapped=map(RudderAxisRaw, 0,1023, 0, 180);
RudderServo,write(RudderAxisMapped);

}
*/
