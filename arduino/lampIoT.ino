#include <MsTimer2.h>
#define CHA 3
int pinLed =13;
int pinLedMotion =12;
long count = 0;
int numClap =0;
boolean stateLight = LOW ;
int index=0;
int tempIndex=-4;

int motionPin = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(CHA, INPUT_PULLUP);
  pinMode(motionPin, INPUT_PULLUP);
  pinMode(pinLed,OUTPUT);  
  pinMode(pinLedMotion,OUTPUT);  

  attachInterrupt(1, encoder, RISING); 
  Serial.begin(115200); 
  MsTimer2::set(100, rate); // 5ms period
    MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(motionPin) ==1){
   // Serial.println("Co chuyen dong");
    digitalWrite(pinLedMotion,HIGH);

    
  }else{
     digitalWrite(pinLedMotion,LOW);
  }
}

void encoder()
  {
      count+=1;
  }
int checkClap(int Amp){
  
}
void rate()
{
  Serial.println(count);
  if(count <500 && count >0){
    if((index- tempIndex)<=3&&(index-tempIndex)>2){
      stateLight = !stateLight;
      digitalWrite(pinLed,stateLight);
    }else{
      tempIndex=index;
    }
  }
  index++;
  if(index>5000)index=0;
  count=0;
}