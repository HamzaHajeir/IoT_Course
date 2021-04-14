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

BlynkTimer timer;

void pushSensorData(){
	
  int analogValue = analogRead(A0);
  float voltage = analogValue * 3.3f/4095;
  float temperature = voltage / 0.01 ;
  
  Blynk.virtualWrite(V2,temperature);
  Serial.printf("Temperature = %.2f Celsius \n", temperature );
	
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass/*, IPAddress(188,166,206,43)*/);
  
  timer.setInterval(500L, pushSensorData);
  
}

void loop() {
  Blynk.run();
  timer.run();
}
