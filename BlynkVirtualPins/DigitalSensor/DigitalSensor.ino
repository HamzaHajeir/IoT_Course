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
const int button_pin = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass/*, IPAddress(188,166,206,43)*/);
  
  pinMode(button_pin,INPUT);
}

void loop() {
  Blynk.run();
  
  if(digitalRead(button_pin) == LOW){
	  led.on();
  }
  else {
	  led.off();
  }
  
}
