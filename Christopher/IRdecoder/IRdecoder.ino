#include <IRremote.h>

const int IRpin(10);

IRrecv irrecv(IRpin);
decode_results kappa;

void setup(){

    Serial.begin(9600);
    irrecv.enableIRIn();

}
   
void loop(){
    if(irrecv.decode(&kappa)){

        Serial.println(kappa.value,DEC);
        
        irrecv.resume();

    }
}
