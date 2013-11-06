/**************************************************************************/
/*!
    @file     HIH6130.h
    @author   Albert Lederer
    @license  see license.txt

    This is a library for the HIH6130 humidity sensor.

    This is a third-party library for the HIH6130
	humidity sensor breakout board.

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

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
	#define HIH6130_ADDRESS                       0x4E 
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/

/*=========================================================================*/

class HIH6130_SoftI2C{
 public:
  HIH6130_SoftI2C(SoftI2cMaster *i2cMaster);
  void begin(void);
  float getHumidity(void);
  float getTemperature(void);
  void getHT(float *H, float *T);

 private:
  SoftI2cMaster *i2c;
};
