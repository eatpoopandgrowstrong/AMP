#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#define DHTPIN 6
#define DHTTYPE DHT11
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
//0X3F IS LCD ADDRESS IN HEX, THERE ARE 16 COLUMNS AND 2 ROWS IN THE LCD
DHT dht(DHTPIN, DHTTYPE);

//DHT11
unsigned long TempInterval = 10000;
unsigned long PreviousTempMillis;
double h;
double t;


//LCD
unsigned long CurrentMillis;
unsigned long LCDInterval = 1000;
unsigned long PreviousLCDMillis;
int LCDPage;
int PreviousPage;

void Temp();
void LCD();


void setup() {
  Serial.begin(9600);
  lcd.init(); //INITIALISE THE LCD
  lcd.backlight(); //SWITCH ON THE BACKLIGHT
  dht.begin();
}
 void loop(){
  CurrentMillis = millis();
  LCD();
  Temp();
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
  if(0<t&&t<20){
    LCDPage=1;
  }
  if(20<t&&t<28){
    LCDPage=2;
  }
  if(29<t&&t<32){
    LCDPage=3;
  }
     //temperature=analogRead(Potentiometer);

   
    //if(temperature<15)
      //LCDPage=1;
      switch(LCDPage){
      case 1:
      if(PreviousPage!=1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cool Temp");
      lcd.setCursor(0,1);
      lcd.print("No fire detected");
      //LCDPage++;
      Serial.println(LCDPage);
      PreviousPage=1;
      }
      break;

      case 2:
      if(PreviousPage!=2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Normal Temp");
      lcd.setCursor(0,1);
      lcd.print("No fire detected");
      //LCDPage++;
      Serial.println(LCDPage);
      PreviousPage=2;
      }
      break;

      case 3:
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
      break;
    }
    PreviousLCDMillis+=LCDInterval;

  
  }
  
