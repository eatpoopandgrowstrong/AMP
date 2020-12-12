#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
//0X27 IS LCD ADDRESS IN HEX, THERE ARE 16 COLUMNS AND 2 ROWS IN THE LCD
void setup() {
  lcd.init(); //INITIALISE THE LCD
  lcd.backlight(); //SWITCH ON THE BACKLIGHT
}
void loop() {

  lcd.setCursor(0, 0); //SET THE CURSOR TO FIRST COLUMN FIRST ROW
  lcd.print("TORONTO"); 
  lcd.setCursor(0, 1); // SET THE CURSOR TO FIRST COLUMN SECOND ROW
  lcd.print("MAPLE LEAFS");
  
  delay(5000); //DELAY FOR HOW LONG FOR STRING TO APPEAR
  lcd.clear(); //CLEAR THE DISPLAY
  delay(10);   //GIVE A WHILE FOR THE DISPLAY TO CLEAR
               //BEFORE DISPLAYING THE NEXT STRING

  lcd.setCursor(0, 0); //SET THE CURSOR TO FIRST COLUMN FIRST ROW
  lcd.print("GO LEAFS GO");
  lcd.setCursor(0, 1); // SET THE CURSOR TO FIRST COLUMN SECOND ROW
  lcd.print("BUDS ALL DAY");

  delay(5000);
  lcd.clear();
  delay(10);
}
