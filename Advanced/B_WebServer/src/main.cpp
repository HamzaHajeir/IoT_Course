#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

const char *ssid = "yourSSID";
const char *password = "yourPASS";

ESP8266WebServer server(80);

void handleRoot()
{
    server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void switchON()
{

    digitalWrite(LED_BUILTIN, LOW); //Turn LED ON

    String message = "LED is ON!\n";
    server.send(200, "text/plain", message);
}

void switchOFF()
{

    digitalWrite(LED_BUILTIN, HIGH); //Turn LED OFF

    String message = "LED is OFF!\n";
    server.send(200, "text/plain", message);
}

void setup()
{
    // put your setup code here, to run once:

    Serial.begin(115200);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    WiFi.waitForConnectResult();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else        //Cause WDT, Resets the MCU.
    {
        while (1)
            ;
    }

    if (MDNS.begin("esp8266"))
    {
        Serial.println("MDNS responder started");
    }

    pinMode(LED_BUILTIN, OUTPUT);


    server.on("/", handleRoot);
    server.on("/ON", switchON);
    server.on("/OFF", switchOFF);
    server.on("/inline", []() { //lambda function
        server.send(200, "text/plain", "this works as well");
    });
    server.on("/hamza", []() {
        server.send(401, "text/plain", "Error auth");
    });

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    // put your main code here, to run repeatedly:
    server.handleClient();
    MDNS.update();
}