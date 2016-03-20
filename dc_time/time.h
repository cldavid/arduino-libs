//
//  time.h
//  ds_motor
//
//  Created by David Cluytens on 08/10/12.
//  Copyright (c) 2012 Cluytens.net All rights reserved.
//

/* Enable if you want to use ctime and the other human friendly time functions */
/* This will increase the code size with +- 2124 bytes */
 
// #define __DC_TIME_HAS_HUMAN_TIME__ 1

#ifndef __DC_TIME__
#define __DC_TIME__
#include <stddef.h>
#include <stdint.h>
#define MILLIS_MAX          0xFFFFFFFF + 1 //unsigned long max

typedef struct {
	unsigned long tv_sec;           //Number of seconds since either boot or 1 Januari 1980 blabla :)
	unsigned long tv_ms;            //Milliseconds
	unsigned long prev_millis;      //Time in milliseconds since the board was started
} tv_t;

#ifdef __DC_TIME_HAS_HUMAN_TIME__
struct tm {
	uint8_t 	tm_sec;     /* seconds after the minute [0-60] */
	uint8_t 	tm_min;     /* minutes after the hour [0-59] */
	uint8_t 	tm_hour;    /* hours since midnight [0-23] */
	uint8_t 	tm_mday;    /* day of the month [1-31] */
	uint8_t 	tm_mon;     /* months since January [0-11] */
	uint8_t 	tm_year;    /* years since 1900 */
	uint8_t 	tm_wday;    /* days since Sunday [0-6] */
	uint16_t 	tm_yday;    /* days since January 1 [0-365] */
};

#endif //__DC_TIME_HAS_HUMAN_TIME__

class TimeClass {
    tv_t        sysTime;
    char        humanTime[24];

public:
    void time_init(void);
    void updateTime(unsigned long curTime);
    void setUnixTime(unsigned long epoch);
    unsigned long getUnixTime(void);
#ifdef __DC_TIME_HAS_HUMAN_TIME__
    void ctime(char *buffer, size_t size);
    const char *getHumanTime();
    void getTime(struct tm *time);
#endif //__DC_TIME_HAS_HUMAN_TIME__
};

extern TimeClass Time;

#endif //__DC_TIME__
