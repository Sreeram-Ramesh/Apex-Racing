/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Attention! Please check out TinyGSM guide:
    https://tiny.cc/tinygsm-readme

  Change GPRS apm, user, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!

 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3IU31GKPy"
#define BLYNK_TEMPLATE_NAME "SIM800L"
#define BLYNK_AUTH_TOKEN "WiukljEq7O5epb5TMgUZHKUGahqNmuaU"


#define TINY_GSM_MODEM_SIM800

const int Relay1_line1 = 35;
const int Relay1_line2 = 39;
const int Relay2_line1 = 45;
const int Relay2_line2 = 49;


// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "airtelgprs.com";
char user[] = "";
char pass[] = "";

// Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// or Software Serial on Uno, Nano
// #include <SoftwareSerial.h>
// SoftwareSerial SerialAT(2, 3); // RX, TX

TinyGsm modem(SerialAT);

BLYNK_CONNECTED(){
  Blynk.syncVirtual(V0, V1, V2, V3);
}

BLYNK_WRITE(V0){
  digitalWrite(Relay1_line1, param.asInt());
}

BLYNK_WRITE(V1){
  digitalWrite(Relay1_line2, param.asInt());
}

BLYNK_WRITE(V2){
  digitalWrite(Relay2_line1, param.asInt());
}

BLYNK_WRITE(V3){
  digitalWrite(Relay2_line2, param.asInt());
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(Relay1_line1, OUTPUT);
  pinMode(Relay1_line2, OUTPUT);
  pinMode(Relay2_line1, OUTPUT);
  pinMode(Relay2_line2, OUTPUT);

  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(9600);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  modem.restart();

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  Blynk.begin(BLYNK_AUTH_TOKEN, modem, apn, user, pass);
}

void loop()
{
  Blynk.run();
}

