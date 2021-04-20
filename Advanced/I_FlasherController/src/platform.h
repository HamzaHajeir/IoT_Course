#ifdef ARDUINO_ARCH_ESP32 

#define LED_RED     13
#define LED_YELLOW  12
#define LED_GREEN   14

constexpr int ledPin = 27;

#elif defined(ARDUINO_ARCH_ESP8266)

#define LED_RED     D8
#define LED_YELLOW  D7
#define LED_GREEN   D6
constexpr int ledPin = D5;
#endif