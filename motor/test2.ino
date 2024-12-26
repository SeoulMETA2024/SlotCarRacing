#include <Arduino.h>
#include <math.h>

/* 모터 제어 핀 */
#define CONTROL1 9
#define CONTROL2 8
#define SPEEDPIN 10

/* 버튼 핀 */
#define BUTTON 5

/* 초음파 센서 핀 */
#define ECHO 6
#define TRIG 7

/* 거리 상수 */
const float CAR_AND_WALL_DISTANCE = 10.0f; // 조정 필요

/* 모터 제어 */
const int THRESHOLD = 5000; // 0.5초
int speed = 0;
float oldTime = 0.0f;
float currentTime = 0.0f;
float deltaTime = 0.0f;

/* 상태 정의 */
enum State {
    StateWait,
    StateRun,
    StateArrive,
    StateReset,
};

enum State carState = StateWait;

/* 시간 */
unsigned long preTime = 0;
unsigned long nowTime = 0;

/* 거리 측정 */
float cycletime;
float nowdistance;

void setup() {
    Serial.begin(9600);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(SPEEDPIN, OUTPUT);
    pinMode(CONTROL1, OUTPUT);
    pinMode(CONTROL2, OUTPUT);

    pinMode(BUTTON, INPUT);

    digitalWrite(CONTROL1, LOW);
    digitalWrite(CONTROL2, LOW);
    analogWrite(SPEEDPIN, 0);
}

void loop() {
    /* 초음파 거리 측정 */
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    cycletime = pulseIn(ECHO, HIGH);
    nowdistance = ((340.0 * cycletime) / 10000.0) / 2.0; // 거리 계산 (cm)

    Serial.print("Distance: ");
    Serial.print(nowdistance);
    Serial.println(" cm");

    /* 상태 머신 */
    switch (carState) {
        case StateWait: {
            int buttonState = digitalRead(BUTTON);
            if (buttonState == HIGH) {
                carState = StateRun;
                oldTime = millis();
                preTime = millis();
                break;
            }
            break;
        }

        case StateRun: {
            int buttonState = digitalRead(BUTTON);
            if (buttonState == HIGH) {
                oldTime = currentTime;
                currentTime = millis();
                deltaTime = currentTime - oldTime;

                float x = THRESHOLD - deltaTime;
                if (x <= 0) x = 0;

                int y = (int)(70 * log(x + 1)); // 속도 계산, 계수 조정 가능
                speed = constrain(y, 0, 255);  // 속도 제한

                digitalWrite(CONTROL1, HIGH);
                digitalWrite(CONTROL2, LOW);
                analogWrite(SPEEDPIN, speed);
            } else {
                // 버튼이 눌리지 않았을 때 서서히 감소
                if (speed > 0) {
                    speed -= 1; // 감소 속도 조정 가능
                    digitalWrite(CONTROL1, HIGH);
                    digitalWrite(CONTROL2, LOW);
                    analogWrite(SPEEDPIN, speed);
                } else {
                    digitalWrite(CONTROL1, LOW);
                    digitalWrite(CONTROL2, LOW);
                    analogWrite(SPEEDPIN, 0);
                }
            }

            if (nowdistance < CAR_AND_WALL_DISTANCE) {
                carState = StateArrive;
            }
            break;
        }

        case StateArrive: {
                digitalWrite(CONTROL1, HIGH);
                digitalWrite(CONTROL2, LOW);
                analogWrite(SPEEDPIN, 50);

            if (nowdistance < CAR_AND_WALL_DISTANCE) {
                unsigned long currentMillis = millis();
                unsigned long elapsedTime = currentMillis - preTime;
                Serial.print("Elapsed Time: ");
                Serial.print(elapsedTime);
                Serial.println(" ms");
                digitalWrite(CONTROL1, LOW);
                digitalWrite(CONTROL2, LOW);
                analogWrite(SPEEDPIN, 0);
                carState = StateReset;
            }
            delay(1000);
            break;
        }

        case StateReset: {
            if (nowdistance < CAR_AND_WALL_DISTANCE) {
                digitalWrite(CONTROL1, LOW);
                digitalWrite(CONTROL2, HIGH);
                analogWrite(SPEEDPIN, 50); // 천천히 후진
            } else {
                digitalWrite(CONTROL1, LOW);
                digitalWrite(CONTROL2, LOW);
                analogWrite(SPEEDPIN, 0);
                carState = StateWait;
            }
            delay(1000);
            break;
        }
    }
}
