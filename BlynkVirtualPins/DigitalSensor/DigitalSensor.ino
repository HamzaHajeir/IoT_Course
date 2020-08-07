#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

WidgetLED led(V4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(D1,INPUT);
}

void loop() {
  Blynk.run();
  
  if(digitalRead(D1) == LOW){
	  led.on();
  }
  else {
	  led.off();
  }
  
}
