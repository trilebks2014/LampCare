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
int checkIndexInGraph;
int motionPin = 4;
int switchLeftGraph =1;

int leftGraph[6],rightGraph[6];
int indexLeft=0,indexRight=0;
int countTopLeftGraph=0,countTopRightGraph=0;
int maxLeftGraph=0,maxRightGraph=0;
int matchGraph=1;
int sumLeft=0,sumRight=0;

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
int checkTop(int graph[6],int *maxGraph,int indexGraph){
  if(graph[indexGraph]>graph[indexGraph-1])*maxGraph=graph[indexGraph];
  return (index>=3 && (graph[indexGraph-2]<graph[indexGraph-1]&&graph[indexGraph]<graph[indexGraph-1]));
}
void processAnalogSound(int analogSound,int *countTop,int *indexGraph,int *maxGraph,int *sumGraph,int graph[6]){
    if(*indexGraph<6){
       // Serial.println("Dang xu ly");
           if(*indexGraph>0){      
             if(*countTop>1) matchGraph=0;
             else{
                if(checkTop(graph,maxGraph,*indexGraph)){
                  *maxGraph=graph[(*indexGraph)-1];
                  (*countTop)++;
                }
                
                graph[(*indexGraph)++]=analogSound;
                checkIndexInGraph= index;
                *sumGraph+=analogSound;
              //  Serial.println("Save");
             }
           }
           else{
            //  Serial.println(*indexGraph);
              graph[(*indexGraph)++]=analogSound;
              checkIndexInGraph= index;
              *sumGraph+=analogSound;
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
  index=0;
  maxLeftGraph=0;
  maxRightGraph=0;
  sumLeft=0;
  sumRight=0;

}
int isMatch(){
  return analogSound==0&&switchLeftGraph==0&&matchGraph&& abs(maxLeftGraph - maxRightGraph)<250 && indexLeft>1&& indexLeft<6&&indexRight>1&&indexRight<6&&index-checkIndexInGraph==1&&(sumLeft+sumRight)>1000&&(sumLeft+sumRight)<2800; 
}
void saveAnalogSound()
{
  index ++;
  Serial.println(analogSound);
  if(analogSound <1000 && analogSound >0&& matchGraph){
    if((index-checkIndexInGraph)<=3&&(index-checkIndexInGraph)>1&&switchLeftGraph==1){
      switchLeftGraph=0;
      Serial.println("Switch:");
      Serial.println("Begin1");
      for(int i=0;i<indexLeft;i++){
        Serial.println(leftGraph[i]);
      }
      Serial.println("End1");
    }
    if(switchLeftGraph) processAnalogSound(analogSound,&countTopLeftGraph,&indexLeft,&maxLeftGraph,&sumLeft,leftGraph);
    else  processAnalogSound(analogSound,&countTopRightGraph,&indexRight,&maxLeftGraph,&sumRight,rightGraph);
  }
  
  if(matchGraph==0||((index-checkIndexInGraph)>3)){
    resetValue();
  }
  

  if(isMatch()){
    Serial.println("Begin1");
    for(int i=0;i<indexLeft;i++){
      Serial.println(leftGraph[i]);
    }
    Serial.println("End1");
    Serial.println("Begin2");
    for(int i=0;i<indexRight;i++){
      Serial.println(rightGraph[i]);
    }
    Serial.println("End2");
    stateLight=!stateLight;
    digitalWrite(pinLed,stateLight);
  }

  analogSound=0;
  
}
