/*
 * Scheduling.h
 *
 *  Created on: 18 May 2016
 *      Author: Bowmer
 */


/**
 *
 * DUE ON THE	|				|				|				|at 	|		|repeat every 	|
 * ____________________________________________________________________________________________________________
 * 1st			|this			|day			|of this month	|xx:xx	|am		|x				|minutes
 * 2nd			|next			|monday			|of next month	|		|pm		|				|hours
 * 3rd			|last			|..				|of Jan			|		|		|				|days
 * ..			|				|sunday			|..				|		|		|				|weeks
 * 31st			|				|				|of Dec			|		|		|				|fortnights
 * today		|				|				|from today		|		|		|				|months
 * tomorrow		|				|				|				|		|		|				|years
 * 				|				|				|				|		|		|				|monday
 * 				|				|				|				|		|		|				|..
 * 				|				|				|				|		|		|				|sunday
 * ____________________________________________________________________________________________________________
 * sInitDay		|sInitRelative	|sInitWeekday	|sInitMonth		|time_t	|sAmpm	|uint16_t		|sRepeatFreq
 *
 *
 *
 * Examples:
 * Weekly bin: 			Due on the THIS WEDNESDAY at 8 PM repeat every WEDNESDAY
 * Fortnightly bin:		Due on the THIS WEDNESDAY at 8 PM repeat every 2 WEEKS
 * OR:					Due on the NEXT WEDNESDAY at 8 PM repeat every FORTNIGHT
 * Sweep the floor:		Due on the LAST DAY OF THIS MONTH at 5 PM repeat every 60 DAYS
 * finish the milk:		Due on the 7TH DAY FROM TODAY at 5PM
 * pay the rent:		Due on the 27TH DAY OF THIS MONTH at 12PM repeat every 14 DAYS
 * This arvo:			Due on the TODAY at 17:34
 * This arvo repeat:	Due on the TODAY at 17:34 repeat every 1 months
 *
 *
 * **/

#ifndef SCHEDULING_SCHEDULING_H_
#define SCHEDULING_SCHEDULING_H_

#include <stdbool.h>
#include <stdint.h>
#include "../datetime/datetime.h"

#endif /* SCHEDULING_SCHEDULING_H_ */


typedef enum
{
	schID1st,
	schID2nd,
	schID3rd,
	schID4th,
	schID5th,
	schID6th,
	schID7th,
	schID8th,
	schID9th,
	schID10th,
	schID11th,
	schID12th,
	schID13th,
	schID14th,
	schID15th,
	schID16th,
	schID17th,
	schID18th,
	schID19th,
	schID20th,
	schID21st,
	schID22nd,
	schID23rd,
	schID24th,
	schID25th,
	schID26th,
	schID27th,
	schID28th,
	schID29th,
	schID30th,
	schID31st,
	schIDtoday,
	schIDtomorrow,
	schIDnull
} sInitDay;

typedef enum
{
	schIRthis,
	schIRnext,
	schIRlast,
	schIRnull
} sInitRelative;

typedef enum
{
	schIWday,
	schIWmonday,
	schIWtuesday,
	schIWwednesday,
	schIWthursday,
	schIWfriday,
	schIWsaturday,
	schIWsunday,
	schIWnull
} sInitWeekday;

typedef enum
{
	schIMofThisMonth,
	schIMofNextMonth,
	schIMofJanuary,
	schIMofFebruary,
	schIMofMarch,
	schIMofApril,
	schIMofMay,
	schIMofJune,
	schIMofJuly,
	schIMofAugust,
	schIMofSeptember,
	schIMofOctober,
	schIMofNovember,
	schIMofDecember,
	schIMfromToday,
	schIMnull
} sInitMonth;

typedef enum
{
	schAPam,
	schAPpm,
	schAPnull
} sAmpm;

typedef enum
{
	schRFminutes,
	schRFhours,
	schRFdays,
	schRFweeks,
	schRFfortnights,
	schRFmonths,
	schRFyears,
	schRFmonday,
	schRFtuesday,
	schRFwednesday,
	schRFthursday,
	schRFfriday,
	schRFsaturday,
	schRFsunday,
	schRFnull
} sRepeatFreq;

typedef struct
{
	time_t		StartTime;
	time_t		EndTime;
	uint16_t	DurationElapsed;
	bool		IsPeriodic;
	time_t		RepeatFrequency;
} Schedule;

extern	void createSchedule(Schedule *s, time_t startTime, time_t endTime, time_t isPeriodic, time_t frequency);
extern	uint16_t createScheduleFromComponents(Schedule *s, sInitDay id, sInitRelative ir, sInitWeekday iw, sInitMonth im, uint8_t hour, uint8_t minute, sAmpm ap, uint16_t freq, sRepeatFreq rf);

extern	void setStartTime(Schedule *s, time_t t, bool isPeriodic);
extern	void setStartTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);
extern	void setStartTimeFromNow(Schedule *s, int32_t t);
extern	void setStartTimeNow(Schedule *s);

extern	void setEndTime(Schedule *s, time_t t);
extern	void setEndTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);
extern	void setEndTimeFromNow(Schedule *s, int32_t t);
extern	void setEndTimeNow(Schedule *s);

extern	void setPeriodic(Schedule *s, bool isPeriodic);
extern	uint16_t updateElapsedTime(Schedule *s);

extern	void ackSchedule(Schedule *s);

