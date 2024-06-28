// #include<Arduino>
#include "DHT.h"
int ldrPin = A0;  
int ldrValue = 0; 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

///

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(13, OUTPUT); // light
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  
  lcd.init(); // initialize the lcd
  lcd.backlight();

  lcd.clear();
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

  if (h < 55)
  {
    digitalWrite(11, HIGH);
    Serial.print("sonic is work");
  }
  if (h > 70)
  {
    digitalWrite(11, LOW);
    Serial.println("sonic is OFF");
  }

  //
  ldrValue = analogRead(ldrPin);
  String ldrstatus = "";
  String flowerstatus = "";
  String WaterLevel = "";
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  if (ldrValue > 50)
  {
    Serial.println(" lights on");
    ldrstatus = "lights on";
    digitalWrite(13, HIGH);
  }
  else
  {
    Serial.println(" lights Off ");
    ldrstatus = "lights off";
    digitalWrite(13, LOW);
  }

  //
  Serial.print("Raw Moisture Value: ");
  Serial.println(soilMoistureValue);
  if (soilMoistureValue > 380)
  {
    Serial.println("i'm thirsty ");
    flowerstatus = "i'm thirsty";
    if (WaterLevelValue > 30)
    {
      digitalWrite(12, HIGH);
    }
    else
    {
      for (int i = 0; i < 3; i++)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Water Tank");
        lcd.setCursor(1, 1);
        lcd.print("Is Empty");
        delay(1000);
      }
    }
  }
  else if (soilMoistureValue < 380 && soilMoistureValue > 275)
  {
    Serial.println("i'm be OK ");
    flowerstatus = "i'm be OK";
    digitalWrite(12, LOW);
  }
  else
  {
    Serial.println("I'm drowning");
    flowerstatus = "I'm drowning";
    digitalWrite(12, LOW);
  }

  //
  lcd.clear();
  Serial.print("Water Level Value: ");
  Serial.print(WaterLevelValue / 3);
  Serial.println("%");
  if (WaterLevelValue > 300)
  {
    Serial.println("Tank is full!");
    WaterLevel = "Tank is full!";
  }
  else if (WaterLevelValue > 100 && WaterLevelValue < 180)
  {
    Serial.println("Be careful");
    WaterLevel = "Be careful";
  }
  else if (WaterLevelValue > 30 && WaterLevelValue < 100)
  {
    Serial.println("  It's Bad");
    WaterLevel = "It's Bad";
  }
  else if (WaterLevelValue < 10)
  {
    Serial.println("Don't worry!! you have no water !! ");
    WaterLevel = "  Empty !!";
  }
  else
  {
    Serial.println("It's OK");
    WaterLevel = "  It's OK";
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(10, 1);
  lcd.print(h);
  lcd.print("%");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.setCursor(5, 1);
  lcd.print(ldrstatus);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Flower Status : ");
  lcd.setCursor(1, 1);
  lcd.print(flowerstatus);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Status : ");
  lcd.setCursor(1, 1);
  lcd.print(WaterLevel);
}