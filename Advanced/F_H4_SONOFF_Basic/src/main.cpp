#include <Arduino.h>
#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop

#define SSID    "XXXXXXXX"
#define PASS    "XXXXXXXX"

H4P_GPIOManager h4gm;
H4P_FlasherController h4fc;
H4P_WiFi h4wifi(SSID,PASS,"H4-Test");
H4P_AsyncMQTT h4mqtt("192.168.1.20",1883);// Server IP , Port
H4P_BinarySwitch h4onof(RELAY_BUILTIN,ACTIVE_HIGH,OFF);
H4P_UPNPServer h4upnp("Test SONOFF");
H4P_MultiFunctionButton h43fb(BUTTON_BUILTIN,INPUT_PULLUP,ACTIVE_LOW,15);
