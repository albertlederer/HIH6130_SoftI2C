#include <HIH6130_SoftI2C.h>
#include <DigitalIO.h>

const uint8_t SDA_PIN = A4;
const uint8_t SCL_PIN = A5;

SoftI2cMaster i2c(SCL_PIN, SDA_PIN);

HIH6130_SoftI2C humiditySensor(&i2c); 

void setup() {
  humiditySensor.begin();

}

void loop() {
  float humidityHih = 0, temperatureHih = 0;

  humiditySensor.getHT(&humidityHih, &temperatureHih);
  Serial.print("Humidity: "); Serial.print(humidityHih, 4); Serial.print(" %; ");
  Serial.print("Temperature: "); Serial.print(temperatureHih, 1); Serial.println(" C"); 
  
  delay(1000);
  
}
