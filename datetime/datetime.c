/*
 * datetime.c
 *
 *  Created on: 16 May 2016
 *      Author: Bowmer
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "datetime.h"


/* Date Strings */

#define	dt_SHORT_STR_LEN	3
#define	PGM_P				const char *
#define	pgm_read_byte(addr)	(*(const unsigned char *)(addr))
#define pgm_read_word(addr)	(*(const unsigned char **)(addr))


static char buffer[dt_MAX_STRING_LENGTH + 1];

const char monthStr0[] = "";
const char monthStr1[] = "January";
const char monthStr2[] = "February";
const char monthStr3[] = "March";
const char monthStr4[] = "April";
const char monthStr5[] = "May";
const char monthStr6[] = "June";
const char monthStr7[] = "July";
const char monthStr8[] = "August";
const char monthStr9[] = "September";
const char monthStr10[] = "October";
const char monthStr11[] = "November";
const char monthStr12[] = "December";

const char * const monthNames_P[] =
{
		monthStr0,monthStr1,monthStr2,monthStr3,monthStr4,monthStr5,monthStr6,
		monthStr7,monthStr8,monthStr9,monthStr10,monthStr11,monthStr12,
};

const char monthShortNames_P[] = "ErrJanFebMarAprMayJunJulAugSepOctNovDec";

const char dayStr0[] = "Err";
const char dayStr1[] = "Monday";
const char dayStr2[] = "Tuesday";
const char dayStr3[] = "Wednesday";
const char dayStr4[] = "Thursday";
const char dayStr5[] = "Friday";
const char dayStr6[] = "Saturday";
const char dayStr7[] = "Sunday";


const char * const dayNames_P[] =
{
		dayStr0,dayStr1,dayStr2,dayStr3,dayStr4,dayStr5,dayStr6,dayStr7
};

const char dayShortNames_P[] = "ErrMonTueWedThuFriSatSun";

char* monthStr(uint8_t month)
{
	strcpy(buffer, (PGM_P)pgm_read_word(&(monthNames_P[month])));
	return buffer;
}

char* monthShortStr(uint8_t month)
{
	uint8_t index = (month * dt_SHORT_STR_LEN), i;
	for(i=0;i < dt_SHORT_STR_LEN; i++)
	{
		buffer[i] = pgm_read_byte(&(monthShortNames_P[i + index]));
	}
	buffer[dt_SHORT_STR_LEN] = 0;
	return buffer;
}

char* dayStr(uint8_t day)
{
	strcpy(buffer, (PGM_P)pgm_read_word(&(dayNames_P[day])));
	return buffer;
}


char* dayShortStr(uint8_t day)
{
	uint8_t index = (day * dt_SHORT_STR_LEN), i;
	for(i=0;i < dt_SHORT_STR_LEN; i++)
	{
		buffer[i] = pgm_read_byte(&(dayShortNames_P[i + index]));
	}
	buffer[dt_SHORT_STR_LEN] = 0;
	return buffer;
}

/* DateTime */

static tmElements_t tm;
static time_t cacheTime;
static uint32_t syncInterval = 300;

void refreshCache(time_t t)
{
	if(t != cacheTime)
	{
		breakTime(t, tm);
		cacheTime = t;
	}
}


uint32_t hourNow()
{
	return hour(now());
}

uint32_t hour(time_t t)
{
	refreshCache(t);
	return tm.Hour;
}

uint32_t hourFormat12Now()
{
	return hourFormat12(now());
}

uint32_t hourFormat12(time_t t);
{
	refreshCache(t);
	if(tm.Hour == 0)
		return 12;	// Midnight
	else if (tm.Hour > 12)
		return tm.hour - 12;
	else
		return tm.hour;
}
/*
uint8_t isAMNow()
{

}


uint8_t isAM(time_t t)
{

}


uint8_t isPMNow()
{

}


uint8_t isPM(time_t t)
{

}


uint32_t minuteNow()
{

}


uint32_t minute(time_t t)
{

}


uint32_t secondNow()
{

}


uint32_t second(time_t t)
{

}


uint32_t dayNow()
{

}


uint32_t day(time_t t)
{

}


uint32_t weekdayNow()
{

}


uint32_t weekday(time_t t)
{

}


uint32_t monthNow()
{

}


uint32_t month(time_t t)
{

}


uint32_t yearNow()
{

}


uint32_t year(time_t t)
{

}

*/




























