#include <Arduino.h>

String myName = "HamzaHajeir";
String myBirthYear = "1995";

void setup()
{

    Serial.begin(115200);
    Serial.println("myName variable = " + myName);

    myName.toUpperCase();

    int birthDate = myBirthYear.toInt();    // Parse the ineger value from the String.

    Serial.println("myName variable =" + myName);
    Serial.println("myBirthYear variable =" + myBirthYear);
    Serial.println("I am " + String(2021 - birthDate) + " Years old."); // Perform a mathmatical equation upon value as integer.
}

void loop()
{
}
