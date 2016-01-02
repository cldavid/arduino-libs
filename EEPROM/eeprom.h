//
//  dc_eeprom.h
//  ds_motor
//
//  Created by David Cluytens on 08/10/12.
//  Copyright (c) 2012 Cluytens.net All rights reserved.
//

#ifndef ds_motor_dc_eeprom_h
#define ds_motor_dc_eeprom_h

#include <inttypes.h>
#include "EEPROM.h"

class EEPROMClass {
public:
    uint8_t read(int);
    void    write(int, uint8_t);
    void    read_block(void *dst, const void *src, size_t n);
    void    write_block(const void *src, void *dst, size_t n);
};

extern EEPROMClass EEPROM;


#endif
