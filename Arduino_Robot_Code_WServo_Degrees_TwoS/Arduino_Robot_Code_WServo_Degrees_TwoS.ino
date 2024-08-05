void(* resetFunc) (void) = 0;
//Defining connections for the motors
#define in1 3    //in1 (H-board) connected with 2 (Arduino)   Left
#define in2 5    //in2 (H-board) connected with 4 (Arduino)   Left
#define in3 6    //in3 (H-board) connected with 7 (Arduino)   Right
#define in4 8    //in4 (H-board) connected with 8 (Arduino)   Right

//Defining connections for ultrasonic sensor
//Going to have to define pins for the new sensor

//#define
//#define

#define echoPin 9    //echo (Sensor) connected with PWM 9
#define trigPin 10   //trig (Sensor) connected with PWM 10
#define ECHOPIN 9
#define TRIGPIN 10
#define RESET 12     //restarts code

#include <Servo.h>
Servo myservo;

//Defining variables regarding the Swivel Servo
long Sduration; //Long variable used to extend the amount of time the sensor records to properly measure the the speed of the wavelength when calculating distance
int Sdistance; //variable for distance in centimeters
double STim; //Time is in regards to miliseconds
int Sang=0; //For Swivel Servo
int conWall=0;
int SLeft=0;
int SRight=0;

//Defining variables regarding the Front Servo
long Fduration; //Long variable used to extend the amount of time the sensor records to properly measure the the speed of the wavelength when calculating distance
int Fdistance; //variable for distance in centimeters
double FTim; //Time is in regards to miliseconds
int Fang=0; //For Swivel Servo


void setup() 
{
 myservo.attach(11);
 myservo.write(0);
 pinMode (trigPin, OUTPUT);     //The trig pin on the Swivel Sensor
 pinMode (echoPin, INPUT);      //The echo pin on the Swivel Sensor
 pinMode (TRIGPIN, OUTPUT);     //The trig pin on the Front Sensor
 pinMode (ECHOPIN, INPUT);      //The echo pin on the Front Sensor
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
 Front();
 FollowWallSides();
 //More stuff                               The velocity is 3.989822670059037m/s (or 0.398982267005903668), the distance is found, and the time is t=d/v
}

double FindWall()
{
  do
  {
    myservo.write(Sang);
    digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
    delay(10);                              //The delay
    digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
    delay(10);                              //Another delay
    digitalWrite(trigPin, LOW);             //Stops the Sensor
    Sduration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
    Sdistance=Sduration*0.0343/2;             //Distance=Duration*Speed of Sound (in centimeters)/the delay that the trigPin writes (in microseconds)
    Serial.print("Distance: ");             //Print
    Serial.print(Sdistance);                 //Print
    Serial.println(" cm");                  //Prints and has the printing in the Serial Monitor be on separate lines
    Sang=Sang+1;         
    delay (100);
  }
  while(Sang<=170&&Sdistance>=20);               //Change 40 to 20
    {
      if (Sdistance<=20)                        //Change 40 to 20
      {
        Sang=Sang;
        Serial.print("Found nearby object: ");
        Serial.print(Sdistance);
        Serial.print(" cm away at ");
        Serial.print(Sang);
        Serial.println(" degrees");
        digitalWrite(trigPin, LOW);       //
        digitalWrite(echoPin, LOW);
        Serial.println("Scanning...paused");
        delay(1000);
        TurnToWall();
        Time();
        Approach();
      }
      if (Sang>=170)
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
  if (Sang==0)
  {
    //The robot would have to turn 90 degrees, so only left motor would need to spin forward or both would need to spin the same distance
  }
    if (Sang>=10||Sang<20)
  {
    
  }
    if (Sang>25||Sang<35)
  {
  
  }
    if (Sang>40||Sang<50)
  {
  
  }
    if (Sang>55||Sang<65)
  {
  
  }
    if (Sang>70||Sang<80)
  {
  
  }
    if (Sang>85||Sang<95)
  {
    //The only one that would be able to go forward
  }
    if (Sang>100||Sang<110)
  {
  
  }
    if (Sang>115||Sang<125)
  {
  
  }
    if (Sang>130||Sang<140)
  {
  
  }
    if (Sang>145||Sang<155)
  {
  
  }
    if (Sang>160)
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
    Sduration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  Sdistance=Sduration*0.0343/2;  
  STim=Sdistance/0.398982267005903668;
  Serial.print("Distance to wall: ");
  Serial.print(Sdistance);
  Serial.println(" cm");
  Serial.print(STim*0.1);                    //Multiplied by 0.001
  Serial.println(" seconds to approach object");
}

void Approach()
{
  int SRight=0;
  int SLeft=0;
  digitalWrite(in2, HIGH);   //Left
  digitalWrite(in3, HIGH);   //Right                              I think these are reversed since 
  delay(STim*100);                  //either times 10 or 100
  digitalWrite(in2, LOW);   //Left
  digitalWrite(in3, LOW);   //Right
  delay(10);
  Serial.println("Here");
  Serial.println(Sdistance);
  delay(1000);
  Serial.println(Sdistance);
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
    Sduration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
    Sdistance=Sduration*0.0343/2;  
    STim=Sdistance/0.398982267005903668;
  delay (2000);
  SLeft=Sdistance;
  delay(1000);
  myservo.write(90);
  Serial.println("Left Side Scanned");
  Serial.println(Sdistance);
  delay(3000);
  return SLeft;
}
double RSide()
{
  myservo.write(10);
    digitalWrite(trigPin, LOW);             //Doesn't trigger the Sensor
    Serial.println("Scanning distance to wall");
    delay(10);                              //The delay
    digitalWrite(trigPin, HIGH);            //Triggers the Sensor and the ultrasonic pulses
    delay(10);                              //Another delay
    digitalWrite(trigPin, LOW);             //Stops the Sensor
    Sduration=pulseIn(echoPin, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
    Sdistance=Sduration*0.0343/2;  
    STim=Sdistance/0.398982267005903668;
  delay (500);
  SRight=Sdistance;
  delay(1000);
  myservo.write(90);
  Serial.println("Right Side Scanned");
  Serial.println(Sdistance);
  return SRight;
}

void LRCompare()
{
  LSide();
  RSide();
  if (SLeft>SRight)  //Or unable to turn Right
  {
    Serial.println("Turning Left"); //I just put these to test but I do need to get the numbers at some point
    Serial.println(SLeft);
    Serial.println(SRight);
    myservo.write(0);
    digitalWrite(in1, 100);
    digitalWrite(in3, 100);
    delay(1000); //Approx of 45 degrees
    digitalWrite(in1, 0);
    digitalWrite(in3, 0);
  }
  if (SLeft<SRight)  //Or unable to turn Left
  {
    Serial.println("Turning Right");   //This is where the motors will turn the robot to align parallel with the wall
    Serial.println(SLeft);
    Serial.println(SRight);
    myservo.write(180);
    digitalWrite(in4, HIGH);
    digitalWrite(in2, 250);
    delay(1000);
    digitalWrite(in4, 0);
    digitalWrite(in2, 0);
  }
/*  if (LSide=RSide)  //I might set it to turn another direction (back it up and rescan) if it does not have enough distance to turn in either direction
  {
    Serial.println("Confused");
  }
  else
  {
    Serial.println("It works????");
    Serial.println(RSide);
  }*/
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

void Front()
{
    digitalWrite(TRIGPIN, LOW);             //Doesn't trigger the Sensor
    Serial.println("Scanning distance to wall");
    delay(10);                              //The delay
    digitalWrite(TRIGPIN, HIGH);            //Triggers the Sensor and the ultrasonic pulses
    delay(10);                              //Another delay
    digitalWrite(TRIGPIN, LOW);             //Stops the Sensor
    Fduration=pulseIn(ECHOPIN, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  Fdistance=Fduration*0.0343/2;  
  FTim=Sdistance/0.398982267005903668;
  Serial.print("Distance to wall: ");
  Serial.print(Fdistance);
  Serial.println(" cm");
  Serial.print(FTim*0.1);                    //Multiplied by 0.001
  Serial.println(" seconds to approach object");
}

void loop() 
{
  //LCorner or RCorner statement
  FollowWallSides();
}
