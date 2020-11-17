const int LED=2;
const int button=3;

int x = 0;

void setup() {
  // put your setup code here, to run once:

pinMode(LED,OUTPUT);
pinMode(button,INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:

if(digitalRead(button)==LOW){

  if(x==0){
    digitalWrite(LED,HIGH);
    x=1;
  }
  else{
    digitalWrite(LED,LOW);
    x=0;
  }

 delay(500);
}

}
