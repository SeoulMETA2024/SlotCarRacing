int echo = 8;
int trig = 11;
unsigned long preTime = 0;
unsigned long nowTime = 0;

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


  
  if (/*센서작동할때*/) //이거 만들기!
  {
        preTime = nowTime;
        unsigned long nowTime = millis();
        int Time = nowTime - preTime ;
        char a[20];
        itoa(Time,a,10);
        //char b[] = "시간 측정 시작";
        //printf("%s\n",b);
      }

      
    }
  
  