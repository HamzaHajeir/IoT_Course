#include<H4Plugins.h>
H4_USE_PLUGINS(115200,20,false) // Serial baud rate, Q size, SerialCmd autostop
/*

Optional: Allows you to "tag" your tasks with a name* so that you can find them
    easily in the diagnostic dump

    *keep it to 4 chs or the columns won't line up

*/
const char* giveTaskName(uint32_t n){
  static H4_INT_MAP mydata={
    {1,"Tick"},
    {4,"Rude"},
    {13,"Link"}, // don't have to be in order (but why not?)
    {6,"1Tim"}, // don't have to be used (but why not?)
    {49,"10GB"} // Keep them below 50 - IDs 50-99 are used by the system
    };
  return mydata.count(n) ? mydata[n].c_str():"ANON";
}
// if you don't want task naming, just delete the above



void h4setup() {
    h4.everyRandom(5000,10000,[](){ 
    Serial.print(millis());Serial.println(" RUDE INTERRUPTION");
    h4cmd.dumpQ();
  },nullptr,4);

  h4.every(1000,[]{ Serial.print(millis());Serial.println(" PING "); },nullptr,1);  
  
  h4.once(30000,
    []{ Serial.print(millis());Serial.println(" ONE TIME ONLY!!!"); },
    [](){ // chain fn - fires immediately aftery primary completes
      Serial.println("Chained from 1Tim and fire off new task");
      h4.nTimes(11,5000,[](){ // the song is "10 green bottles", but we want to include zero
        uint32_t nBottles=11 - (h4.context->nrq+1);
        Serial.print(nBottles);Serial.println(" green bottles, hangin' on a wall...");
      },nullptr,99);
    },13);
}
/*
    Optional:

        Used ONLY for other libraries that have "loop" / "handle" / "keepalive" functions
        that must be called regularly.

        If you dont have any, delete the whole function
*/
void h4UserLoop(){
  static long prev=0;
  if(millis() - prev > 5000) {
      // e.g. http.handleClient();
      // e.g. mqtt.loop();
      // etc
    Serial.print("USER LOOP\n");
    prev=millis();
  }
}