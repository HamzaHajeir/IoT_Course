#include <Arduino.h>

class Car
{
    String brand;
    String model;
    String yearOfM;
    String color;
    int engineS;

public:
    Car(String brandName, String modelName) : brand(brandName),
                                              model(modelName)
    {
    }

    Car(String brandName, String modelName, String yearOfManufacture, String colorName, int engineSize);

    void runTheCar()
    {
        Serial.printf("Car %s %s which Engine size=%d and %s colored .. is now running\n\n\n", brand.c_str(), yearOfM.c_str(), engineS, color.c_str());
    }

    void setBrandName(String newName);
};

void setup()
{

    Serial.begin(115200);

    Serial.println("Hello");

    Car myCar("Hyundai", "Accent", "2017", "White", 1600);

    myCar.runTheCar();

    delay(2000);
    Car myFriendsCar("Ford", "Fusion", "2015", "Silver", 1600);
    myFriendsCar.runTheCar();

    delay(2000);
    myFriendsCar.setBrandName("Toyota");
    myFriendsCar.runTheCar();

    delay(2000);
    Car thirdCar("BMW", "350i");
    thirdCar.runTheCar();
}

void loop()
{
}

/* in a cpp file */

void Car::setBrandName(String newName)
{
    brand = newName;
}

Car::Car(String brandName, String modelName,
         String yearOfManufacture, String colorName,
         int engineSize) : brand(brandName),
                           model(modelName),
                           yearOfM(yearOfManufacture),
                           color(colorName),
                           engineS(engineSize)
{
}