#include <DHT.h>
DHT dht (11, DHT11);

#define RAIN_PIN A0
#define LDR_PIN  A1
#define BUZZER   7
#define LED1     5
#define LED2     6

bool fanState = false;
bool rainState = false;
bool windowState = false;
bool buzzerDone = false;
int whileState = 0;
int Buzzer = 0;

int LDRVAL;//Define variable for LDR
int RAINVAL;//Define variable for Rain Sensor

void setup() {

  // input sensors
  pinMode(RAIN_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  
  // outputs
  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600); //To start Serial Monitor
  Serial.println("Welcome! Weather Aware System is Starting...");
  delay(1000);

  dht.begin(); //For dht11 sensor

}

void loop() {
  
  float temperature = dht.readTemperature(); //Read Temperature
  Serial.println(temperature);

  // Check if any reads failed in DHT11
  if (isnan(temperature)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }
  
//Turning on the fan 
 if (temperature >= 25) {
    fanturnon();
    fanState = true; 
    buzzerDone == false;                     
}

//Turning buzzor for on time
  if (fanState == true && buzzerDone == false) {

    tone(BUZZER, 1000);
    delay(500);
    noTone(BUZZER);

    buzzerDone = true;   // prevents repeat beep
}

//Turning off the fan
  if (temperature <= 20) {
      fanturnoff();
      fanState = false;                   
 } 


//get rain sensor value
  RAINVAL = analogRead(RAIN_PIN);
  int MAP_RAINVAL = map(RAINVAL,0,1023,0,255);
  //Serial.println(MAP_RAINVAL);

  if (MAP_RAINVAL >= 200) {
    Serial.println("It's not raining");
    rainState = false;
  }
  
  if (MAP_RAINVAL <= 200) {
    Serial.println("It's raining");
    rainState = true; 
  } 

  LDRVAL = analogRead(LDR_PIN);
  if (LDRVAL >= 300 && rainState == false) {
    windowopen();
    whileState = 0;
    Buzzer = 0;
  }
  
  if (LDRVAL <= 300) {
    windowclose();

 }

 //Turning Buzzer for one time
  if (LDRVAL >= 300 && rainState == true && windowState == true) {
    windowclose();
    Buzzer = 1;
 }
 
 if (Buzzer == 1 && whileState == 0) {
    whileState = 1;                 // go to next stage
  }

  while (whileState == 1) {
    tone(BUZZER, 1000);
    delay(1000);
    noTone(BUZZER);

    whileState = 2;   // completed → go to final state
  }

}

//Function for turn on fan
void fanturnon(){
  Serial.println("Fan turned ON");
  digitalWrite(LED2, HIGH);
  delay(500);
}

//Function for turn off fan
void fanturnoff(){
  Serial.println("Fan turned OFF");
  digitalWrite(LED2, LOW);
}

//Function for close the window
void windowclose(){
  Serial.println("Window is closing...");
  digitalWrite(LED1, LOW);
  windowState = false;
}

//Function for open the window
void windowopen(){
  Serial.println("Window is opening...");
  digitalWrite(LED1, HIGH);
  windowState = true;
}
