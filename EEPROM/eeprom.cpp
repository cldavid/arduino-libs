//
//  dc_eeprom.cpp
//  ds_motor
//
//  Created by David Cluytens on 08/10/12.
//  Copyright (c) 2012 Cluytens.net All rights reserved.
//

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <avr/eeprom.h>
#include "Arduino.h"
#include "eeprom.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * User API
 ******************************************************************************/

void EEPROMClass::read_block(void *dst, const void *src, size_t n)
{
    eeprom_busy_wait();
    eeprom_read_block(dst, src, n);	
}

void EEPROMClass::write_block(const void *src, void *dst, size_t n)
{
    eeprom_busy_wait();
    eeprom_write_block(src, dst, n);
}

uint8_t EEPROMClass::read(int address)
{
    eeprom_busy_wait();
	return eeprom_read_byte((unsigned char *) address);
}

void EEPROMClass::write(int address, uint8_t value)
{
    eeprom_busy_wait();
	eeprom_write_byte((unsigned char *) address, value);
}

EEPROMClass EEPROM;