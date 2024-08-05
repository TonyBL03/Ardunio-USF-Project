//int incomingByte = 0; // for incoming serial data
#define in1 2
#define in2 4
#define RECEIVER_PIN 12
#include <IRremote.h>

  int f=1;
  int r=1;
  int p=1;
  int i=1;

IRrecv receiver (RECEIVER_PIN);
decode_results results;

void setup() 
{
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  receiver.enableIRIn();
  receiver.blink13(true);
  Serial.println("Type in: 0,1, or 2");

}

char incomingByte=0;

void loop() 
{
  // reply only when you receive data:
  if (((receiver.decode(&results)))&&(i<5))
  {
    // read the incoming byte:
 //   results.value = Serial.read();
    {
      if ((results.value == 16718055)&&(f<5))
      {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        Serial.println("0-Forward");
        f++;
      }
      if ((results.value == 16730805)&&(r<5))
      {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        Serial.println("1-Reverse");
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        r++;
      }
      
      if ((results.value == 16726215)&&(p<5))
      {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        Serial.println("2-Stop");
        p++;
      }
    }
    i++;
  }
}
