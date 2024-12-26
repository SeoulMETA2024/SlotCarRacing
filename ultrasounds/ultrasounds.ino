
#include <math.h>
int echo = ?;//핀 지정하기
int trig = 11;
unsigned long preTime = 0;
unsigned long nowTime = 0;
float cycletime;
float nowdistance;
float predistance;
float carandwalldistance;//차와 벽 사이의 길이 보단 길고, 센서와 벽사이의 길이보단 짧아야함!

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  
  
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  
  cycletime = pulseIn(echo, HIGH);
  predistance = nowdistance; 
  
  nowdistance = ((340 * cycletime) / 10000) / 2;  

  //Serial.print("Distance:");
  //Serial.println(distance);
  //Serial.print("cm"); 
  delay(500);


  if(predistance <carandwalldistance && nowdistance >carandwalldistance ){
    
    
          preTime = nowTime;
          unsigned long nowTime = millis();

          float Time = floor(nowTime) - floor(preTime) ;
          char a[20];
          itoa(Time,a,10);
          Serial.println(a);
          //char b[] = "시간 측정 시작";
          //printf("%s\n",b);
      

  }

      
    }
  
  