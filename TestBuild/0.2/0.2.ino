#include <IRremote.h>
#include <Servo.h>

void Decoder();


//DEFINING IR BUTTONS

#define IRButton1 0xC
#define IRButton2 0x18
#define IRButton3 0x5E
#define IRButton4 0x8
#define IRButton5 0x1C
#define IRButton6 0x5A
#define IRButton7 0x42
#define IRButton8 0x52
#define IRButton9 0x4A

//Buttons

int button1=0;
int button2=0;
int button3=0;
int button4=0;
int button5=0;
int button6=0;
int button7=0;
int button8=0;
int button9=0;


//IRPin
int IR_RECEIVE_PIN = 9;

void setup() {
  // put your setup code here, to run once:
//IR Pin
Serial.begin(9600);
IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  // put your main code here, to run repeatedly:
Decoder();
}
void Decoder(){
  
  if(IrReceiver.decode()){   
    if(IrReceiver.decodedIRData.decodedRawData == IRButton1){
      Serial.println("Button 1 was pressed");
      button1=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton2){
      Serial.println("Button 2 was pressed");
      button2=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton3){
      Serial.println("Button 3 was pressed");
      button3=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton4){
      Serial.println("Button 4 was pressed");
      button4=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton5){
      Serial.println("Button 5 was pressed");
      button5=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton6){
      Serial.println("Button 6 was pressed");
      button6=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton7){
      Serial.println("Button 7 was pressed");
      button7=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton8){
      Serial.println("Button 8 was pressed");
      button8=1;
    }
    if(IrReceiver.decodedIRData.command == IRButton9){
      Serial.println("Button 9 was pressed");
      button9=1;
    }
    IrReceiver.resume(); // Continue receiving
  }
}
