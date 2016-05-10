#include "clapclap.h"
#include "iostream"
#include "math.h"
ClapClap::ClapClap(int pinSound,int  sum2GraphMin,int sum2GraphMax,int disparityTopGraph):sum2GraphMin(sum2GraphMin),sum2GraphMax(sum2GraphMax),disparityTopGraph(disparityTopGraph){}



int ClapClap::checkTop(GraphSound graphSound){
	if(graphSound.graph[graphSound.index]>graphSound.graph[graphSound.index-1])graphSound.top=graphSound.graph[graphSound.index];
  return (graphSound.index>=3 
  	&& (graphSound.graph[graphSound.index-2]<graphSound.graph[graphSound.index-1]
  	&&graphSound.graph[graphSound.index]<graphSound.graph[graphSound.index-1]));
}

int ClapClap::isMatch(){
  return analogSound==0&&switchLeftGraph==0&&matchGraph&&
   std::abs(leftGraph.top - rightGraph.top)<disparityTopGraph &&
   leftGraph.index>1&& leftGraph.index<6&&
   rightGraph.index>1&&rightGraph.index<6&&
   indexSound-checkIndexInGraph==1&&
   (leftGraph.sum+ rightGraph.sum)>sum2GraphMin&&(leftGraph.sum+ rightGraph.sum)<sum2GraphMax; 
}

void ClapClap::processAnalogSound(GraphSound graphSound){
	if(graphSound.index<6){
       // Serial.println("Dang xu ly");
					 if(graphSound.index==0){
						 //  Serial.println(*indexGraph);
              graphSound.graph[(graphSound.index)++]=analogSound;
              checkIndexInGraph= indexSound;
              graphSound.sum+=analogSound;
              graphSound.top=analogSound;
             // Serial.println(*indexGraph);
					 }else{      
             if(graphSound.countTop>1) matchGraph=0;
             else{
                if(checkTop(graphSound)){
                  graphSound.top=graphSound.graph[graphSound.index-1];
                  (graphSound.countTop)++;
                }
                
                graphSound.graph[graphSound.index++]=analogSound;
                checkIndexInGraph= indexSound;
                graphSound.sum+=analogSound;
              //  Serial.println("Save");
             }
           }
    }
    else matchGraph=0;
}


int ClapClap::checkClapClap(int analogSoundIn){
	  indexSound++;
    analogSound=analogSoundIn;
 // Serial.println(analogSound);
  if (analogSound< MAX_SOUND_CLAPCLAP && analogSound >0&& matchGraph){
    if ((indexSound-checkIndexInGraph)<=LENGTH_MIDDLE_GRAPS
    	&&(indexSound-checkIndexInGraph)>1&&switchLeftGraph==1){
      switchLeftGraph=0;
    }
    if(switchLeftGraph) processAnalogSound(leftGraph);
    else  processAnalogSound(rightGraph);
  }
  
  if(matchGraph==0||((indexSound-checkIndexInGraph)>4)){
    resetValue();
  }
  if(isMatch()){
    // Serial.println("Begin1");
    // for(int i=0;i<indexLeft;i++){
    //   Serial.println(leftGraph[i]);
    // }
    // Serial.println("End1");
    // Serial.println("Begin2");
    // for(int i=0;i<indexRight;i++){
    //   Serial.println(rightGraph[i]);
    // }
    // Serial.println("End2");
    // stateLight=!stateLight;
    // digitalWrite(pinLed,stateLight);
    resetValue();
    return 1;
  }

  analogSound=0;
  if(indexSound>300000) resetIndex();
  return 0;
}
void ClapClap::resetValue(){

}
void ClapClap::resetIndex(){
  indexSound=0;
}

