#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#define control1 7
#define control2 8 
#define speedpin 6
#define button 9

const int THRESHOLD = 500; // 임계값 0.5초
int speed = 200;
float oldTime = 0.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;

void setup() {
    pinMode(speedpin, OUTPUT);
    pinMode(control1, OUTPUT);
    pinMode(control2, OUTPUT);
    pinMode(button, INPUT);
    
    digitalWrite(control1, LOW);
    digitalWrite(control2, LOW);
    analogWrite(speedpin, 0);
    
    Serial.begin(9600);
}

void loop() {
    int buttonState = digitalRead(button);
    
    if (buttonState == HIGH) {
        oldTime = currentTime;
        currentTime = millis();
        deltaTime = currentTime - oldTime;
        
        // 로그 함수를 이용한 속도 제어
        float x = THRESHOLD - deltaTime;
        if(x > 0) {
            int y = (int)log(x*100) ;//계수 조정
            speed = constrain(y*255, 0, 255); // 속도값 범위 제한,계수조정
            


            digitalWrite(control1, HIGH);
            digitalWrite(control2, LOW);
            analogWrite(speedpin, speed);
            
            //Serial.print("Speed: ");
            //Serial.println(speed);
        }
    } else {
        if(buttonState == HIGH){
                // 버튼이 눌리지 않았을 때 모터 속도 서서히 감소
                if(speed > 0) {
                    speed = speed - 1;  // 감소량 조절 가능
                    digitalWrite(control1, HIGH);
                    digitalWrite(control2, LOW);
                    analogWrite(speedpin, speed);
                } else {
                    digitalWrite(control1, LOW);
                    digitalWrite(control2, LOW);
                    analogWrite(speedpin, 0);
                }
        }
    }
}
