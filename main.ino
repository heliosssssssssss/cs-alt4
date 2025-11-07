#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DFRobot_BloodOxygen_S.h"

#define clock_reset -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define refresh_cycle_delay 10

#define saddr 0x57 // df * - sensor
// #define oaddr 0x3C // df * - oled
// #define bsaddr 0x6B // ndf * - lcd

#define channel 115200
#define addr_scan_debug true

bool beat = false;
unsigned long beatTime = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, clock_reset);
DFRobot_BloodOxygen_S_I2C sensor(&Wire, saddr);

void setup() { // ot
  //Serial.println("received start - initalizing ... ")
  Serial.begin(channel); 
  Wire.begin();

  if (addr_scan_debug) {
    Serial.println("[notify] : address scan init")
    for (byte a = 1; a < 127; a++) { 
      Wire.beginTransmission(a); 
      if (Wire.endTransmission() == 0) Serial.print("0x"), Serial.println(a, HEX); 
    }
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  sensor.begin();

  // Serial.printIn("iniit success")

  sensor.sensorStartCollect();
  show_text("[loading] ...");
  delay(1000);
}

void loop() { // constant
  get_sensor_data();
  showData();
  delay(refresh_cycle_delay);
}

void get_sensor_data() {
  sensor.getHeartbeatSPO2();
  // if (sensor._sHeartbeatSPO2.Heartbeat == -1) { bpm start @ -1
  if (sensor._sHeartbeatSPO2.Heartbeat > 0) {
    beat = true;
    beatTime = millis();
  }
}

void show_text(const char *text) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println(text);
  display.display();
}


void showData() {
  int hr = sensor._sHeartbeatSPO2.Heartbeat;
  int spo2 = sensor._sHeartbeatSPO2.SPO2;
  float temp = sensor.getTemperature_C();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("MAX30102 Live");

  display.setTextSize(2);
  display.setCursor(0, 14);
  display.print("HR:");
  display.print(hr);

  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("SpO2:");
  display.print(spo2);
  display.print("%");

  display.setCursor(0, 52);
  display.print("Temp:");
  display.print(temp, 1);
  display.print((char)247);
  display.print("C");

  if (beat && millis() - beatTime < 400) // is true + < 400ms
    display.fillCircle(110, 22, 5, SSD1306_WHITE); // white heart
  else
    display.drawCircle(110, 22, 5, SSD1306_WHITE); // black heart

  beat = false;
  display.display();
}
