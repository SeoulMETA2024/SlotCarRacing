// 핀 정의
#define ECHO_PIN 6       // 초음파 센서 ECHO 핀
#define TRIG_PIN 7       // 초음파 센서 TRIG 핀
#define ENA 10           // 모터 속도 제어 핀 (PWM)
#define DIR1 9           // 모터 방향 제어 핀 1
#define DIR2 8           // 모터 방향 제어 핀 2
#define BUTTON_PIN 5     // 버튼 입력 핀

void setup() {
  // 핀 모드 설정
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 버튼을 풀업 입력으로 설정

  // 초기화
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  analogWrite(ENA, 0);

  Serial.begin(9600); // 시리얼 모니터용
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN); // 버튼 상태 읽기
  long distance = measureDistance();        // 초음파 센서로 거리 측정

  if (buttonState == LOW) { // 버튼이 눌렸을 때 (LOW는 풀업 상태에서 버튼이 눌린 상태)
    if (distance > 20) { // 거리가 20cm보다 클 때 전진
      motorForward(200); // 속도 200
    } else { // 거리가 20cm 이하일 때 정지
      motorStop();
    }
  } else { // 버튼이 눌리지 않았을 때
    motorStop();
  }

  delay(100); // 짧은 대기 시간
}

// 초음파 센서로 거리 측정
long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH); // 초음파 신호가 돌아오는 시간 측정
  long distance = duration * 0.0343 / 2;  // cm로 변환
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// 모터 전진
void motorForward(int speed) {
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  analogWrite(ENA, speed);
}

// 모터 정지
void motorStop() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  analogWrite(ENA, 0);
}
