#include <LiquidCrystal.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
int speakerPin = 9;
int length = 1;
#define DHTPIN 6
#define DHTTYPE DHT11
#define LED_TOO_COLD A0
#define LED_PERFECT A1
#define LED_TOO_HOT A2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");

  dht.begin();
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  pinMode(speakerPin, OUTPUT);
  /*pinMode (A0 , OUTPUT);
  pinMode (A1 , OUTPUT);
  pinMode (A2 , OUTPUT);*/
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
    digitalWrite(A0, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (250);
    digitalWrite(speakerPin, LOW);
    digitalWrite(A0, LOW);
  }
  if (20 < t < 27) {
    Serial.println("Perfect temperature!");
    digitalWrite(A1, HIGH);
    delay (500);
    digitalWrite(A1, LOW);
  }
  if (t >= 29) {
    Serial.println("Too hot!");
    digitalWrite(A2, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (250);
    digitalWrite(speakerPin, LOW);
    digitalWrite(A2, LOW);
  }

}
