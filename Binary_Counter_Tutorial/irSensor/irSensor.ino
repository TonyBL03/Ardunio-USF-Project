#define sensorPin 14

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int sensorStatus = digitalRead(sensorPin);

  if(sensorStatus == HIGH){
    Serial.println("HIGH - No obstable/Black surface");
    
  }
  else{
    Serial.println("LOW - Obstacle/White surface");
  }
delay (500);
}
