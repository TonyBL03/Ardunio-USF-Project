void(* resetFunc) (void) = 0;
//Defining connections for the motors
#define in1 2    //in1 (H-board) connected with 2 (Arduino)   Left
#define in2 4    //in2 (H-board) connected with 4 (Arduino)   Left
#define in3 7    //in3 (H-board) connected with 7 (Arduino)   Right
#define in4 8    //in4 (H-board) connected with 8 (Arduino)   Right

//Defining connections for ultrasonic sensor
#define echoPin 9    //echo (Sensor) connected with PWM 9
#define trigPin 10   //trig (Sensor) connected with PWM 10
#define RESET 12     //restarts code

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

//Array time baby
//double aArray[2];
//double ReturnStartDist(double aArray[]);

void setup() 
{
 myservo.attach(11);
 myservo.write(0);
 pinMode (trigPin, OUTPUT);     //The trig pin on the Sensor
 pinMode (echoPin, INPUT);      //The echo pin on the Sensor
 pinMode (in1, OUTPUT);         //In1 on the H-Board; Used to spin the left motor in the same direction as In3
 pinMode (in2, OUTPUT); //       //In2 on the H-Board; Used to spin the left motor in the same direction as In4  INPUT
 pinMode (in3, OUTPUT);         //In3 on the H-Board; Used to spin the right motor in the same direction as In1
 pinMode (in4, OUTPUT);          //In4 on the H-Board; Used to spin the right motor in the same direction as In2 INPUT

 Serial.begin(9600);            //Launches the Serial Monitor in 9600 baud
 Serial.println("Launching..."); //Just to know when the program starts
 Serial.println("(Failsafe Ready)");
 delay(2000);

 //Methods
 FindWall();           //Used only when an object is not located
 TurnToWall();
 Time();
 Approach();
 LRCompare();                                           //Possibly scan to detect which direction will allow the robot to move 
 FollowWallSides();
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
  while(ang<=180&&distance>=20);               //Change 40 to 20
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
      if (ang>=170)
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
  if (ang==0)
  {
    //The robot would have to turn 90 degrees, so only left motor would need to spin forward or both would need to spin the same distance
  }
    if (ang>=10||ang<20)
  {
    
  }
    if (ang>25||ang<35)
  {
  
  }
    if (ang>40||ang<50)
  {
  
  }
    if (ang>55||ang<65)
  {
  
  }
    if (ang>70||ang<80)
  {
  
  }
    if (ang>85||ang<95)
  {
    //The only one that would be able to go forward
  }
    if (ang>100||ang<110)
  {
  
  }
    if (ang>115||ang<125)
  {
  
  }
    if (ang>130||ang<140)
  {
  
  }
    if (ang>145||ang<155)
  {
  
  }
    if (ang>160)
  {
  
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
  digitalWrite(in2, HIGH);   //Left
  digitalWrite(in3, HIGH);   //Right
  delay(Tim*10);                  //either times 10 or 100
  digitalWrite(in2, LOW);   //Left
  digitalWrite(in3, LOW);   //Right
  delay(10);
  Serial.println("Here");
  Serial.println(distance);
  delay(1000);
  Serial.println(distance);
//  LSide();
//  RSide();
//  LRSide();
//  LRCompare();
}

double LSide()
{
  myservo.write(170);
    digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
    Serial.println("Scanning distance to wall");
    delay(10);                              //The delay
    digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
    delay(10);                              //Another delay
    digitalWrite(trigPin, LOW);             //Stops the Sensor
    duration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
    distance=duration*0.0343/2;  
    Tim=distance/0.398982267005903668;
  delay (2000);
  Left=distance;
  delay(1000);
  myservo.write(90);
  Serial.println("Left Side Scanned");
  Serial.println(distance);
  delay(3000);
  return Left;
}
double RSide()
{
  myservo.write(50);
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
    myservo.write(0);
    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);
    delay(1000); //Approx of 45 degrees
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);
  }
  if (Left<Right)  //Or unable to turn Left
  {
    Serial.println("Turning Right");   //This is where the motors will turn the robot to align parallel with the wall
    Serial.println(Left);
    Serial.println(Right);
    myservo.write(180);
    digitalWrite(in4, HIGH);
    digitalWrite(in2, HIGH);
    delay(1000);
    digitalWrite(in4, LOW);
    digitalWrite(in2, LOW);
  }
}

void FollowWallSides()
{
  //Constant scanning of the wall, while constanly changing the speeds of the motors to maintain a distance from the wall
  
}

void LCorner()
{
  //This is going to be for another sensor or for this one to periodically scan in front of it, so it can turn based upon distance
  
  
}

void RCorner()
{
  //Same as the other one but I might put these into the loop
}

void loop() 
{
  //LCorner or RCorner statement
  FollowWallSides();
}