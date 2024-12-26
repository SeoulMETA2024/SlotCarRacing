int echo = 8;
int trig = 11;
unsigned long preTime = 0;
unsigned long nowTime = 0;
float cycletime;
float nowdistance;
float predistance;
float carandwalldistance;

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
          int Time = nowTime - preTime ;
          char a[20];
          itoa(Time,a,10);
          //char b[] = "시간 측정 시작";
          //printf("%s\n",b);
      

  }

      
    }
  
  