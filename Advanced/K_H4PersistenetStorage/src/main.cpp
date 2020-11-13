#include <Arduino.h>
#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop

#define SSID    "ORANGE_1"
#define PASS    "123456789"

void onChange(const string& name,const string& value){
    Serial.printf("ITEM %s changed to %s\n",CSTR(name),CSTR(value));
}

H4P_GPIOManager h4gm;
H4P_FlasherController h4fc;
H4P_WiFi h4wifi(SSID,PASS,"H4-Test");
H4P_AsyncMQTT h4mqtt("192.168.1.4",1883);// Server IP , Port
H4P_AsyncWebServer h4asws;
H4P_BinarySwitch h4onof(RELAY_BUILTIN,ACTIVE_HIGH,OFF,[](bool b){
    if(b)
    {
        h4ps.inc("starts");
    }
});
H4P_UPNPServer h4upnp("My Light");
H4P_MultiFunctionButton h43fb(BUTTON_BUILTIN,INPUT_PULLUP,ACTIVE_LOW,15,LED_BUILTIN,ACTIVE_LOW);
H4P_PersistentStorage h4ps(onChange);

void h4setup() {
    h4ps.setstring("secret","life, the universe and everything");
    h4ps["peasy"]="easy"; //can also set string values like this
    string easy=h4ps["peasy"]; // or get them like this
    easy=h4ps.getstring("peasy"); // and this
    Serial.printf("Using H4P_PersistentStorage is %s\n",CSTR(h4ps["peasy"]));

    if(!h4ps.exists("answer")){
        Serial.printf("What is the secret of %s?\n",CSTR(h4ps["secret"]));
        h4ps.setint("answer",42); // no short way to handle integers
        Serial.println("send h4/reboot to find out");
    }
    else {
        Serial.printf("Apparently the secret of %s is %d\n",CSTR(h4ps["secret"]),h4ps.getint("answer"));
        h4ps.inc("answer"); // increments the value: can also dec it
        Serial.println("send h4/reboot repeatedly to see increasingly WRONG answer");
    }
}