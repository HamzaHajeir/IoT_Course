#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop



/*
    Open Serial monitor and try typing any of the following:

    * h4/reboot
    * h4/show/Q
    * h4/show/Qstats
    * h4/show/all
    * h4/show/tnames
    * h4/show/unload
    * h4/unload
    * help

*/
void h4setup() { // H4 constructor starts Serial
    Serial.println("H4P_SerialCmd Example v"H4P_VERSION);
    h4cmd.invokeCmd("help"); // Automatically show help at startup
    Serial.println("Show Q caused by invokeCmd");
    h4cmd.invokeCmd("h4/show/Q"); // Automatically show H4 queue at startup
    Serial.println("Show Q caused by call to dumpQ()");
    h4cmd.dumpQ(); // same as above but more efficient
    if(h4cmd.invokeCmd("bogus/nonsense")) Serial.println("Invalid command invoked");
    Serial.println("Show all caused by call to all()");
    h4cmd.all(); // show everything
}
