void setup() 
  {
  //Start serial communication
  Serial.begin(9600);
  //For the loop to run from 2 to 9
  for (int i=2; i<10; i++)
    {
  //Makes the pins the output
      pinMode(i,OUTPUT);
  //Setting pins to LOW makes sure the LEDs are off
      digitalWrite(i,LOW);
    }
  }

void loop() 
    {
            //I MIGHT HAVE TO CHANGE THIS BASED UPON WHEN I DO IT
      int counter = 1;
    for (int i = 0; i<8; i++)
      {
        if (bitRead(counter,i) == 1)
          {
            //I think this loop has the light turn on when i=1, otherwise turn off
            digitalWrite(i+2,HIGH);
          }
        else
          {
            digitalWrite(i+2,LOW);
          }
      }
      //This is a delay of 100ms so we can see the counter counting
      delay(100);
      //Increments the counter (shortened for "counter=counter+1")
      counter++;
      //The maximum the counter can reach is 255, then reverts to 0
      //Sends the counter value to the serial port to the serial monitor in the Arduino IDE
      Serial.print(counter); //Counter value to serial port
      Serial.print(" as binary number:"); //Send a string
      //BIN=binary, HEX=hexadecimal
      Serial.println(counter,BIN); //Sends the value in binary format and then a line feed
   }
