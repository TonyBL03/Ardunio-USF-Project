void(* resetFunc) (void) = 0;
//Defining connections for the motors
#define in1 3    //in1 (H-board) connected with 2 (Arduino)   Left
#define in2 5    //in2 (H-board) connected with 4 (Arduino)   Left                Probably change these values up here
#define in3 7    //in3 (H-board) connected with 7 (Arduino)   Right
#define in4 8    //in4 (H-board) connected with 8 (Arduino)   Right

//Definionnections for ultrasonic sensor
#define echoPin 9    //echo (Sensor) connected with PWM 9
#define trigPin 10   //trig (Sensor) connected with PWM 10
#define RESET 12     //restarts code

//
#define echoPinF A1    //echo (Sensor) connected with PWM 9
#define trigPinF A0   //trig (Sensor) connected with PWM 10

#include <Servo.h>
Servo myservo;

//Defining variables
long duration; //Long variable used to extend the amount of time the sensor records to properly measure the the speed of the wavelength when calculating distance
int distance; //variable for distance in centimeters
double Tim; //Time is in regards to miliseconds
int ang=0; //For Servo
int conWall=0;
int Left=0;
int Right=0;
double DWall=0;



//Defining variables for Front
long Fduration;
int Fdistance;
double FTim;
int Front=0;


void setup() 
{
 myservo.attach(11);
 myservo.write(45);
 pinMode (trigPin, OUTPUT);     //The trig pin on the Servo Sensor
 pinMode (echoPin, INPUT);      //The echo pin on the Servo Sensor
 pinMode (trigPinF, OUTPUT);    //The trig pin on the Front Sensor
 pinMode (echoPinF, INPUT);     //The echo pin on the Front Sensor
 pinMode (in1, OUTPUT);         //In1 on the H-Board; Used to spin the left motor in the same direction as In3
 pinMode (in2, OUTPUT); //       //In2 on the H-Board; Used to spin the left motor in the same direction as In4  INPUT
 pinMode (in3, OUTPUT);         //In3 on the H-Board; Used to spin the right motor in the same direction as In1
 pinMode (in4, OUTPUT);          //In4 on the H-Board; Used to spin the right motor in the same direction as In2 INPUT

 Serial.begin(9600);            //Launches the Serial Monitor in 9600 baud
 Serial.println("Launching..."); //Just to know when the program starts
 Serial.println("(Failsafe Ready)");
 delay(2000);

 //Methods
 FindWall();                    //Used to find object
 TurnToWall();                  //Turns the robot in the direction of the wall
 LRCompare();                   //Possibly scan to detect which direction will allow the robot to move 
 FollowWallSides();             //Wall following
 //More stuff                               The velocity is 3.989822670059037m/s (or 0.398982267005903668), the distance is found, and the time is t=d/v
}

double FindWall()
{
  do
  {
    myservo.write(ang);
    digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
    delay(10);                              //The delay
    digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
    delay(10);                              //Another delay
    digitalWrite(trigPin, LOW);             //Stops the Sensor
    duration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
    distance=duration*0.0343/2;             //Distance=Duration*Speed of Sound (in centimeters)/the delay that the trigPin writes (in microseconds)
    Serial.print("Distance: ");             //Print
    Serial.print(distance);                 //Print
    Serial.println(" cm");                  //Prints and has the printing in the Serial Monitor be on separate lines
    ang=ang+1;         
    delay (100);
  }
  while(ang<=135&&distance>=20);               //Change 40 to 20
    {
      if (distance<=20)                        //Change 40 to 20
      {
        ang=ang;
        Serial.print("Found nearby object: ");
        Serial.print(distance);
        Serial.print(" cm away at ");
        Serial.print(ang);
        Serial.println(" degrees");
        digitalWrite(trigPin, LOW);       //
        digitalWrite(echoPin, LOW);
        Serial.println("Scanning...paused");
        delay(1000);
        TurnToWall();
        Time();
        Approach();
      }
      if (ang>=135)
      {
        Serial.println("Task Failed: Reset");
        myservo.write(0);
        Serial.println("Repositioning Start...");
        Serial.println("Failsafe enabled");
        //Implement motors to either go foward by a little bit or spin to readjust itself
//       Realign ();
        resetFunc();
      }
    }
}

void TurnToWall()  //Used to change servo and readjust the motors
{
    if (ang>40&&ang<50)
  {
    Serial.println("Turning 45 degrees");
  analogWrite(in1,50);
  analogWrite(in4,50);
  delay(3);
  }
    if (ang>55&&ang<65)
  {
    Serial.println("Turning 30 degrees");
  analogWrite(in1,50);
  analogWrite(in4,50);
  delay(2);
  }
    if (ang>70&&ang<80)
  {
    Serial.println("Turning 15 degrees");
  analogWrite(in1,50);
  analogWrite(in4,50);
  delay(1);
  }
    if (ang>85&&ang<95)
  {
    //The only one that would be able to go forward; so nothing would happen
    Serial.println("Turning 0 degrees");
  }
    if (ang>100&&ang<110)
  {
    Serial.println("Turning 15 degrees");
  analogWrite(in2,50);
  analogWrite(in3,50);
  delay(1);
  }
    if (ang>115&&ang<125)
  {
    Serial.println("Turning 30 degrees");
  analogWrite(in2,50);
  analogWrite(in3,50);
  delay(2);
  }
    if (ang>130&&ang<140)
  {
    Serial.println("Turning 45 degrees");
  analogWrite(in2,50);
  analogWrite(in3,50);
  delay(3);
  }
}

void Time()
{
  //Basically use the distance given and divide by the velocity to find the time needed to determine how long the wheels should spin for


    digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
    Serial.println("Scanning distance to wall");
    delay(10);                              //The delay
    digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
    delay(10);                              //Another delay
    digitalWrite(trigPin, LOW);             //Stops the Sensor
    duration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  distance=duration*0.0343/2;  
  Tim=distance/0.398982267005903668;
  Serial.print("Distance to wall: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print(Tim*0.1);                    //Multiplied by 0.001
  Serial.println(" seconds to approach object");
}

void Approach()
{
  int Right=0;
  int Left=0;
  analogWrite(in1,250);
  analogWrite(in3,255);                   //           I think these are reversed but I would have to test it 
  delay(Tim*100);                  //either times 10 or 100
  analogWrite(in1,0);
  analogWrite(in3,0);
  delay(10);
  Serial.println("Here");
  Serial.println(distance);
  delay(1000);
  Serial.println(distance);
}

double LSide()
{
  myservo.write(135);
  digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
  Serial.println("Scanning distance to wall");
  delay(10);                              //The delay
  digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
  delay(10);                              //Another delay
  digitalWrite(trigPin, LOW);             //Stops the Sensor
  duration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  distance=duration*0.0343/2;  
  Tim=distance/0.398982267005903668;
  delay (500);
  Left=distance;
  delay(1000);
  myservo.write(90);
  Serial.println("Left Side Scanned");
  Serial.println(distance);
  return Left;
}
double RSide()
{
  myservo.write(45);
  digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
  Serial.println("Scanning distance to wall");
  delay(10);                              //The delay
  digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
  delay(10);                              //Another delay
  digitalWrite(trigPin, LOW);             //Stops the Sensor
  duration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  distance=duration*0.0343/2;  
  Tim=distance/0.398982267005903668;
  delay (500);
  Right=distance;
  delay(1000);
  myservo.write(90);
  Serial.println("Right Side Scanned");
  Serial.println(distance);
  return Right;
}

void LRCompare()
{
  LSide();
  RSide();
  if (Left>Right)  //Or unable to turn Right
  {
    Serial.println("Turning Left"); //I just put these to test but I do need to get the numbers at some point
    Serial.println(Left);
    Serial.println(Right);
    myservo.write(45);
    analogWrite(in1, 250);
    analogWrite(in4, 250);
    delay(500); //Approx of 45 degrees
    analogWrite(in1, 0);
    analogWrite(in4, 0);
  }
  if (Left<Right)  //Or unable to turn Left
  {
    Serial.println("Turning Right");   //This is where the motors will turn the robot to align parallel with the wall
    Serial.println(Left);
    Serial.println(Right);
    myservo.write(135);
    analogWrite(in2, 250);
    analogWrite(in3, 250);
    delay(5000);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
  }
  if (LSide==RSide)  //I might set it to turn another direction (back it up and rescan) if it does not have enough distance to turn in either direction
  {
    Serial.println("Confused");
    if (Left<20||Right<20)                                                                                          //Backs up if either left or right are less than 20, otherwise it automatically turns left
    {
      analogWrite(in2, 10);
      analogWrite(in4, 10);
      delay(100);
    }
    else
    {
    //Turn Left
    Serial.println("Turning Left"); //I just put these to test but I do need to get the numbers at some point
    Serial.println(Left);
    Serial.println(Right);
    myservo.write(45);
    analogWrite(in1, 250);
    analogWrite(in4, 250);
    delay(5000); //Approx of 45 degrees
    analogWrite(in1, 0);
    analogWrite(in4, 0);
    }
  }
}

void FollowWallSides()
{
  //Constant scanning of the wall, while constanly changing the speeds of the motors to maintain a distance from the wall
  FrontSensor();
  SideSensor();
  Serial.println(Front);
  if (Front<10)
  {
    Serial.println("Wall");
    Serial.print(Front);
    Serial.println(" cm left");
    delay(1000);
    //Put digitalWrite statements here to stop the robot so it can reasses
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 0); 
    LSide();
    RSide();
    LRCompare();
  }
  if (Front>10)
  {
    Serial.println("DA");
    Serial.print(Front);
    Serial.println(" cm left until Wall");
    analogWrite(in1,250);           //     forward motors
    analogWrite(in3,250);
  }
  //If the robot turned Right
  if (DWall>30&&Left<Right)
  {
//    digitalWrite();
//    digitalWrite();
    Serial.println("Shift towards wall");
  }
  if (DWall<10&&Left<Right)
  {
//    digitalWrite();
//    digitalWrite();  
    Serial.println("Shift away from wall");
  }
  if (DWall>40&&Left<Right)
  {
    LCorner();
  }
  //If the robot turned left
    if (DWall>30&&Right<Left)
  {
//    digitalWrite();
//    digitalWrite();
    Serial.println("Shift towards wall");
  }
  if (DWall<10&&Right<Left)
  {
//      digitalWrite();
//      digitalWrite();
    Serial.println("Shift away from wall");
  }
  if (DWall>40&&Right<Left)
  {
    RCorner();
  }
  
}

//Inside if-statements for Follow Wall Sides
void LCorner()
{
  //This is going to be if a corner is detected on the left, which will cause the robot to turn to the left to follow the corner
//  digitalWrite();
//  digitalWrite();
}

void RCorner()
{
  //Same as the other one but for the right side
//digitalWrite();
//digitalWrite();
}



double FrontSensor()
{
  //Checks forward
  digitalWrite(trigPinF, LOW);             //Doesn't trigger the Sensor
  Serial.println("Scanning distance to wall");
  delay(10);                              //The delay
  digitalWrite(trigPinF, HIGH);            //Triggers the Sensor and the ultrasonic pulses
  delay(10);                              //Another delay
  digitalWrite(trigPinF, LOW);             //Stops the Sensor
  Fduration=pulseIn(echoPinF, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  Fdistance=Fduration*0.0343/2;
  Front=Fdistance;
  FTim=Fdistance/0.398982267005903668;
  Serial.print("Distance to wall: ");
  Serial.print(Fdistance);
  Serial.println(" cm");
  Serial.print(FTim*0.1);                    //Multiplied by 0.001
  Serial.println(" seconds until collision");
  return Front;
}
double SideSensor()
{
  //Checks forward
  digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
  Serial.println("Scanning distance to wall");
  delay(10);                              //The delay
  digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
  delay(10);                              //Another delay
  digitalWrite(trigPin, LOW);             //Stops the Sensor
  duration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  distance=duration*0.0343/2;
  DWall=distance;
  Serial.print("Distance to wall@: ");
  Serial.print(distance);
  Serial.println(" cm");
  return DWall;
}




void loop() 
{
  //LCorner or RCorner statement
  FollowWallSides();
}
