#define dimmer 9

void setup() {
  // put your setup code here, to run once:
  pinMode(dimmer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(dimmer, 64);
}
