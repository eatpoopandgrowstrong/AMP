#include <IRremote.h>

#define IR1 16724175


int IRpin = 10;
IRrecv irrecv(IRpin);
decode_results results;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    Serial.println(results.value,DEC);
    if(results.value==IR1){
    Serial.println("Button 1 was pressed');
    }
    results.value=0;
    irrecv.resume();
  }
  
}
