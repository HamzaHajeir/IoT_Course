#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

WidgetLED led(V4);
const int button_pin = 25;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass/*, IPAddress(188,166,206,43)*/);

  pinMode(button_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Blynk.run();
  static uint32_t prevmillis;
  if (digitalRead(button_pin) == HIGH) {

    if (millis() - prevmillis >= 7000) {
      led.on();
      prevmillis = millis();
    }

    digitalWrite(LED_BUILTIN , LOW);

  }
  else {
    led.off();

    digitalWrite(LED_BUILTIN , HIGH);
  }
}
