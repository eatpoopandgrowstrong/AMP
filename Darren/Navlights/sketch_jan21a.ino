#include <IRremote.h>
#define IR1 16724175  //IR1 is for NavLights
#define IR2 16718055  //IR2 is to toggle the landing gear
#define IR3 16743045  //IR3 is for Spoilers
#define IR4 16716015
#define IR5 16726215
#define IR6 16734885

//functions
void Decoder();
void navlights();

//LED
const int IRpin = 8;
int first_led_pin = 7;
int second_led_pin = 6;
int led[] = {0,0};

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


void setup() {

Serial.begin(9600);
irrecv.enableIRIn();
pinMode(first_led_pin, OUTPUT);
pinMode(second_led_pin, OUTPUT);

}

/*void loop() {

if (receiver.decode(&output)) {
unsigned int value = output.value;
switch(value) {

case first_key:
if(led[1] == 1) {
digitalWrite(first_led_pin, LOW);
led[1] = 0;
} else {
digitalWrite(first_led_pin, HIGH);
led[1] = 1;
}
break;

case second_key:
if(led[2] == 1) {
digitalWrite(second_led_pin, LOW);
led[2] = 0; }
 else {
digitalWrite(second_led_pin, HIGH);
led[2] = 1;
}
break;
}
Serial.println(value);
receiver.resume();


}
*/
void loop()
{
 Decoder();
 navlights();
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
  void navlights(){

  if(button4==1){
    digitalWrite(first_led_pin, HIGH);
    button4 =0;
  }
   
  }
  
