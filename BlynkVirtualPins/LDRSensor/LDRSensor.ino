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

BlynkTimer timer;

void pushSensorData(){
	
  int ldrValue = analogRead(A0);
  
  Blynk.virtualWrite(V2,ldrValue);
  Serial.printf("LDR Value = %d \n", ldrValue );
	
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(500L, pushSensorData);
  
}

void loop() {
  Blynk.run();
  timer.run();
}
