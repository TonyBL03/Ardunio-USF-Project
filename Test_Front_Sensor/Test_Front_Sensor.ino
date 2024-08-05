#define echoPinF A1
#define trigPinF A0

long Fduration;
int Fdistance;
double FTim;

void setup() 
{
 pinMode (trigPinF, OUTPUT);
 pinMode (echoPinF, INPUT);
  
}

void loop() 
{
  digitalWrite(trigPinF, LOW);             //Doesn't trigger the Sensor
  Serial.println("Scanning distance to wall");
  delay(10);                              //The delay
  digitalWrite(trigPinF, HIGH);            //Triggers the Sensor and the ultrasonic pulses
  delay(10);                              //Another delay
  digitalWrite(trigPinF, LOW);             //Stops the Sensor
  Fduration=pulseIn(echoPinF, HIGH);        //The echoPin activates and recieves the wave used by the trigPin
  Fdistance=Fduration*0.0343/2;  
  FTim=Fdistance/0.398982267005903668;
  Serial.print("Distance to wall: ");
  Serial.print(Fdistance);
  Serial.println(" cm");
  Serial.print(FTim*0.1);                    //Multiplied by 0.001
  Serial.println(" seconds until collision");
  delay(900);
}
