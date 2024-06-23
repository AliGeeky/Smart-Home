//#include<Arduino>
#include "DHT.h"
int ldrPin = A0;  // َAnalog pin
int ldrValue = 0; // متغیری برای ذخیره مقدار خوانده شده از فتوسل
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

///

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(13, HIGH);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");


}

void loop()
{
    delay(2000);
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
    Serial.println(ldrValue); 
    if(ldrValue >50){
      Serial.println(" lights on");

      digitalWrite(13, HIGH);
    }
    else{
      Serial.println(" lights Off ");
      digitalWrite(13, LOW);
    }
    
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

 
    lcd.setCursor(6, 0);
    lcd.print(t);
    lcd.print(" C");
    lcd.setCursor(10, 1);
    lcd.print(h);
    lcd.print("%");



}