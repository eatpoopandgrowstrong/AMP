const int buzzer = 3;                             //the output to the buzzer is pin 3, change this number if you change the connection to another pin

void setup() {
  // put your setup code here, to run once:
pinMode(buzzer,OUTPUT);                           //set your buzzer pin to output
}

void loop() {
  // put your main code here, to run repeatedly:

tone(buzzer,2000);                                //the tone function syntax is tone(pin, frequency), so output frequency 2000hz at pin 3
delay(100);
tone(buzzer,3000);
delay(100);

tone(buzzer,2000,5000);                           //the tone function syntax can also include the optional duration, tone(pin, frequency, duration);



//for more information on the tone function, refer to 
https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/

}
