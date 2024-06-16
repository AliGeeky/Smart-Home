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
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

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
    
}
