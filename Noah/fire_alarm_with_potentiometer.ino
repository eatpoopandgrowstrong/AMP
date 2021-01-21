#include <IRremote.h> 
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#define DHTPIN 6
#define DHTTYPE DHT11
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
//0X3F IS LCD ADDRESS IN HEX, THERE ARE 16 COLUMNS AND 2 ROWS IN THE LCD
DHT dht(DHTPIN, DHTTYPE);


void Decoder();
void Temp();
void LCD();
void Potentiometer();

//DHT11
unsigned long TempInterval = 500;
unsigned long PreviousTempMillis;
double h;
double t;


//LCD
unsigned long CurrentMillis;
unsigned long LCDInterval = 1000;
unsigned long PreviousLCDMillis;
int LCDPage;
int PreviousPage;

//Potentiometer
int sensorPin = A0;

//Buzzer
int speakerPin = 9;

//IR
#define IR1 16724175  //IR1 is for NavLights
#define IR2 16718055  //IR2 is to toggle the landing gear
#define IR3 16743045  //IR3 is for Spoilers
#define IR4 16716015
#define IR5 16726215
#define IR6 16734885

const int IRpin = 10;
IRrecv irrecv(IRpin);
decode_results results;

//buttons
int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;
int button5 = 0;
int button6 = 0;
int button7 = 0;


int outputValue=0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin,INPUT);
  lcd.init(); //INITIALISE THE LCD
  lcd.backlight(); //SWITCH ON THE BACKLIGHT
  dht.begin();
}
 void loop(){
  CurrentMillis = millis();
  Decoder();
  LCD();
  Temp();
  Potentiometer();
 }

 void Decoder() {

  if (irrecv.decode(&results)) {
    //Serial.println(results.value,HEX);
    //Serial.println(&results);
    //Serial.println(results.value);
  
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

void Temp(){
  if(CurrentMillis-PreviousTempMillis>=TempInterval){
  h = dht.readHumidity();
  t = dht.readTemperature();
  }
}
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
    PreviousLCDMillis+=LCDInterval;
Serial.println(PreviousLCDMillis);
  }

  void Potentiometer(){
  int analogValue = analogRead(sensorPin);
  //Serial.println(analogValue);
  outputValue = map (analogValue, 0, 1023, 300, 800);
  //Serial.println(outputValue);
  }
