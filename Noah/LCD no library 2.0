#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
int speakerPin = 9;
#define DHTPIN 6
#define DHTTYPE DHT11
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
//0X3F IS LCD ADDRESS IN HEX, THERE ARE 16 COLUMNS AND 2 ROWS IN THE LCD
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  lcd.init(); //INITIALISE THE LCD
  lcd.backlight(); //SWITCH ON THE BACKLIGHT
  dht.begin();
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  pinMode(speakerPin, OUTPUT);
 for (int DigitalPin = 7; DigitalPin <= 9; DigitalPin++) 
 {
  pinMode(DigitalPin, OUTPUT);
 }
  lcd.begin(16,2);  //16 by 2 character display
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);  //printing temperarture to the LCD display
  lcd.print("'C");
  
  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(h);  //printing humidity to the LCD display
  lcd.print("%");
  delay(500);
  lcd.clear();

 if (20 < t < 27) {
  lcd.setCursor (0,0);
  lcd.print("No fire");
  lcd.setCursor (0,1);
  lcd.print("detected");
  delay(1000);
  lcd.clear(); }
if (t>=29) {
  lcd.setCursor (0,0);
  lcd.print("Caution");
  lcd.setCursor (0,1);
  lcd.print("fire!!");
  delay(1000);
  lcd.clear(); }


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  if (t <= 20) {
    Serial.println("Too cold!");
    digitalWrite(speakerPin, HIGH);
    delay (250);
    digitalWrite(speakerPin, LOW);
  }
  if (20 < t < 27) {
    Serial.println("Perfect temperature!");
    delay (500);
  }
  if (t >= 29) {
    Serial.println("Too hot!");
    digitalWrite(speakerPin, HIGH);
    delay (250);
    digitalWrite(speakerPin, LOW);
  }

}
