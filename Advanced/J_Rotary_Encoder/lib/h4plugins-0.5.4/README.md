![H4P Logo](/assets/H4PLogo.png)

# Arduino IDE library targeting ESP8266, ESP32 and STM32-NUCLEOxx boards providing IOT functionality including WiFi, MQTT, GPIO management and diagnostic tools

## (WiFi and dependent plugins not available on STM32-NUCLEOxx series)

*All plugins depend upon the presence of the [H4 library](https://github.com/philbowles/H4), which must be installed first.*

## Version **0.5.1** is a major release with many changes, you *must* read the [Release Notes](docs/rn051.md) and upgrade to [H4 library](https://github.com/philbowles/H4) v0.5.1 first

---![H4PluginsFF](/assets/h4plugins.jpg)

Think of H4 and its plugins as "IOT Lego" or an "IOT Swiss Army Knife" (or both) for [**H4**](https://github.com/philbowles/H4) - and if you are not already using H4's advanced scheduling and timing features, why not? Get it now from the link above, as you will need it to use the H4Plugins system.

H4Plugins includes modules for WiFi + OTA, Webserver, MQTT, numerous common types of GPIO handling (e.g. debouncing, rotary encoders), Amazon Alexa voice control, logging to remote MySQL server and extensive diagnostics. By "plugging " together only the required modules, you can rapidly build your own custom firmware or IOT app. Everything you build will be stable and responsive: the plugins work together to allow multiple simultaneous processes to run, so ***no more WDT resets***! As your experience grows you can extend your app / firmware with H4Plugins' well-documented API and runtime command system. Let's see H4Plugins being used as replacement firmware for a SONOFF Basic switch.

What follows is the *entire H4Plugins code* - despite the fact it might look like there is something missing, there is not. The code as shown compiles to produce firmware that can be uploaded directly to any / all of your SONOFF devices and provides:

* Autoconnect/reconnect of failed WiFI and/or MQTT with no reboot
* AP mode configuration
* OTA
* Full control via Serial console
* Full control via MQTT including publish on state change
* Single-button multifunction control for on/off, reboot, factory reset and forced AP Mode  depending on the hold time
* LED pattern signalling, e.g. ... --- ... ("SOS") = No WiFi, two short blips = no MQTT, single slow blip = AP mode etc
* HTTP REST control from any other device with JSON response
* Dynamic reconfiguration of SSID and/or MQTT server
* Optional master/slave of other H4 devices
* UPNP device control from e.g. Windows Network Explorer
* Alexa voice control

```cpp
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop

H4P_GPIOManager h4gm;
H4P_FlasherController h4fc;
H4P_WiFi h4wifi("XXXXXXXX","XXXXXXXX","h104");
H4P_AsyncWebServer h4asws("admin","admin");
H4P_AsyncMQTT h4mqtt("192.168.1.4",1883);
H4P_BinarySwitch h4onof(RELAY_BUILTIN,ACTIVE_HIGH,OFF);
H4P_UPNPServer h4upnp("Demo Switch");
H4P_MultiFunctionButton h43fb(BUTTON_BUILTIN,INPUT,ACTIVE_LOW,15,LED_BUILTIN,ACTIVE_LOW);
```

As you can see, all you need to do is list the modules you require and provide a few necessary values such as ssid / passwords etc and the plugins link up with each other, exchange messages between themselves and "stitch" everything together into a seamless piece of stable firmware. If you know of anything easier for both beginners and seasoned developers, please let us know.

The modular design of H4's plugin architecture minimises scarce resources in low-memory MCU targets: You only compile in what you need with a simple `#include`. Detailed diagnostics can be easily included (or completely compiled-out) and controlled at runtime via the serial console, HTTP REST or MQTT depending on which options you choose. It is built on top of the very stable [H4](https://github.com/philbowles/H4) timer/scheduler which traces its ancestry back to "Esparto" - of which one user recently said: *"and now have Esparto modules with months of uptime without an issue"*.

There are 52(!) example sketches demonstrating all the features and the API of all of the plugins. They should be used both as a template for your own sketches and as a learning resource. Users are strongly recommended to work through them in the order [listed below](readme.md#current-plugins-februrary-2020)

Each plugin is also throroughly documented in the links below. *Please make sure you have read and fully understood the documentation for the [H4 library](https://github.com/philbowles/H4) and the relevant Plugin(s) before raising an issue.*

---

# Examples / applications / ideas

## AP configuration mode webserver on mobile phone:

![SONOFF](/assets/mobilesmall.jpg)

## Windows 10 Network Explorer interface

![UPNP](/assets/upnpsmall.jpg)

## Extensive GPIO library

Simple one-line GPIO management of debouncing, retriggering, pulse counting, timing rotary encoders etc

![UPNP](/assets/GPIOsmall.jpg)

## Cross-platform code

Some of the plugins (non WiFi-dependent) also run on STM32-NUCLEO boards. Some have been tested also on Raspberry Pi and even Ubuntu linux. 


## Device drivers

H4Plugins make it really easy and quick to write your own safe, stable fimrware for novel devices. The code co-operates automatically with (and can be controlled by) existing plugins. As an example H4Plugins comes with a fully working controller for a cheap ($3) square-wave generator which provides both frequency and duty cycle sweeps as well as simple F and DC value setting via Serial, HTTP REST and/or MQTT

When you think that H4Plugins also has "plug and play" rotary encoder handling, it is easy to see how you could build a complete WiFi and manual-control lab instrument in a day. *I* did!

![SQWV](/assets/sqwvhardware.jpg)

---

# Plugins
## Core IOT functionality

* [**H4P_SerialCmd**](docs/h4cmd.md): Send commands from multiple sources to H4 and/or plugins to control and/or diagnose
* [**H4P_FlasherController**](docs/h4fc.md): One-line coding of multiple simultaneous LED flashing by Square Wave, PWM, abitrary pattern and Morse code
* [**H4P_GPIOManager**](docs/h4gm.md): One-line coding of debouncing, retriggering, rotary encoding plus numerous other GPIO strategies
* [**H4P_WiFi**](docs/h4wifi.md): Automatic Connection / reconnection manager + AP configuration + OTA + HTTP REST
* [**H4P_AsyncWebServer**](docs/h4asws.md): Fully Asynchronous Webserver
* [**H4P_AsyncMQTT**](docs/h4mqtt.md): Automatic Connection/ reconnection MQTT client allows remote control of H4
* [**H4P_BinarySwitch**](docs/things.md): GPIO object that allows control by commands from multiple sources
* [**H4P_BinaryThing**](docs/xxx.md): user-defined functional object that allows control by commands from multiple sources
* [**H4P_UPNPServer**](docs/things.md): provides full UPNP device with Alexa voice control, Windows10 Desktop integration
* [**H4P_MultiFunctionButton**](docs/h4mfnb.md): Tact-button giving on/off, reboot,factory reset and forced AP Mode depending on hold time
* [**H4P_PersistentStorage**](docs/h4stor.md): Save name/value pairs across reboots (requires SPIFFS)
* [**H4P_H4Detector**](docs/h4pd.md): Execute function when specific H4 device joins / leaves network
* [**H4P_H4DetectorSource**](docs/h4pd.md): Switch default BinarySwitch/Thing when specific H4 device joins / leaves network
* [**H4P_MDNSDetector**](docs/h4pd.md): Execute function when specific MDNS service/protocol found / lost on network
* [**H4P_MDNSDetectorSource**](docs/h4pd.md): Switch default BinarySwitch/Thing when specific MDNS service/protocol found / lost on network
* [**H4P_IPDetector**](docs/h4pd.md): Execute function when specific IP address joins / leaves network
* [**H4P_IPDetectorSource**](docs/h4pd.md): Switch default BinarySwitch/Thing when specific IP address joins / leaves network
* [**H4P_UPNPDetector**](docs/h4pd.md): Execute function when specific UPNP device USN joins / leaves network
* [**H4P_UPNPDetectorSource**](docs/h4pd.md): Switch default BinarySwitch/Thing when specific UPNP device USN joins / leaves network
* [**H4P_RemoteUpdate**](docs/h4ru.md): OTA update from remote server
  
## Diagnostic / Development tools:

* [**H4P_CmdErrors**](docs/h4ce.md): Provide text error messages instead of error codes to SerialCmd
* [**H4P_QueueWarn**](docs/h4qw.md): Call user function on low Queue
* [**H4P_TaskSniffer**](docs/h4ts.md): Low-level task / queue dumper for H4 + Plugins
* [**H4P_SerialLogger**](docs/h4logs.md): Event logging to serial monitor
* [**H4P_LocalLogger**](docs/h4logs.md): Event logging to SPIFFS file
* [**H4P_MQTTLogger**](docs/h4logs.md): Event logging to MQTT Serve
* [**H4P_MQTTHeapLogger**](docs/h4logs.md): Specialised H4P_MQTTLogger which periodically logs value of free heap
* [**H4P_MQTTQueueLogger**](docs/h4logs.md): Specialised H4P_MQTTLogger which periodically logs size of Queue
* [**H4P_HttpMySQLLogger**](docs/mysql.md): log to remote webserver to update MySQL log db (server example provided)
  
## Specialist Device Drivers

* [**H4P_ExternalSqWave**](docs/h4esw.md): Serial driver for cheap ebay square wave device

![sqwv](assets/sqwvhardware.jpg)

---

# Compatible Hardware

* ESP8266 - any board e.g. nodeMCU, Wemos D1 Mini etc
* ESP8285 - any board e.g. Wemos D1 mini Lite
* ESP32 - any board e.g. DevKit, Lolin D32
* STM32-NUCLEO - "official" boards from ST - others may work too
* SONOFF Basic, S20, SV others may work too if ESP8266 based

---

# Installation

H4Plugins is tested using

* H4 0.5.4
* ArduinoIDE 1.8.12
* ESP8266 core 2.6.3
* ESP32 core 1.0.4
* STM32-NUCLEO core 1.8.0

Use the ArduinoIDE boards manager to install those versions. Earlier version *may* work, but am only able to offer support on the above.

H4Plugins is a standard Arduino library. The simplest method is to download the zip form the link above and then use the menu command: `Sketch / Include Library / Add .ZIP Library...`

First you need to install the [H4](https://github.com/philbowles/H4) library. 

Next install the 3rd-party libraries:

* [Async MQTT client library](https://github.com/marvinroger/async-mqtt-client)
* [ESP8266 ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP)
* [ESP8266 ESPAsyncTCP Library](https://github.com/me-no-dev/ESPAsyncTCP)
* [ESP32 AsyncTCP Library](https://github.com/me-no-dev/AsyncTCP)

The above libraries coexist quite happily if you download all of them to enable targetting both ESP8266 and ESP32.

* [ESPAsyncWebServer](https://github.com/philbowles/ESPAsyncWebServer) * See note
* Finally, install this H4Plugins library

(* The standard ESPAyncWebServer library has a long-standing bug in its basic web authentication. I have raised the issue at least twice, but the last time I looked they sill hadn't fixed it, so until then you need to use the patched version from the link above.)

If using WiFi, you will need to install either the [ESP8266 sketch data uploader](https://github.com/esp8266/arduino-esp8266fs-plugin) or the [ESP32 sketch data uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin) (or both) depending on which platform you compile for. 

# Tools / Build Guidelines

To reduce the footprint of the binary code and provide best WiFi / MQTT performance, the following IDE options
are recommended (if available for the chosen board):

See [Advanced Topics](docs/advanced.md) for how to simply add H4 optimised board definitions that will ensure you get the smallest possible binary (and therefore most likelyto be OTA-able)

## For ALL sketches

* Debug Level: NoAssert-NDEBUG
* Exceptions: Disabled

## For WiFi sketches

* lwIP Variant: v2 Higher Bandwidth (No Features)

### **IMPORTANT**

WiFI sketches must reserve SPIFFS space to hold the AP Mode web pages. These take < 64K so allocate the minimum SPIFFS possible that is greater than or equal to 64k and remember to copy the `data` folder to the sketch folder and upload using either the [ESP8266 sketch data uploader](https://github.com/esp8266/arduino-esp8266fs-plugin) or the [ESP32 sketch data uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin) (or both) depending on which platform you compile for.

---

# In the pipeline

* NTP time sync
* Ethernet manager (for STM32 NUCLEO)
* Web-driven OTA (by file upload)
* wifiClient http / https
* ESP32 Bluetooth detector
* ESP32 MDNSDetector
* ESP32 RemoteUpdate

Plus of course any others you think may be useful. Let me know using one of the links below

---

(c) 2020 Phil Bowles h4plugins@gmail.com

* [Youtube channel (instructional videos)](https://www.youtube.com/channel/UCYi-Ko76_3p9hBUtleZRY6g)
* [Blog](https://8266iot.blogspot.com)
* [Facebook Esparto Support / Discussion](https://www.facebook.com/groups/esparto8266/)
* [Facebook H4  Support / Discussion](https://www.facebook.com/groups/444344099599131/)
* [Facebook General ESP8266 / ESP32](https://www.facebook.com/groups/2125820374390340/)
* [Facebook ESP8266 Programming Questions](https://www.facebook.com/groups/esp8266questions/)
* [Facebook IOT with ESP8266 (moderator)}](https://www.facebook.com/groups/1591467384241011/)
* [Facebook ESP Developers (moderator)](https://www.facebook.com/groups/ESP8266/)
* [Support me on Patreon](https://patreon.com/esparto)
