int echo = 8;
int trig = 11;



void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  float cycletime;
  float distance;

  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  cycletime = pulseIn(echo, HIGH);

  distance = ((340 * cycletime) / 10000) / 2;

  //Serial.print("Distance:");
  Serial.println(distance);
  //Serial.print("cm");
  delay(500);


  
  if (distance >= 10)  //거리가 트랙 너비일때
  {
    unsigned long preTime = millis();
    char b[] = "시간 측정 시작";
    //printf("%s\n",b);
  }
  if (distance < 10) {
    unsigned long nowTime = millis();
    char a[20];
    int Time = nowTime - preTime;
    itoa(Time, a, 10);
    //printf("%s\n",a)
  }
}