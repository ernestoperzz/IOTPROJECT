#include <DFRobot_DHT11.h>
#include <Wire.h>


DFRobot_DHT11 DHT;
#define AO_PIN 34 // Arduino's pin connected to AO pin of the MQ2 sensor
#define DHT11_PIN  21 // ESP32 pin GPIO21 connected to DHT11 sensor
#define RELAY_PIN 15 // ESP32 pin GPIO16 that connects to relay to control the 12V buzzer


const int TRIG_PIN = 5;
const int ECHO_PIN=18;
long duration;
float cms, inches;





void setup() {
  // serial port begin
  Serial.begin (9600);

  // define inputs and outputs
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
 pinMode(RELAY_PIN, OUTPUT);

  Serial.println("1.Burglar alarm.");
  Serial.println("2.Temperature and humidity");
  Serial.println("3.Smoke alarm");



}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("Which sensor would you like to read? ");

  while (Serial.available() == 0) {
  }

  int menu = Serial.parseInt();

  switch (menu) {

    case 1:
      //burglar alarm
    BurglarAlarm();
    
    break;
    case 2:
      // temp and humidity sensor code goes here
    TempAndHumidity();
     
    break;
    case 3:
      // Smoke alarm
    SmokeAlarm();
    
    break;
    default:
      Serial.println("Please choose a valid selection");
      break;
  }
}

void BurglarAlarm(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);

 duration=pulseIn(ECHO_PIN, HIGH);



 cms = (duration/2)/29.1;
 inches = (duration/2)/74;

 Serial.print(inches);
 Serial.print("in, ");
 Serial.print(cms);
 Serial.print("cm");
 Serial.println();
if(cms < 5){
  Serial.print("Pedestrian detected!!\n");
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);
  delay(2000);
}
 delay(250); 

}

void TempAndHumidity(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);
}

void SmokeAlarm(){
  int gasValue = analogRead(AO_PIN);

  Serial.print("MQ2 sensor AO value: ");
  Serial.println(gasValue);
 if(gasValue > 900){
   Serial.print("High amount of gas detected!!!\n");
   digitalWrite(RELAY_PIN, HIGH);
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);
  delay(2000);
 }
}




