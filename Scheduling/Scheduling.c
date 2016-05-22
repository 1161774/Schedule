/*
 * Header.c
 *
 *  Created on: 18 May 2016
 *      Author: Bowmer
 */


#include "scheduling.h"
#include "../ErrorCodes.h"

void createSchedule(Schedule *s, time_t startTime, time_t endTime, time_t isPeriodic, time_t frequency)
{
	setStartTime(s, startTime, isPeriodic);
	setEndTime(s, endTime);
}

void setStartTime(Schedule *s, time_t t, bool isPeriodic)
{
	s->StartTime = t;
	s->IsPeriodic = isPeriodic;
	if(s->EndTime > 0)
	{
		s->DurationElapsed = updateElapsedTime(s);
	}
	else
	{
		s->DurationElapsed = 0;
	}
}

void setStartTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
	setStartTime(s, getTimeFromParts(year, month, day, hour, minute, second), s->IsPeriodic);
}

void setStartTimeFromNow(Schedule *s, int32_t t)
{
	setStartTime(s, now() + t, s->IsPeriodic);
}

void setStartTimeNow(Schedule *s)
{
	setStartTime(s, now(), s->IsPeriodic);
}



void setEndTime(Schedule *s, time_t t)
{
	s->EndTime = t;
	if(s->StartTime > 0)
	{
		s->DurationElapsed = updateElapsedTime(s);
	}
	else
	{
		s->DurationElapsed = 0;
	}
}

void setEndTimeFromParts(Schedule *s, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
	setEndTime(s, getTimeFromParts(year, month, day, hour, minute, second));
}

void setEndTimeFromNow(Schedule *s, int32_t t)
{
	setEndTime(s, now() + t);
}

void setEndTimeNow(Schedule *s)
{
	setEndTime(s, now());
}

void setPeriodic(Schedule *s, bool isPeriodic)
{
	s->IsPeriodic = isPeriodic;
}

uint16_t updateElapsedTime(Schedule *s)
{
	if(s->StartTime > 0 && s->EndTime > 0)
	{
		if(s->EndTime < s->StartTime)
		{
			s->DurationElapsed = UINT16_MAX;
		}
		else
		{
			uint64_t n = now() - s->StartTime;
			s->DurationElapsed = (n * UINT16_MAX) / (s->EndTime - s->StartTime);
		}
	}
	else
	{
		s->DurationElapsed = 0;
	}

	return s->DurationElapsed;
}

void ackSchedule(Schedule *s)
{
	if(s->IsPeriodic)
	{
		time_t delta = s->EndTime - s->StartTime;
		s->StartTime = s->EndTime;
		s->EndTime += delta;
		updateElapsedTime(s);
	}
	else
	{
		s->StartTime = 0;
		s->EndTime = 0;
		s->DurationElapsed = 0;
	}
}


uint16_t validateComponents(sInitDay id, sInitRelative ir, sInitWeekday iw, sInitMonth im, uint8_t hour, uint8_t minute, sAmpm ap, uint16_t freq, sRepeatFreq rf)
{




	/*
	// Validate hour
	if(hour > 24)
	{
		return INVALID_HOUR;
	}

	// Validate ap
	if((hour > 12 && ap == schAPam) || (hour == 0 && ap == schAPpm))
	{
		return HOUR_AMPM_MISMATCH;
	}

	// Validate minute
	if(minute > 60)
	{
		return INVALID_MINUTE;
	}


	// Validate repeat settings
	if((rf == schRFmonday
			|| rf == schRFtuesday
			|| rf == schRFwednesday
			|| rf == schRFthursday
			|| rf == schRFfriday
			|| rf == schRFsaturday
			|| rf == schRFsunday)
			&& freq > 0)
	{
		return INVALID_RF_FREQ;
	}


	// Validate id

	// if set relative to today or tomorrow, ignore the rest of the parameters
	if(id == schIDtoday || id == schIDtomorrow)
	{
		return 0;
	}






	if(ir == schIRthis && 	( !(id == schIDnull)
							  || iw == schIWday
							  || iw == schIWnull
							  || !(im == schIMnull)))
	{
		return INVALID_THIS;
	}
*/
	return 0;
}




uint16_t getRepeatFreq(Schedule *s, uint16_t freq, sRepeatFreq rf)
{
	switch(rf)
	{
		case schRFminutes:
			s->RepeatFrequency =  minutesToTime_t(freq);
			break;
		case schRFhours:
			s->RepeatFrequency = hoursToTime_t(freq);
			break;
		case schRFdays:
			s->RepeatFrequency = daysToTime_t(freq);
			break;
		case schRFweeks:
			s->RepeatFrequency = weeksToTime_t(freq);
			break;
		case schRFfortnights:
			s->RepeatFrequency = 2 * weeksToTime_t(freq);
			break;
		case schRFnull:
			s->RepeatFrequency = 0;
			break;

		/* Will need to think about these */
		case schRFmonths:
		case schRFyears:
		case schRFmonday:
		case schRFtuesday:
		case schRFwednesday:
		case schRFthursday:
		case schRFfriday:
		case schRFsaturday:
		case schRFsunday:
	}

	return 0;
}

uint8_t schIDtoVal(sInitDay id)
{
	switch(id)
	{
	case(schID1st):
				return 1;
	case(schID2nd):
				return 2;
	case(schID3rd):
				return 3;
	case(schID4th):
				return 4;
	case(schID5th):
				return 5;
	case(schID6th):
				return 6;
	case(schID7th):
				return 7;
	case(schID8th):
				return 8;
	case(schID9th):
				return 9;
	case(schID10th):
				return 10;
	case(schID11th):
				return 11;
	case(schID12th):
				return 12;
	case(schID13th):
				return 13;
	case(schID14th):
				return 14;
	case(schID15th):
				return 15;
	case(schID16th):
				return 16;
	case(schID17th):
				return 17;
	case(schID18th):
				return 18;
	case(schID19th):
				return 19;
	case(schID20th):
				return 20;
	case(schID21st):
				return 21;
	case(schID22nd):
				return 22;
	case(schID23rd):
				return 23;
	case(schID24th):
				return 24;
	case(schID25th):
				return 25;
	case(schID26th):
				return 26;
	case(schID27th):
				return 27;
	case(schID28th):
				return 28;
	case(schID29th):
				return 29;
	case(schID30th):
				return 30;
	case(schID31st):
				return 31;
	default:
	return 0;
	}
}

uint8_t schIMtoVal(sInitMonth im)
{
	switch(im)
	{
	case(schIMofJanuary):
				return 1;
	case(schIMofFebruary):
				return 2;
	case(schIMofMarch):
				return 3;
	case(schIMofApril):
				return 4;
	case(schIMofMay):
				return 5;
	case(schIMofJune):
				return 6;
	case(schIMofJuly):
				return 7;
	case(schIMofAugust):
				return 8;
	case(schIMofSeptember):
				return 9;
	case(schIMofOctober):
				return 10;
	case(schIMofNovember):
				return 11;
	case(schIMofDecember):
				return 12;
	default:
	return 0;
	}
}

uint8_t schIWtoVal(sInitWeekday iw)
{
	switch(iw)
	{
	case(schIWmonday):
				return 1;
	case(schIWtuesday):
				return 2;
	case(schIWwednesday):
				return 3;
	case(schIWthursday):
				return 4;
	case(schIWfriday):
				return 5;
	case(schIWsaturday):
				return 6;
	case(schIWsunday):
				return 7;
	default:
	return 0;
	}
}


uint16_t createScheduleFromComponents(Schedule *s, sInitDay id, sInitRelative ir, sInitWeekday iw, sInitMonth im, uint8_t hour, uint8_t minute, sAmpm ap, uint16_t freq, sRepeatFreq rf)
{
	uint8_t schRelativeDate = 0, schRelativeDay = 0,schRelativeMonth = 0;
	uint32_t dueTime;
	uint16_t validate;
	uint32_t dueYear;
	uint32_t dueDay;


	validate = validateComponents(id, ir, iw, im, hour, minute, ap, freq, rf);

	if(validate > 0)
	{
		return validate;
	}

	dueYear = yearNow();

	// If the start time hasnt been set, then set it to now
/*	silly me, it's not initialised to zero. will have to manually set the start time for now.
 * if(s->StartTime == 0)
	{
		s->StartTime = now();
		updateElapsedTime(s);
	}*/


	// 12am is 0 hours after midnight
	hour = (hour == 12 && ap == schAPam)? 0 : hour;

	// pm is 12 hours, but 12pm is already 12 hours after midnight
	hour = (hour != 12 &&ap == schAPpm)? hour + 12 : hour;

	dueTime = minutesToTime_t(minute) + hoursToTime_t(hour);

	/* should have the due time now */
	/* now for the hard part... */

	// determining what date to set the schedule
	if(id == schIDtoday)
	{
		s->EndTime = (previousMidnight(now()) + dueTime);
		return 0;
	}
	else if(id == schIDtomorrow)
	{
		s->EndTime = nextMidnight(now()) + dueTime;
		return 0;
	}
	// Not today, not tomorrow, not null, must be a 1st-31st
	else if(id !=schIDnull)
	{
		schRelativeDate = schIDtoVal(id);
	}
	// id is null
	else
	{
		// Nothing to do.
	}

	// determining what day to set the schedule
	if(iw == schIWday)
	{
		schRelativeDay = 1;
	}
	else if (iw != schIWnull)
	{
		schRelativeDay = schIWtoVal(iw);
	}
	// iw is null
	else
	{
		// Nothing to do.
	}


	if(ir == schIRthis || ir == schIRnext)
	{
		int8_t today = (int8_t)weekdayNow();
		uint8_t deltaDays;

		for(deltaDays = 1; deltaDays < 10; deltaDays++)
		{
			if(today + deltaDays > 7)
			{
				today -= 7;
			}
			if((today + deltaDays) == schRelativeDay)
			{
				break;
			}
		}

		if(ir == schIRnext)
		{
			deltaDays += 7;
		}

		s->EndTime = previousMidnight(now()) + daysToTime_t(deltaDays) + dueTime;
		return 0;
		//dueDay
	}


	// Determine the month to set the schedule
	if(im == schIMofThisMonth)
	{
		schRelativeMonth = monthNow();
	}
	else if(im == schIMofNextMonth)
	{
		schRelativeMonth = monthNow() + 1;
		// If this month is December, next month is January (citation needed)
		if(schRelativeMonth == 13)
		{
			schRelativeMonth = 1;
			dueYear += 1;
		}
	}
	else if (im == schIMfromToday)
	{
		schRelativeMonth = monthNow();
	}
	else if (im != schIMnull)
	{
		schRelativeMonth = schIMtoVal(im);
	}
	// im is null
	else
	{
		// Nothing to do.
	}



	// schRelativeDate, schRelativeMonth, schRelativeDay





	getRepeatFreq(s, freq, rf);
	return 0;
}


























