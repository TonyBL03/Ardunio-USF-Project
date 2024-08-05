//Defines the connections between the H-bridge and the Arduino
#define in1 12
#define in2 4
#define ENAPin 11

void setup() 
{
  pinMode (11, OUTPUT);   //Sets the pin at in1 to output 
  pinMode (in2, OUTPUT);   //Sets the pin at in2 to output

}

void loop() 
{
  // Turn in one direction
  //Left Motor
  analogWrite(11, 250);
  digitalWrite(in2, LOW);

  delay (5000);
  
  //Turn in opposite direction
  digitalWrite(11, LOW);
  digitalWrite(in2, HIGH);

  delay (2000);
}
