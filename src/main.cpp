#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define DS18B20_PIN 32
#define DHT11_PIN 4
#define LED_PIN 19
#define RELAY_1_PIN 14
#define RELAY_2_PIN 27

// #define BLYNK_TEMPLATE_ID "TMPL6GNmO6020"
// #define BLYNK_TEMPLATE_NAME "iot hidropoink"
// #define BLYNK_AUTH_TOKEN "l7lQQsP-yi4QsXvM0rFmPXJ1dB1rSJk_"
// #include <BlynkSimpleEsp32.h>

#define DHT_TYPE DHT11

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

DHT dht(DHT11_PIN, DHT_TYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient client;

const char *ssid = "POCO X6 Pro 5G";
const char *password = "1234567890";

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);

  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  lcd.init();
  lcd.backlight();
  dht.begin();
  sensors.begin();
}

// BLYNK_CONNECTED() {
//    Blynk.syncAll();
// }

// BLYNK_WRITE(V10)
// {
//   if(param.asInt() == 1)
//   {
//     digitalWrite(RELAY_1_PIN, HIGH); 
//   }
//   else
//   {
//     digitalWrite(RELAY_1_PIN, LOW);    
//   }
// }

// BLYNK_WRITE(V11)
// {
//   if(param.asInt() == 1)
//   {
//     digitalWrite(RELAY_2_PIN, HIGH); 
//   }
//   else
//   {
//     digitalWrite(RELAY_2_PIN, LOW);    
//   }
// }


void loop()
{
  // Blynk.run();
  delay(1000);
  float roomTemperature = dht.readTemperature();
  float roomHumidity = dht.readHumidity();
  sensors.requestTemperatures();
  float waterTemperature = sensors.getTempCByIndex(0);

  // Blynk.virtualWrite(V0, roomTemperature);
  // Blynk.virtualWrite(V1, waterTemperature);
  // Blynk.virtualWrite(V2, roomHumidity);
  if (roomTemperature > 29)
  {
    digitalWrite(RELAY_1_PIN, HIGH);
  }
  else
  {
    digitalWrite(RELAY_1_PIN, LOW);
  }

  Serial.printf("Room temperature: %f C | Room humidity: %f % | Water temperature: %f C\n", roomTemperature, roomHumidity, waterTemperature);
  lcd.setCursor(0, 0);
  lcd.print("Room: ");
  lcd.printf("%.1f\337C %d", roomTemperature, (int)roomHumidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Water: ");
  lcd.printf("%.1f\337C", waterTemperature);
}