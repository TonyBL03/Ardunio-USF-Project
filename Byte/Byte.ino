//int incomingByte = 0; // for incoming serial data
#define in1 2
#define in2 4

void setup() 
{
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

char incomingByte=0;

void loop() 
{
  // reply only when you receive data:
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    {
      if (incomingByte == 48)
      {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        Serial.println("0-Forward");
      }
      if (incomingByte == 49)
      {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        Serial.println("1-Reverse");
      }
      if (incomingByte ==50)
      {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        Serial.println("2-Stop");
      }
    }
    // say what you got:
//    Serial.print("I received: ");
//    Serial.println(incomingByte, DEC);
  }
}
