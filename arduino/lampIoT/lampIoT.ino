// Introduce with clap clap
// Clap clap will have 2 graph left and right, I sended in my folder with name graphclapclap.xml
// I have 2 leftGraph and rightGraph to make sure it was clap clap
// If clap clap 
//    Each leftGraph/rightGraph have not more 5 paragram >0
//    Summurize  of number  leftGraph/rightGraph from 650->1500
//    |Max leftGraph - Max rightGraph| <250
//    The zero between LeftGraph and rightGraph not have more 3 number
//    and finally it look like a double moutain raise up and fall down complety
//So this is my code for that
// switchLeftGraph: notice if save to variable left

#include <MsTimer2.h>
#define CHA 3
int pinLed =13;
int pinLedMotion =12;
long analogSound = 0;
int numClap =0;
boolean stateLight = LOW ;
int index=0;
int tempIndex=-4;
int motionPin = 4;
int switchLeftGraph =1;

int leftGraph[6],rightGraph[6];
int indexLeft=0,indexRight=0;
int countTopLeftGraph=0,countTopRightGraph=0;

int matchGraph=1;


void setup() {
  // put your setup code here, to run once:
  pinMode(CHA, INPUT_PULLUP);
  pinMode(motionPin, INPUT_PULLUP);
  pinMode(pinLed,OUTPUT);  
  pinMode(pinLedMotion,OUTPUT);  

  attachInterrupt(1, encoder, RISING); 
  Serial.begin(115200); 
  MsTimer2::set(100, saveAnalogSound); // 5ms period
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
      analogSound+=1;
  }
int checkClap(int Amp){
  
}
int checkTop(int graph[6],int indexGraph){
  return (index>=3 && (graph[indexGraph-2]<graph[indexGraph-1]&&graph[indexGraph]<graph[indexGraph-1]));
}
void processAnalogSound(int analogSound,int *countTop,int *indexGraph,int graph[6]){
    if(*indexGraph<6){
       // Serial.println("Dang xu ly");
           if(*indexGraph>0){      
             if(*countTop>1) matchGraph=0;
             else{
                if(checkTop(graph,*indexGraph)){
                  (*countTop)++;
                }
                graph[(*indexGraph)++]=analogSound;
              //  Serial.println("Save");
             }
           }
           else{
            //  Serial.println(*indexGraph);
              graph[(*indexGraph)++]=analogSound;
             // Serial.println(*indexGraph);
           }
    }
    else matchGraph=0;
}

void resetValue(){
  indexLeft=0;
  indexRight=0;
  matchGraph=1;
  switchLeftGraph=1;
  countTopRightGraph=0;
  countTopLeftGraph=0;
}
void saveAnalogSound()
{

  if(analogSound <1000 && analogSound >0&& matchGraph){
    if(switchLeftGraph) processAnalogSound(analogSound,&countTopLeftGraph,&indexLeft,leftGraph);
    else  processAnalogSound(analogSound,&countTopRightGraph,&indexRight,rightGraph);
  }

  if(matchGraph==0){
    resetValue();
  }

  if(analogSound==0&&switchLeftGraph&&matchGraph&&indexLeft!=0){
    Serial.println("Begin");
    for(int i=0;i<indexLeft;i++){
      Serial.println(leftGraph[i]);
    }
    Serial.println("End");
  }
  analogSound=0;
}
