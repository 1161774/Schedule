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
		breakTime(t, &tm);
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

uint32_t hourFormat12(time_t t)
{
	refreshCache(t);
	if(tm.Hour == 0)
		return 12;	// Midnight
	else if (tm.Hour > 12)
		return tm.Hour - 12;
	else
		return tm.Hour;
}

uint8_t isAMNow()
{
	return !isPM(now());
}


uint8_t isAM(time_t t)
{
	return !isPM(t);
}


uint8_t isPMNow()
{
	return isPM(now());
}


uint8_t isPM(time_t t)
{
	return (hour(t) >= 12);
}


uint32_t minuteNow()
{
	return minute(now());
}


uint32_t minute(time_t t)
{
	refreshCache(t);
	return tm.Minute;
}


uint32_t secondNow()
{
	return second(now());
}


uint32_t second(time_t t)
{
	refreshCache(t);
	return tm.Second;
}


uint32_t dayNow()
{
	return day(now());
}


uint32_t day(time_t t)
{
	refreshCache(t);
	return tm.Day;
}


uint32_t weekdayNow()
{
	return weekday(now());
}


uint32_t weekday(time_t t)
{
	refreshCache(t);
	return tm.Wday;
}


uint32_t monthNow()
{
	return month(now());
}


uint32_t month(time_t t)
{
	refreshCache(t);
	return tm.Month;
}


uint32_t yearNow()
{
	return year(now());
}


uint32_t year(time_t t)
{
	refreshCache(t);
	return tm.Year;
}


#define	LEAP_YEAR(Y)	(((2000 + Y) > 0) && !((2000 + Y) % 4) && (((2000 + Y) % 100) || !((2000 + Y) % 400)))

static const uint8_t monthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

extern uint64_t millis;


void breakTime(time_t timeInput, tmElements_t *tm)
{

	uint8_t year;
	uint8_t month, monthLength;
	uint64_t time;
	unsigned long days;

	time = (uint64_t)timeInput;
	tm->Second = time % 60;
	time /= 60;
	tm->Minute = time % 60;
	time /= 60;
	tm->Hour = time % 24;
	time /= 24;
	tm->Wday = ((time + 5) % 7) + 1;

	year = 0;
	days = 0;
	while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
	    year++;
	}
	tm->Year = year;

	days -= LEAP_YEAR(year) ? 366 : 365;
	time -= days;

	days = 0;
	month = 0;
	monthLength = 0;
	for(month=0; month < 12; month++)
	{
		if(month == 1)
		{
			if(LEAP_YEAR(year))
			{
				monthLength = 29;
			}
			else
			{
				monthLength = 28;
			}
		}
		else
		{
			monthLength = monthDays[month];
		}

		if(time >= monthLength)
		{
			time -= monthLength;
		}
		else
		{
			break;
		}
	}

	tm->Month = month + 1;
	tm->Day = time + 1;
}


time_t makeTime(tmElements_t *tm){

  int16_t i;
  uint32_t seconds;

  seconds= tm->Year*(SECS_PER_DAY * 365);
  for (i = 0; i < tm->Year; i++) {
    if (LEAP_YEAR(i)) {
      seconds +=  SECS_PER_DAY;   // add extra days for leap years
    }
  }

  // add days for this year, months start from 1
  for (i = 1; i < tm->Month; i++) {
    if ( (i == 2) && LEAP_YEAR(tm->Year)) {
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
    }
  }
  seconds += (tm->Day-1) * SECS_PER_DAY;
  seconds += tm->Hour * SECS_PER_HOUR;
  seconds += tm->Minute * SECS_PER_MIN;
  seconds += tm->Second;
  return (time_t)seconds;
}

static uint32_t sysTime = 0;
static uint32_t prevMillis = 0;
static uint32_t nextSyncTime = 0;
static timeStatus_t Status = timeNotSet;

getExternalTime getTimePtr;



time_t now() {
	// calculate number of seconds passed since last call to now()
  while (millis - prevMillis >= 1000) {
		// millis() and prevMillis are both unsigned ints thus the subtraction will always be the absolute value of the difference
    sysTime++;
    prevMillis += 1000;
  }
  if (nextSyncTime <= sysTime) {
    if (getTimePtr != 0) {
      time_t t = getTimePtr();
      if (t != 0) {
        setTime(t);
      } else {
        nextSyncTime = sysTime + syncInterval;
        Status = (Status == timeNotSet) ?  timeNotSet : timeNeedsSync;
      }
    }
  }
  return (time_t)sysTime;
}

void setTime(time_t t) {
  sysTime = (uint32_t)t;
  nextSyncTime = (uint32_t)t + syncInterval;
  Status = timeSet;
  prevMillis = millis;
}


time_t	getTimeFromParts(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
	tmElements_t t;
	  if( year > 99)
	  {
		  year = year - 2000;
	  }
	  t.Year = year;
	  t.Month = month;
	  t.Day = day;
	  t.Hour = hour;
	  t.Minute = minute;
	  t.Second = second;

	  return makeTime(&t);
}


void setTimeFromParts(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{


	setTime(getTimeFromParts(year, month, day, hour, minute, second));
}



void adjustTime(uint64_t adjustment) {
  sysTime += adjustment;
}

// indicates if time has been set and recently synchronized
timeStatus_t timeStatus() {
  now(); // required to actually update the status
  return Status;
}

void setSyncProvider( getExternalTime getTimeFunction){
  getTimePtr = getTimeFunction;
  nextSyncTime = sysTime;
  now(); // this will sync the clock
}

void setSyncInterval(time_t interval){ // set the number of seconds between re-sync
  syncInterval = (uint32_t)interval;
  nextSyncTime = sysTime + syncInterval;
}


uint8_t getDaysToNextDay(int8_t startDOW, uint8_t endDOW)
{
	uint8_t deltaDays;

	for(deltaDays = 1; deltaDays < 10; deltaDays++)
	{
		if(startDOW + deltaDays > 7)
		{
			startDOW -= 7;
		}
		if((startDOW + deltaDays) == endDOW)
		{
			return deltaDays;
		}
	}
	// shouldn't get here
	return 0;
}


uint8_t daysInMonth(uint8_t year, uint8_t month)
{
	if(month > 0 && month < 13)
	{
	    if ((month == 2) && LEAP_YEAR(year)) {
	      return 29;
	    }
	    else
	    {
	      return monthDays[month - 1];  //monthDay array starts from 0
	    }
	}
	return 0;
}

uint8_t	weekdaysInMonth(uint8_t year, uint8_t month, uint8_t wday)
{
	uint8_t mDays = daysInMonth(year, month);
	uint8_t mStartDay = weekday(getTimeFromParts(year, month, 1, 0, 0, 0));

	// There will always either be 4 or 5 weekdays in any month
	uint8_t maxDeltaDays = mDays - 28;
	uint8_t deltaDays = wday >= mStartDay ? wday - mStartDay : (wday + 7) - mStartDay;

	return deltaDays < maxDeltaDays ? 5 : 4;

}













