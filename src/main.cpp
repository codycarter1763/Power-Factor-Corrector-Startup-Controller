#include <Arduino.h>
#include <Wire.h>

#define PF_ENABLE 11
#define LD_ENABLE 12
#define PF_ENABLE_LED 10
#define LD_ENABLE_LED 9
float TEMP_MON;
float CURR_MON;
float TEMP_MON_RAW;
float CURR_MON_RAW;
float SCALED_TEMP;
float SCALED_CURR;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(PF_ENABLE, OUTPUT);
  pinMode(LD_ENABLE, OUTPUT);
  pinMode(PF_ENABLE_LED, OUTPUT);
  pinMode(LD_ENABLE_LED, OUTPUT);

  digitalWrite(PF_ENABLE, HIGH);
  digitalWrite(PF_ENABLE_LED, LOW);

  digitalWrite(LD_ENABLE, HIGH);
  digitalWrite(LD_ENABLE_LED, HIGH);
  delay(2000);

  digitalWrite(PF_ENABLE, LOW);
  digitalWrite(PF_ENABLE_LED, HIGH);
  delay(600);
  digitalWrite(LD_ENABLE, LOW);
  digitalWrite(LD_ENABLE_LED, LOW);

}

void loop() {
  TEMP_MON_RAW = analogRead(A0);
  CURR_MON_RAW = analogRead(A1);

  SCALED_CURR = CURR_MON_RAW * (5.0 / 1023.0);
  SCALED_TEMP = TEMP_MON_RAW * (5.0 / 1023.0);
  TEMP_MON = (SCALED_TEMP - 0.5) / 0.01;
  CURR_MON = SCALED_CURR / 0.3;

  Wire.beginTransmission(0x67); // Ideal address
  Wire.write((uint8_t*)&TEMP_MON, sizeof(TEMP_MON));  
  Wire.write((uint8_t*)&CURR_MON, sizeof(CURR_MON));   
  Wire.endTransmission();

  Serial.print("Temperature: ");
  Serial.print(TEMP_MON);
  Serial.print(" C  | Current: ");
  Serial.print(CURR_MON);
  Serial.println(" A");
  delay(500);
}
