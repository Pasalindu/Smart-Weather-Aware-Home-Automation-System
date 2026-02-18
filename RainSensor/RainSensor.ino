void setup() {
  Serial.begin(9600);//enable serial monitor
  pinMode(4, OUTPUT);//define LED pin
}
void loop() {
  int value = analogRead(A3);//read value
  Serial.print("Value : ");
  Serial.println(value);
  if (value < 400) {//check condition
    digitalWrite(4, HIGH);
    Serial.print("Heavy rain  LED on ");
  } else {
    digitalWrite(4, LOW);
  }
}
