#include <stdio.h>
#include <string.h>
#include "println.h"
#include "time.h"

static const char *strWday[] 	= {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
static const char *strMonth[] 	= {"January", "Februari", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

#define LEAP_YEAR(Y)     (((Y)>0) && !((Y)%4) && ( ((Y)%100) || !((Y)%400)))

void TimeClass::time_init() {
	memset(&sysTime, 0, sizeof(tv_t));
    
    return;
}

void TimeClass::updateTime(unsigned long curTime) {
	unsigned long dt;
	unsigned long el_ms;
	unsigned long el_sec;
	if (sysTime.prev_millis > curTime){                         //Detect time overflow
		dt      = curTime - sysTime.prev_millis + MILLIS_MAX ;  //Correct overflow
	} else {
		dt      = curTime - sysTime.prev_millis;
	}

	el_ms                   = sysTime.tv_ms + dt;
	sysTime.tv_ms           = el_ms % 1000;
	el_sec                  = el_ms / 1000;
	sysTime.tv_sec         += el_sec;
	sysTime.prev_millis     = curTime;    
    return;
}

void TimeClass::setUnixTime(unsigned long epoch) {
	sysTime.tv_sec  = epoch;
	sysTime.tv_ms   = 0;    
    return;
}

unsigned long TimeClass::getUnixTime() {
	return sysTime.tv_sec;
}

void TimeClass::getTime(struct tm *time) {
    unsigned long tmp   = getUnixTime();

	const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
	unsigned long days  = 0;
	unsigned int  month = 0;
	unsigned int  monthLength = 0;
	unsigned int  year  = 1970;

	time->tm_sec        = tmp % 60;
	tmp                /= 60;
	time->tm_min        = tmp % 60;
	tmp                /= 60;
	time->tm_hour       = tmp % 24;
	tmp                /= 24;
	time->tm_wday       = (tmp + 4) % 7;

	while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= tmp) {
		year++;
	}
	time->tm_year = year - 1970;
	days -= LEAP_YEAR(year) ? 366 : 365;
	tmp  -= days; // now it is days in this year, starting at 0
	time->tm_yday = tmp;

	days=0;
	month=0;
	monthLength=0;
	for (month=0; month<12; month++) {
		if (month==1) { // february
			if (LEAP_YEAR(year)) {
				monthLength=29;
			} else {
				monthLength=28;
			}
		} else {
			monthLength = monthDays[month];
		}

		if (tmp >= monthLength) {
			tmp -= monthLength;
		} else {
			break;
		}
	}
	time->tm_mon    = month;
	time->tm_mday   = tmp + 1;   // day of month
}

void TimeClass::ctime(char *buffer, size_t size) {
	struct tm time;

	getTime(&time);
	snprintf(buffer, size, "%02d-%02d-%d %02d:%02d:%02d",
			time.tm_mday,
			time.tm_mon + 1,
			time.tm_year + 1970,
			time.tm_hour,
			time.tm_min,
			time.tm_sec);
}

const char *TimeClass::getHumanTime(void){
    Time.ctime(humanTime, sizeof(humanTime));
    return humanTime;
}
TimeClass Time;
