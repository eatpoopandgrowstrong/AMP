const int A0input=A0;

float input;
float test;
void setup() {
  // put your setup code here, to run once:

pinMode(A0input,INPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

input=analogRead(A0input);

Serial.print(input);
}
