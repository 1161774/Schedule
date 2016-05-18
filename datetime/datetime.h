/*
 * datetime.h
 *
 *  Created on: 16 May 2016
 *      Author: Bowmer
 */

#ifndef DATETIME_H_
#define DATETIME_H_

#include <stdbool.h>
#include <stdint.h>


typedef uint64_t time_t;

typedef enum {
	timeNotSet,
	timeNeedsSync,
	timeSet
} timeStatus_t;

typedef enum {
	dowInvalid,
	dowSunday,
	dowMonday,
	dowTuesday,
	dowWednesday,
	dowThursday,
	dowFriday,
	dowSaturday
} timeDayOfWeek_t;

typedef enum {
	tmSecond,
	tmMinute,
	tmHour,
	tmWday,
	tmDay,
	tmMonth,
	tmYear,
	tmNbrFields
} tmByteFields_t;

typedef struct {
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Wday;	// Day of week, Monday is 1, Sunday is 7
	uint8_t Day;
	uint8_t Month;
	uint8_t Year;	// Offset from 2000
} tmElements_t;



#define	tmYearToCalendar(Y)	((Y) + 2000)
#define	CalendarToTmYear(Y)	((Y) - 2000)

typedef time_t(*getExternalTime)();

#define	SECS_PER_MIN	60
#define SECS_PER_HOUR	3600
#define	SECS_PER_DAY	86400
#define	DAYS_PER_WEEK	7
#define	SECS_PER_WEEK	604800
#define SECS_PER_YEAR	31536000

#define	numberOfSeconds(_time_)		(_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_)		((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define	numberOfHours(_time_)		((_time_ % SECS_PER_DAY) / SECS_PER_HOUR)
#define	dayOfWeek(_time_)			(((_time / SECS_PER_DAY + 6) % DAYS_PER_WEEK) + 1)	// 1 = Monday
#define	elapsedDays(_time)			(_time / SECS_PER_DAY)								// Number of days since 2000-01-01
#define	elapsedSecsToday(_time_)	(_time_ % SECS_PER_DAY)								// Number of seconds since last midnight

#define	previousMidnight(_time_)	((_time_ / SECS_PER_DAY) * SECS_PER_DAY)			// Time at the start of the given day
#define	nextMidnight(_time)			( previousMidnight(_time) + SECS_PER_DAY)			// Time and the start of the next day
#define	elapsedSecsThisWeek(_time_)	(elapsedSecsToday(_time_) + ((dayOfWeek(_time_)) - 1) * SECS_PER_DAY)	//
#define	previousMonday(_time)		(_time_ - elapsedSecsThisWeek(_time_))
#define	nextMonday(_time_)			(previousMonday(_time_) + SECS_PER_WEEK)


#define	minutesToTime_t(M)	(M * SECS_PER_MIN)
#define hoursToTime_t(H)	(H * SECS_PER_HOUR)
#define daysToTime_t(D)		(D * SECS_PER_DAY)
#define weeksToTime_t(W)	(W * SECS_PER_WEEK)


extern	uint32_t	hourNow();				// The hour now
extern	uint32_t	hour(time_t t);			// The hour for the given time
extern	uint32_t	hourFormat12Now();
extern	uint32_t	hourFormat12(time_t t);	//
extern	uint8_t		isAMNow();
extern	uint8_t		isAM(time_t t);
extern	uint8_t		isPMNow();
extern	uint8_t		isPM(time_t t);
extern	uint32_t	minuteNow();
extern	uint32_t	minute(time_t t);
extern	uint32_t	secondNow();
extern	uint32_t	second(time_t t);
extern	uint32_t	dayNow();
extern	uint32_t	day(time_t t);
extern	uint32_t	weekdayNow();
extern	uint32_t	weekday(time_t t);
extern	uint32_t	monthNow();
extern	uint32_t	month(time_t t);
extern	uint32_t	yearNow();
extern	uint32_t	year(time_t t);

extern	time_t		now();					// Current time as seconds since 2000-01-01

extern	void	setTime(time_t t);
extern	void	setTimeFromParts(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);
extern	void	adjustTime(uint64_t adjustment);

extern	time_t	getTimeFromParts(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);

#define	dt_MAX_STRING_LENGTH	9
extern	char*	monthStr(uint8_t month);
extern	char*	dayStr(uint8_t day);
extern	char*	monthShortStr(uint8_t month);
extern	char*	dayShortStr(uint8_t day);


extern	timeStatus_t	timeStatus();
extern	void			setSyncProvider(getExternalTime getTimeFunction);
extern	void			setSyncInterval(time_t interval);

extern	void	breakTime(time_t timeInput, tmElements_t *tm);	// Break time_t into elements
extern	time_t	makeTime(tmElements_t *tm);					// Convert elements into time_t


#endif /* DATETIME_H_ */
