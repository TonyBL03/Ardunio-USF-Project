void setup() 
{
  int time=3000;
  int time2=1500;
  pinMode(13, OUTPUT);
}

void loop() 
{
  int time=3000;
  int time2=1500;
  digitalWrite(13, HIGH);
  delay(time);
  digitalWrite(13, LOW);
  delay(time2);
}
