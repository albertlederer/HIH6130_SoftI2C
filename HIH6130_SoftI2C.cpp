/**************************************************************************/
/*!
    @file     HIH6130.cpp
    @author   Albert Lederer
    @license  see license.txt)

    This is a library for the HIH6130 humidity sensor.

    This is a third-party library for the HIH6130
	humidity sensor.  The author of this library

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <DigitalIO.h>

#include "HIH6130_SoftI2C.h"

/**************************************************************************/
/*!
    @brief  Instantiates a new HIH6130 class
*/
/**************************************************************************/
HIH6130_SoftI2C::HIH6130_SoftI2C(SoftI2cMaster *i2cMaster) {
	i2c = i2cMaster;
}

/**************************************************************************/
/*!
    @brief  Setups the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
void HIH6130_SoftI2C::begin() {
}

/**************************************************************************/
/*!
    @brief  Gets the relative humidity in percent.
*/
/**************************************************************************/
float HIH6130_SoftI2C::getHumidity() {
  float     relHum,centigrade;

  getHT(&relHum, &centigrade);
  return relHum;
}


/**************************************************************************/
/*!
    @brief  Gets the floating-point temperature in Centigrade
*/
/**************************************************************************/
float HIH6130_SoftI2C::getTemperature() {
  float     relHum, centigrade;

  getHT(&relHum, &centigrade);
  return centigrade;
}

/**************************************************************************/
/*!
    @brief  Gets both at once and saves a little time
*/
/**************************************************************************/
void HIH6130_SoftI2C::getHT(float *H, float *T) {
  uint16_t 	humidity, temp;
  float     humidityComp;
  byte Hum_H, Hum_L, Temp_H, Temp_L, _status;
  unsigned int H_dat, T_dat;

  uint8_t address = 0x00;
  i2c->transfer(HIH6130_ADDRESS | I2C_WRITE, &address, 1, I2C_STOP);  
  delay(5);
  uint8_t buf[4] = { 0 };
  i2c->transfer(HIH6130_ADDRESS | I2C_READ, &buf, 4, I2C_STOP);


/*	
  // Get raw pressure and temperature settings
  Wire.beginTransmission(HIH6130_ADDRESS);
  Wire.endTransmission();

  // Wait a bit for the conversion to complete (3ms max)
  delay(100);
  Wire.requestFrom((int)HIH6130_ADDRESS, (int) 4);
  Hum_H = Wire.read();
  Hum_L = Wire.read();
  Temp_H = Wire.read();
  Temp_L = Wire.read();
  Wire.endTransmission();
  */
  
  Hum_H = buf[0];
  Hum_L = buf[1];
  Temp_H = buf[2];
  Temp_L = buf[3];
  
  _status = (Hum_H >> 6) & 0x03;
  Hum_H = Hum_H & 0x3f;
  H_dat = (((unsigned int)Hum_H) << 8) | Hum_L;
  T_dat = (((unsigned int)Temp_H) << 8) | Temp_L;
  T_dat = T_dat / 4;

  
  // Return humidity and temperature as floating point values
  *H = (float)H_dat * 6.10e-3F;
  *T = (float)T_dat * 1.007e-2 - 40.0;
  
}



