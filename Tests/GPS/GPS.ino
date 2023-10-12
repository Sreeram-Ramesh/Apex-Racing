#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SIM800L.h>
#include <BlynkSimpleSIM800.h>

const int gpsTxPin = 4;  // Connect GPS TX to this pin on Arduino
const int gpsRxPin = 3;  // Connect GPS RX to this pin on Arduino

SoftwareSerial gpsSerial(gpsTxPin, gpsRxPin);
TinyGPSPlus gps;

#define SIM800_RX_PIN 10  // Connect SIM800 RX to this pin on Arduino
#define SIM800_TX_PIN 11  // Connect SIM800 TX to this pin on Arduino
#define SIM800_POWER_PIN 9  // Connect SIM800 power control to this pin on Arduino

char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

SIM800L sim800l(SIM800_RX_PIN, SIM800_TX_PIN, SIM800_POWER_PIN);

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Blynk.begin(auth, sim800l, "BlynkServer.com", 80);
}

void loop() {
  Blynk.run();
  
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isUpdated()) {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 7);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 7);

        Blynk.virtualWrite(V1, gps.location.lat());
        Blynk.virtualWrite(V2, gps.location.lng());
      }
    }
  }
}