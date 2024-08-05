//This is the code for the robot                                        
// make sure to  include the NewPing and Servo Libraries  before uploading else it will show error  
// this code is compatible with Robot shield v0.1 design by Shubham Suresh @S-TROniX_Technologies.
// for more details about Robot Shield V0.1 & V0.2 E-mail:- stronixtechnologies@gmail.com
// code modified on 02-05-2020.
#include <NewPing.h> 
#include <Servo.h>   
#define TRIG_PIN 7  
#define ECHO_PIN 4  
#define MAX_DISTANCE 200  
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);  
Servo myservo;     
boolean goesForward=false; 
int distance = 100; 
int speedSet = 0;  
const int RmotorPin1  = 8;   
const int RmotorPin2  = 9;   
//Motor B 
const int LmotorPin3  = 11;  
const int LmotorPin4  = 10;    
void setup() {  
  pinMode(RmotorPin1,OUTPUT);
   pinMode(RmotorPin2,OUTPUT); 
    pinMode(LmotorPin3,OUTPUT); 
     pinMode(LmotorPin4,OUTPUT);    

  myservo.attach(3);   
  myservo.write(115);  
  delay(2000); 
  distance = readPing(); 
  delay(100); 
  distance = readPing(); 
  delay(100); 
  distance = readPing(); 
  delay(100); 
  distance = readPing(); 
  delay(100); 
}  
void loop() { 
 int distanceR = 0; 
 int distanceL =  0; 
 delay(40); 
  
 if(distance<=20) 
 { 
  moveStop(); 
  delay(100); 
  moveBackward(); 
  delay(600); 
  moveStop(); 
  delay(200); 
  distanceR = lookRight(); 
  delay(200); 
  distanceL = lookLeft(); 
  delay(200);  
  if(distanceR>=distanceL) 
  { 
    turnRight(); 
    moveStop(); 
  }else 
  { 
    turnLeft(); 
    moveStop(); 
  } 
 }else 
 { 
  moveForward(); 
 } 
 distance = readPing(); 
}  
int lookRight() 
{ 
    myservo.write(50);  
    delay(500); 
    int distance = readPing(); 
    delay(100); 
    myservo.write(115);  
    return distance; 
}  
int lookLeft() 
{ 
    myservo.write(170);  
    delay(500); 
    int distance = readPing(); 
    delay(100); 
    myservo.write(115);  
    return distance; 
    delay(100); 
}  
int readPing() {  
  delay(70); 
  int cm = sonar.ping_cm(); 
  if(cm==0) 
  { 
    cm = 250; 
  } 
  return cm; 
}  
void moveStop() { 
  digitalWrite(RmotorPin1, LOW); 
    digitalWrite(RmotorPin2, LOW); 
    digitalWrite(LmotorPin3, LOW); 
    digitalWrite(LmotorPin4, LOW); 
  }  
   
void moveForward() {   
    digitalWrite(RmotorPin1, HIGH); //the value 230 here is a PWM so you can change it depending ip on your motor speed
    digitalWrite(RmotorPin2, LOW); 
    digitalWrite(LmotorPin3, HIGH); // this one too
    digitalWrite(LmotorPin4, LOW);   
   
}  
void moveBackward() { 
     
    digitalWrite(RmotorPin1,LOW); 
    digitalWrite(RmotorPin2, HIGH);
    digitalWrite(LmotorPin3, LOW); 
    digitalWrite(LmotorPin4, HIGH);    
   
}    
void turnRight() { 
 digitalWrite(RmotorPin1, HIGH); 
    digitalWrite(RmotorPin2, LOW); 
  digitalWrite(LmotorPin3, LOW); 
    digitalWrite(LmotorPin4, HIGH);     
  delay(500); 
 moveForward();       
   
}  
  
void turnLeft() { 
  digitalWrite(RmotorPin1, LOW); 
    digitalWrite(RmotorPin2, HIGH);    
 digitalWrite(LmotorPin3, HIGH); 
    digitalWrite(LmotorPin4, LOW);      
  delay(400); 
   moveForward(); 
}
