#include <Arduino.h>

String myName = "HamzaHajeir";
String myBirthYear = "1995";
 
void setup(){
   
    Serial.begin(115200);
    Serial.println("myName variable = " + myName );
    
 
    myName.toUpperCase();
   
    int birthDate = myBirthYear.toInt();

 
    Serial.println("myName variable =" + myName );
    Serial.println("myBirthYear variable =" + myBirthYear );
    Serial.println("I am "+ String(2020-birthDate) +" Years old." );
   
}
 
void loop(){
 
}
