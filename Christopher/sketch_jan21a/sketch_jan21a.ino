const int LED = 6;
const int LED2 = 5;

void setup() {
  // put your setup code here, to run once:
pinMode(LED,OUTPUT);
pinMode(LED2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(LED,HIGH);
delay(500);
digitalWrite(LED,LOW);
delay(500);


digitalWrite(LED2,HIGH);
delay(500);
digitalWrite(LED2,LOW);
delay(500);
}
