#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Servo.h>
Servo myServo;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BLYNK_WRITE(V3) {

  int pinValue = param.asInt();  // assigning incoming value from pin V1 to a variable
  myServo.write(pinValue);
  // process received value
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  myServo.attach(D5);
  Blynk.begin(auth, ssid, pass);
  myServo.write(0);
}

void loop() {
  Blynk.run();
}
