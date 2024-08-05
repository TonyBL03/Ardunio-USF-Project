// defines pins numbers

#define trigPin 9
#define echoPin 10
// defines variables

long travelTimeOfTheWave;
int distanceTraveledByTheWave;


#define in1 2
#define in2 4
#define enA 3

#define in3 5
#define in4 7
#define enB 6

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);

}

void loop() {

digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);

digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
travelTimeOfTheWave = pulseIn(echoPin, HIGH);
// Calculating the distance

distanceTraveledByTheWave= travelTimeOfTheWave*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("distanceTraveledByTheWave: ");
Serial.println(distanceTraveledByTheWave);

if(distanceTraveledByTheWave > 10){

analogWrite(enA, 200);
analogWrite(enB, 200);
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);

delay(500);
}
if(distanceTraveledByTheWave <10)
{
  analogWrite(enA, 0);
analogWrite(enB, 0);
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);


}
}
