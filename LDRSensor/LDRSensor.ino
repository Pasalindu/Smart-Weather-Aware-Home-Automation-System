#define LDR_PIN A0
#define LED_PIN 4

int ldr_value;
int threshold = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ldr_value = analogRead(LDR_PIN);
  Serial.println(ldr_value);
  delay(500);

  if (ldr_value > threshold) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
}
