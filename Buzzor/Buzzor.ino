const int buzzer = 8; //buzzer to arduino pin 9
const int led1 = 6;

void setup(){
   
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(led1, OUTPUT);
}

void loop(){
  
  tone(buzzer, 2000); // Send 1KHz sound signal...
  digitalWrite(led1, HIGH);
  delay(1000);         // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  digitalWrite(led1, LOW);
  delay(1000);         // ...for 1sec
  
}
