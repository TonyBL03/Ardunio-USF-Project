/*
Adafruit Arduino - Lesson 13. DC Motor
*/

#define in1 2
#define in2 4
#define in3 7
#define in4 8

 
void setup() 
{ 
  pinMode(in1, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(in1, speed);
    }
  }
}
