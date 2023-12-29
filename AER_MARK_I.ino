#define BLYNK_TEMPLATE_ID "TMPL3oC5aV9ps"
#define BLYNK_TEMPLATE_NAME "AER"
#define BLYNK_AUTH_TOKEN "-pNSiO5XEHASPf7yT7fj9E-YBj0ablDy"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Gokul";  // Replace with your WiFi name
char pass[] = "08112004";  // Replace with your WiFi password

LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

int gas = A0;
int sensorThreshold = 100;

#define DHTPIN 2 // Connect Out pin to D2 on NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int analogSensor = analogRead(gas);
  Blynk.virtualWrite(V2, analogSensor);
  Serial.print("Gas Value: ");
  Serial.println(analogSensor);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("    Humidity: ");
  Serial.println(h);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(30000L, sendSensor);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Air Quality");
  lcd.setCursor(3, 1);
  lcd.print("Monitoring");
  delay(2000);
  lcd.clear();
}

void loop() {
  Blynk.run();
  timer.run();
}

// Additional code if needed
