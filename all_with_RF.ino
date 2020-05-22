



#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

#include<Wire.h>
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;



//-----------------------------------------------------------------------------------------------------------------------------------------------------

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
  
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------



void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(333);



    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");

    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.println(F("°F"));






  char result1[8]; // Buffer big enough for 7-character float
  dtostrf(h, 6, 2, result1); // Leave room for too large numbers!

char result2[8]; // Buffer big enough for 7-character float
  dtostrf(t, 6, 2, result2); // Leave room for too large numbers!

  char result3[8]; // Buffer big enough for 7-character float
  dtostrf(bmp.readAltitude(), 6, 2, result3); // Leave room for too large numbers!

  char result4[8]; // Buffer big enough for 7-character float
  dtostrf(AcX, 6, 2, result4); // Leave room for too large numbers!

  char result5[8]; // Buffer big enough for 7-character float
  dtostrf(AcY, 6, 2, result5); // Leave room for too large numbers!

  char result6[8]; // Buffer big enough for 7-character float
  dtostrf(AcZ, 6, 2, result6); // Leave room for too large numbers!









    
    driver.send((uint8_t *)result1, strlen(result1));
    if (driver.send((uint8_t *)result1, strlen(result1)) == true)
    {
      Serial.println("Send Successful");
    }
    driver.waitPacketSent();
    delay(10);
    driver.send((uint8_t *)result2, strlen(result2));
    driver.waitPacketSent();
    delay(10);
    driver.send((uint8_t *)result3, strlen(result3));
    driver.waitPacketSent();
    delay(10);
    driver.send((uint8_t *)result4, strlen(result4));
    driver.waitPacketSent();
    delay(10);
    driver.send((uint8_t *)result5, strlen(result5));
    driver.waitPacketSent();
    delay(10);
    driver.send((uint8_t *)result6, strlen(result6));
    driver.waitPacketSent();
    delay(10);

}
