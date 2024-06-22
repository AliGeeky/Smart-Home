//#include<Arduino>
#include "DHT.h"
int ldrPin = A0;  // َAnalog pin
int ldrValue = 0; // متغیری برای ذخیره مقدار خوانده شده از فتوسل

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    dht.begin();
    pinMode(13, HIGH);
}

void loop()
{
    delay(5000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int soilMoistureValue = analogRead(A1);
    int WaterLevelValue = analogRead(A2);
    Serial.println("#######################");
    if (isnan(h) || isnan(t))
    {
        Serial.println("Error!!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.println(" *C ");
    //
    ldrValue = analogRead(ldrPin); 
    Serial.print("LDR Value: ");   
    if(ldrValue >50){
      Serial.println(" lights on");
      digitalWrite(13, HIGH);
    }
    else{
      Serial.println(" lights Off ");
      digitalWrite(13, LOW);
    }
    Serial.println(ldrValue);
    delay(500);
    //
    Serial.print("Raw Moisture Value: ");
    Serial.println(soilMoistureValue);
    if (soilMoistureValue > 380){
      Serial.println("i'm thirsty ");
    }
    else if (soilMoistureValue < 380 && soilMoistureValue > 275)
    {
      Serial.println("i'm be OK ");
    }
    else
    {
      Serial.println("I'm drowning");
    }
    delay(101);
    //
    Serial.print("Water Level Value: ");
    Serial.print(WaterLevelValue/3);
    Serial.println("%");
    if (WaterLevelValue > 300){
      Serial.println("Tank is full!");
    }
    else if (WaterLevelValue > 100 && WaterLevelValue < 180)
    {
      Serial.println("Be careful");
    }
    else if (WaterLevelValue > 30 && WaterLevelValue < 100)
    {
      Serial.println("It's Bad");
    }
    else if (WaterLevelValue < 10)
    {
      Serial.println("Don't worry!! you have no water !! ");
    }
    else{
      Serial.println("It's OK");
    }
}
