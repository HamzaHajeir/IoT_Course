#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

ESP8266WebServer server(80);

const char *ssid = "ESP_AP";
const char *password = "your-pass";

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
    server.send(200, "text/html", "<h1>You are connected</h1>");
}

void switchON() {
    digitalWrite(LED_BUILTIN, LOW);  //Turn LED ON

    String message = "LED is ON!\n";
    server.send(200, "text/plain", message);
}

void switchOFF() {
    digitalWrite(LED_BUILTIN, HIGH);  //Turn LED OFF

    String message = "LED is OFF!\n";
    server.send(200, "text/plain", message);
}

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);

    pinMode(LED_BUILTIN, OUTPUT);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", handleRoot);
    server.on("/ON", switchON);
    server.on("/OFF", switchOFF);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}