#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid     = "yourSSID";
const char* password = "yourPass";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  WiFi.waitForConnectResult();

  if(WiFi.status() == WL_CONNECTED ){
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }


}

void loop() {
  // put your main code here, to run repeatedly:
}