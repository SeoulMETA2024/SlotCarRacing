
#include <stdio.h>
#include <math.h>

/*모터제어*/
#define control1 9
#define control2 8 
#define speedpin 10
#define button 8

/*버튼*/
int buttonState = 0;


/*초음파*/
int echo = 6;//핀 지정하기
int trig = 7;
unsigned long preTime = 0;
unsigned long nowTime = 0;
float cycletime;
float nowdistance;
const float CAR_AND_WALL_DISTANCE = 10;//차와 벽 사이의 길이 보단 길고, 센서와 벽사이의 길이보단 짧아야함!, 상수조정하기!

/*모터제어*/
const int THRESHOLD = 5000; // 임계값 0.5초
int speed = 200;
float oldTime = 0.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;

enum State {
    StateWait,
    StateRun,
    StateArrive,
    StateReset,
};

enum State carState = StateWait;


void setup() {
    Serial.begin(9600);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(speedpin, OUTPUT);
    pinMode(control1, OUTPUT);
    pinMode(control2, OUTPUT);
    pinMode(button, INPUT);
    
    digitalWrite(control1, LOW);
    digitalWrite(control2, LOW);
    analogWrite(speedpin, 0);
}

void loop() {


    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);
  
    cycletime = pulseIn(echo, HIGH);
 
  
    nowdistance = ((340 * cycletime) / 10000) / 2;  

    Serial.print("Distance:");//test
    Serial.print(nowdistance);
    Serial.println("cm"); 


    //Serial.print('buttonState:');
    //Serial.println(buttonState);

   //Serial.print('speed:');
    //Serial.println(speed);
    
    
      







    switch (carState) {
      case StateWait:    
          int buttonState = digitalRead(button);

          if (buttonState == HIGH) {
              carState = StateRun;
              oldTime = currentTime; //생각더하기
              
              break;
          }
          break;





      case StateRun:

          
          preTime = millis();
          buttonState = digitalRead(button);
          if (buttonState == HIGH){
              oldTime = currentTime;
              currentTime = millis();
              deltaTime = currentTime - oldTime;

              float x = THRESHOLD - deltaTime;
              if (x <= 0) {
                  break;
              }

              int y = (int)70*log(x+1) ;//계수 조정
              speed = constrain(y, 0, 255); // 속도값 범위 제한,계수조정

              digitalWrite(control1, HIGH);
              digitalWrite(control2, LOW);
              analogWrite(speedpin, speed);
              
              //Serial.print("Speed: ");
              //Serial.println(speed);
          } else {
              // 버튼이 눌리지 않았을 때 모터 속도 서서히 감소
              if (speed <= 0) {
                  digitalWrite(control1, LOW);
                  digitalWrite(control2, LOW);
                  analogWrite(speedpin, 0);
                  break;
              }

              speed = speed - 1;  // 감소량 조절 가능
              digitalWrite(control1, HIGH);
              digitalWrite(control2, LOW);
              analogWrite(speedpin, speed);
          }

          if(nowdistance < CAR_AND_WALL_DISTANCE ){
              carState = StateArrive; }
          break;







      case StateArrive:
      //기록재는 함수 종료,이름 input,기록 띄우기
          /*차 멈추기*/
          

              
              unsigned long nowTime = millis();

              float Time = floor(nowTime) - floor(preTime) ;
              char a[20];
              itoa(Time,a,10);
              Serial.println(a);
              //char b[] = "시간 측정 시작";
              //printf("%s\n",b);
        

    

          if(nowdistance < CAR_AND_WALL_DISTANCE){
              digitalWrite(control1, LOW);
              digitalWrite(control2, LOW);
              analogWrite(speedpin, 0);
              carState = StateReset;}

          delay(1000);
          break;







      case StateReset:
          if(nowdistance < CAR_AND_WALL_DISTANCE){
              digitalWrite(control1, LOW);
              digitalWrite(control2, HIGH);
              analogWrite(speedpin, 5);
              break;
          }
          
          carState = StateWait;
          
          delay(1000);
          break;
      }


}
