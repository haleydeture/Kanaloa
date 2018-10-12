/**************************************************************************/
/*! 
    @file     Adafruit_MCP4725.cpp
    @author   K.Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	I2C Driver for Microchip's MCP4725 I2C DAC

	This is a library for the Adafruit MCP4725 breakout
	----> http://www.adafruit.com/products/935
		
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

  #pragma once
  #define SDA_PORT PORTD
  #define SDA_PIN 44 //Looking at the ports and microcontroller pins chart, this is digital pin 20
  #define SCL_PORT PORTD
  #define SCL_PIN 43 // Looking at the ports and microcontroller pins chart, this is digital pin 21 SCL
  #define I2C_HARDWARE 1 //Must be used for Arduino Megas
  #define I2C_TIMEOUT 5 //Set time outs for lockups
  #define I2C_MAXWAIT 15 //Time outs for a different class I2C related lockups
  //Port chart: http://forum.arduino.cc/index.php?topic=45329.0 
  #include "Adafruit_MCP4725_custom.h"  
#include "SoftI2CMaster.h" //https://github.com/felias-fogg/SoftI2CMaster 

Adafruit_MCP4725::Adafruit_MCP4725(){

};

  void Adafruit_MCP4725::begin(uint8_t addr) {
  _i2caddr = addr;
  i2c_init();
}
 
/**************************************************************************/
/*! 
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)
    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the MCP4725's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
/*
*/
//include on NUC's version of MCP4725 library
void Adafruit_MCP4725::setVoltage( uint16_t output, bool writeEEPROM )
{
#ifdef TWBR
  uint8_t twbrback = TWBR;
  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
#endif
  i2c_start_wait(_i2caddr);
  if (writeEEPROM)
  {
    i2c_write(MCP4726_CMD_WRITEDACEEPROM);
  }
  else
  {
    i2c_write(MCP4726_CMD_WRITEDAC);
  }
  Serial.println(i2c_write(output / 16));// Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  Serial.println(i2c_write((output % 16) << 4));// Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  i2c_stop();
#ifdef TWBR
  TWBR = twbrback;
#endif
}
