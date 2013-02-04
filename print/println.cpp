//
//  print.cpp
//  ds_motor
//
//  Created by David Cluytens on 12/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include "Arduino.h"
#include "println.h"

static char        buffer[S_WIDTH];

__attribute__ ((noinline)) void println(const char *format, ...) {
    va_list     args;
    
    memset(buffer, 0, sizeof(buffer));
    
    va_start(args, format);
    vsnprintf(buffer, S_WIDTH, format, args);
    va_end(args);
    
    Serial.println(buffer);
}
