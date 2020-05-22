#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);  // Debugging only
    Serial.println("Power");
    if (driver.init() == true)
    {
      Serial.println("Initialized");
    }
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    }
    Serial.println(driver.recv(buf, &buflen));
     Serial.println((char*)buf);   
    if (driver.recv(buf, &buflen) == true)
    {
      Serial.println("Receive Successful");
    }
    else
    {
      Serial.println("Unsucessful receive");
    }
}
