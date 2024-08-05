//Defining connections for the motors
#define in1 2    //in1 (H-board) connected with 2 (Arduino)
#define in2 4    //in2 (H-board) connected with 4 (Arduino)
#define in3 7    //in3 (H-board) connected with 7 (Arduino)
#define in4 8    //in4 (H-board) connected with 8 (Arduino)

//Defining connections for ultrasonic sensor
#define echoPin 9    //echo (Sensor) connected with PWM 9
#define trigPin 10   //trig (Sensor) connected with PWM 10

#include <Servo.h>
Servo myservo;

//Defining variables
long duration; //Long variable used to extend the amount of time the sensor records to properly measure the the speed of the wavelength when calculating distance
int distance; //variable for distance in centimeters
int pos=0; //For Servo

void setup() 
{
 myservo.attach(11);
 pinMode (trigPin, OUTPUT);     //The trig pin on the Sensor
 pinMode (echoPin, INPUT);      //The echo pin on the Sensor
 pinMode (in1, OUTPUT);         //In1 on the H-Board; Used to spin the left motor in the same direction as In3
 pinMode (in2, OUTPUT); //       //In2 on the H-Board; Used to spin the left motor in the same direction as In4  INPUT
 pinMode (in3, OUTPUT);         //In3 on the H-Board; Used to spin the right motor in the same direction as In1
 pinMode (in4, OUTPUT);          //In4 on the H-Board; Used to spin the right motor in the same direction as In2 INPUT
 Serial.begin(9600);            //Launches the Serial Monitor in 9600 baud
 Serial.println("Launching..."); //Just to know when the program starts
}

void loop() 
{
  digitalWrite(trigPin, LOW);    //Doesn't trigger the Sensor
  delay(2000);                      //The delay
  digitalWrite(trigPin, HIGH);   //Triggers the Sensor and the ultrasonic pulses
  delay(1000);                      //Another delay
  digitalWrite(trigPin, LOW);    //Stops the Sensor
  duration=pulseIn(echoPin, HIGH); //The echoPin activates and recieves the wave used by the trigPin
  distance=duration*34300/2000000;        //Distance=Duration*Speed of Sound (in centimeters)/the delay that the trigPin writes (in microseconds)
  Serial.print("Distance: ");             //Print
  Serial.print(distance);                 //Print
  Serial.println(" cm");                  //Prints and has the printing in the Serial Monitor be on separate lines
  {
  if (distance<=10)                       //If the distance is less than or equal to 10 centimeters, then the motors will spin opposite of each other
  {
    for (pos<=0; pos<= 360; pos +=1)
    myservo.write(pos);
    delay(15);
    digitalWrite(in1,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in4,HIGH);
  }
  if (distance ==0)                                   //If the distance is greater than 10 centimeters, then the motors will spin together in the same direction
  {
//    digitalWrite(in1,HIGH);
//    digitalWrite(in3,HIGH);              //analogWrite
//    digitalWrite(in2,LOW);
//    digitalWrite(in4,LOW);
  }
  if (distance >=20)
  {
    for (pos<=0; pos>= 360; pos -=1)
    myservo.write(pos);
    delay(15);
    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
  }
  }
 }
