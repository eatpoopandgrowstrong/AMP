// Navigation lights:
const int NavButton = A0;
const int NavLED = 2;

// Landing lights:
const int LandButton = A1;
const int LandLED1 = 3;
const int LandLED2 = 4;
const int LandLED3 = 5;

// Runway Turnoff & Taxi lights:
const int TaxiButton = A2;
const int TaxiLED = 6;

// Wing Inspection lights:
const int WIButton = A3;
const int WILED = 7;

// Red Anti-collision/Strobe lights:
const int RedACButton = A4;
const int RedACLED = 8;

// White Anti-collision/Strobe lights:
const int WhiteACButton = A5;
const int WhiteACLED = 9;

void blinkLEDs(int pin, long on, long off) {
  digitalWrite(pin, HIGH);
  delay(on);
  digitalWrite(pin, LOW);
  delay(off);
}

void setup() {
  // put your setup code here, to run once:

  // Navigation lights:
  pinMode(NavButton, INPUT);
  pinMode(NavLED, OUTPUT);

  // Landing lights:
  pinMode(LandButton, INPUT);
  pinMode(LandLED1, OUTPUT);
  pinMode(LandLED2, OUTPUT);
  pinMode(LandLED3, OUTPUT);

  // Runway Turnoff & Taxi lights:
  pinMode(TaxiButton, INPUT);
  pinMode(TaxiLED, OUTPUT);

  // Wing Inspection lights:
  pinMode(WIButton, INPUT);
  pinMode(WILED, OUTPUT);

  // Red Anti-collision/Strobe lights:
  pinMode(RedACButton, INPUT);
  pinMode(RedACLED, OUTPUT);

  // White Anti-collision/Strobe lights:
  pinMode(WhiteACButton, INPUT);
  pinMode(WhiteACLED, OUTPUT);
}

void loop() {

  void Nav (){

      while(!digitalRead(NavButton)){
            digitalWrite(NavLED, LOW);
        }
        while(digitalRead(NavButton));
        delay(100);

        while(!digitalRead(NavButton)){
            digitalWrite(NavLED, HIGH);
        }
        while(digitalRead(NavButton));
        delay(100);
    }

  void Land (){
      
      while(!digitalRead(LandButton)){
            digitalWrite(LandLED, LOW);
        }
        while(digitalRead(LandButton));
        delay(100);

        while(!digitalRead(LandButton)){
            digitalWrite(LandLED, HIGH);
        }
        while(digitalRead(LandButton));
        delay(100);
    }

  void Taxi () {

    while (!digitalRead(TaxiButton)) {
      digitalWrite(TaxiLED, LOW);
    }
    while (digitalRead(TaxiButton));
    delay(100);

    while (!digitalRead(TaxiButton)) {
      digitalWrite(TaxiLED, HIGH);
    }
    while (digitalRead(TaxiButton));
    delay(100);
  }

  void WI () {

    while (!digitalRead(WIButton)) {
      digitalWrite(WILED, LOW);
    }
    while (digitalRead(WIButton));
    delay(100);

    while (!digitalRead(WIButton)) {
      digitalWrite(WILED, HIGH);
    }
    while (digitalRead(WIButton));
    delay(100);
  }

  void RedAC() {
    
    int ON = 500;
    int OFF = 1500;
    
    while (!digitalRead(RedACButton)) {
      digitalWrite(RedACLED, LOW);
    }
    while (digitalRead(RedACButton));
    delay(100);

    while (!digitalRead(RedACButton)) {
      blinkLEDs(RedACLED, ON, OFF);
    }
    while (digitalRead(RedACButton));
    delay(100);
  }

}

  void WhiteAC() {

    int ON = 250;
    int PAUSE = 250;
    int OFF = 750;
    
    while (!digitalRead(WhiteACButton)) {
      digitalWrite(WhiteACButton, LOW);
    }
    
    while (digitalRead(WhiteACButton));
    delay(100);

    while (!digitalRead(WhiteACButton)) {
      digitalWrite(WhiteACButton, HIGH);
      delay(ON);
      digitalWrite(WhiteACLED, LOW);
      delay(PAUSE);
      digitalWrite(WhiteACLED, HIGH);
      delay(ON);
      digitalWrite(WhiteACLED, LOW);
      delay(OFF);
    }
    
    while (digitalRead(WhiteACButton));
    delay(100);
  }
