const int button=8;
const int led=4;
const int trigger=2;
const int echo=3;

int time;
int distance;


void setup() {
  // put your setup code here, to run once:
  
pinMode(led,OUTPUT);
pinMode(button,INPUT_PULLUP);



Serial.begin(9600);
pinMode(trigger,OUTPUT);
pinMode(echo,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

    digitalWrite (trigger, HIGH);

    delayMicroseconds (10);

    digitalWrite (trigger, LOW);

    time = pulseIn (echo, HIGH);

    distance = (time * 0.034) / 2;

    Serial.println(distance);
  
    if(distance<=10)
    {
      digitalWrite(led,HIGH);
    }
    else
    {
      digitalWrite(led,LOW);
    }

    

}
