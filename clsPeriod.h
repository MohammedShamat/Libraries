#pragma once
#include "clsDate.h"
#include <iostream>
using namespace std;

class clsPeriod : private clsDate
{
public:

	clsDate startDate;
	clsDate endDate;

	clsPeriod(clsDate StartDate, clsDate DateTo)
	{
		this->startDate = StartDate;
		this->endDate = DateTo;
	}
	void Print()
	{
		cout << "Period Start: ";
		startDate.PrintDate();

		cout << "Period End: ";
		endDate.PrintDate();

	}

	static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
	{
		if (
			clsDate::CompareDate(Period2.endDate, Period1.startDate) == clsDate::enDateCompare::Before
			||
			clsDate::CompareDate(Period2.startDate, Period1.endDate) == clsDate::enDateCompare::After
			)
			return false;
		else
			return true;

	}
	bool IsOverlapPeriods(clsPeriod Period2)
	{
		return IsOverlapPeriods(*this, Period2);
	}

	static int PeriodLengthInDays(clsPeriod period, bool includeEndDay = false) {
		return CalculateDifferenceBetweenTwoDates(period.startDate, period.endDate, includeEndDay);
	}
	int PeriodLengthInDays(bool includeEndDay = false) {
		return PeriodLengthInDays(*this, includeEndDay);
	}

	static bool DateIsWithinPeriod(clsPeriod period, clsDate date) {
		return !(CompareDate(date, period.startDate) == enDateCompare::Before ||
			CompareDate(date, period.endDate) == enDateCompare::After);
	}
	bool DateIsWithinPeriod(clsDate date) {
		return DateIsWithinPeriod(*this, date);
	}

	static int CountOverlapDays(clsPeriod firstPeriod, clsPeriod secondPeriod) {
		int Period1Length = PeriodLengthInDays(firstPeriod, true);
		int Period2Length = PeriodLengthInDays(secondPeriod, true);
		int OverlapDays = 0;
		if (!IsOverlapPeriods(firstPeriod, secondPeriod))
			return 0;
		if (Period1Length < Period2Length) {
			while (IsFirstDateBeforeSecondDate(firstPeriod.startDate, firstPeriod.endDate)) {
				if (DateIsWithinPeriod(secondPeriod, firstPeriod.startDate))
					OverlapDays++;
				firstPeriod.startDate = IncreaseDateByOneDay(firstPeriod.startDate);
			}
		}
		else {
			while (IsFirstDateBeforeSecondDate(secondPeriod.startDate, secondPeriod.endDate)) {
				if (DateIsWithinPeriod(firstPeriod, secondPeriod.startDate))
					OverlapDays++;
				secondPeriod.startDate = IncreaseDateByOneDay(secondPeriod.startDate);
			}
		}
		return OverlapDays;
	}
	int CountOverlapDays(clsPeriod secondPeriod) {
		return CountOverlapDays(*this, secondPeriod);
	}


};

