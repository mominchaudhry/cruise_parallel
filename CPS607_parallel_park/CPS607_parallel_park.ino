#include <Servo.h>
Servo myservo;

int Echo = A4;  
int Trig = A5;

#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

int carSpeed = 150;
int carV = 0;
int distanceC = 0, oldDistanceC = 0;
int deltac = 0;
float rd = 100.0, ld = 100.0, md = 100.0;
int deltad = 100;
int l = 0, m = 0, r = 0;
int l1 = 0;
int countL = 0;
int countR = 0;
bool still = false;
int angle = 90;
int stuck1 = 0;
int stuck2 = 0;
int lane = 0;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0; 
const long interval = 100; 

unsigned long curr2 = 0;
unsigned long prev2 = 0; 
const long interval2 = 500;

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, 225);
  analogWrite(ENB, 225);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, 225);
  analogWrite(ENB, 225);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return Fdistance;
}  

void setup(){
    myservo.attach(3,700,2400);
    Serial.begin(9600);
    pinMode(10,INPUT);
    pinMode(4,INPUT);
    pinMode(2,INPUT);
    pinMode(Echo, INPUT);    
    pinMode(Trig, OUTPUT);  
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    stop();
}

void loop() { 
    myservo.write(0);

    forward();
    delay(900);
    md = Distance_test();
    while(md > 10) {
      md = Distance_test();
      forward();
    }
    stop();
    back();
    delay(400);
    myservo.write(90);
    right();
    delay(600);
    while (!LT_M && !LT_L && !LT_R) {
      forward();
    }
    delay(450);
    
    left();
    delay(400);
    while (!LT_M) {
      left();
    }
    stop();
    md = Distance_test();
    delay(100);
    while(md > 4) {
      forward();
      md = Distance_test();
    }
    while (md < 4) {
      back();
      md = Distance_test();
    }
    stop();
    exit(0);
}
