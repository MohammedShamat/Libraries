#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include<ctime>
#include<vector>
#include"clsString.h"

using namespace std;
class clsDate : private clsString
{
private:
	int _year;
	short _month;
	short _days;



	clsDate GetDateFromDay(short days, int year) {
		clsDate date;
		short RemainingDays = days;
		short monthDays = 0;
		date._year = year;
		date._month = 1;
		while (true) {
			monthDays = DaysInMonth(date);
			if (RemainingDays > monthDays) {
				RemainingDays -= monthDays;
				date._month++;
			}
			else {
				date._days = RemainingDays;
				break;
			}
		}
		return date;
	}

	static short DayNumberInWeek(short year, short month, short day) {
		float a = (14 - month) / 12;
		short y = year - a;
		short m = month + (12 * a) - 2;
		short dayName = ((day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12))) % 7;
		return dayName;
	}

	static string DayNameInWeek(short dayNumber) {
		string namesOfDays[7] = { "Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return namesOfDays[dayNumber];
	}

	static string NameOfMonth(short numMonth) {
		string arrMonthNames[12] = { "Jan", "Feb", "Mar", "Apr", "May","Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arrMonthNames[numMonth - 1];
	}





public:

	clsDate() {

		time_t timeNow = time(0);
		tm* now = localtime(&timeNow);
		_year = now->tm_year + 1900;
		_month = now->tm_mon + 1;
		_days = now->tm_mday;

	}

	clsDate(string sDate) {
		clsString date(sDate);
		vector <string> vSplit = date.Split("/");
		_days = stoi(vSplit[0]);
		_month = stoi(vSplit[1]);
		_year = stoi(vSplit[2]);
	}

	clsDate(short days, short month, int year) {
		_year = year;
		_month = month;
		_days = days;
	}

	clsDate(short days, int year) {
		clsDate date = GetDateFromDay(days, year);
		_year = date._year;
		_month = date._month;
		_days = date._days;
	}

	static string GetSystemDateTimeString()
	{

		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	static enum enDateCompare {
		Before = -1, Equal = 0, After = 1
	};

	void PrintDate() {
		cout << _days << "/" << _month << "/" << _year << endl;
	}

	static void SwapDate(clsDate& firstDate, clsDate& secondDate) {
		clsDate tempDate = firstDate;
		firstDate = secondDate;
		secondDate = tempDate;
	}
	static bool IsLeapYear(clsDate date) {
		return ((date._year % 4 == 0) && (date._year % 100 != 0) || (date._year % 400 == 0));
	}

	bool IsLeapYear() {
		return IsLeapYear(*this);
	}


	static short DaysInMonth(clsDate date) {

		short arr31Dyas[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return  (date._month == 2) ? (IsLeapYear(date) ? 29 : 28) : arr31Dyas[date._month - 1];

	}
	short DaysInMonth() {
		return DaysInMonth(*this);
	}

	static bool IsLastDayInMonth(clsDate date) {
		return DaysInMonth(date) == date._days;
	}
	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsDate date) {
		return date._month == 12;
	}
	bool IsLastMonthInYear() {
		return IsLastMonthInYear(*this);
	}

	static clsDate IncreaseDateByOneDay(clsDate date) {
		clsDate increaseDate = date;
		if (IsLastDayInMonth(date)) {
			if (IsLastMonthInYear(date)) {
				increaseDate._year++;
				increaseDate._month = 1;
				increaseDate._days = 1;
			}
			else {
				increaseDate._month++;
				increaseDate._days = 1;
			}

		}
		else {
			increaseDate._days++;
		}
		return increaseDate;

	}

	clsDate IncreaseDateByOneDay() {
		return IncreaseDateByOneDay(*this);
	}

	static bool IsFirstDateBeforeSecondDate(clsDate firstDate, clsDate secondDate) {
		return (firstDate._year < secondDate._year) ? true : ((firstDate._year ==
			secondDate._year) ? (firstDate._month < secondDate._month ? true : (firstDate._month ==
				secondDate._month ? firstDate._days < secondDate._days : false)) : false);
	}

	bool  IsFirstDateBeforeSecondDate(clsDate date2) {
		return IsFirstDateBeforeSecondDate(*this, date2);
	}

	static int CalculateDifferenceBetweenTwoDates(clsDate firstDate, clsDate secondDate, bool includeEndDay = false) {
		int difference = 0;
		short sawpValue = 1;
		if (!IsFirstDateBeforeSecondDate(firstDate, secondDate)) {
			SwapDate(firstDate, secondDate);
			sawpValue = -1;
		}
		while (IsFirstDateBeforeSecondDate(firstDate, secondDate)) {
			difference++;
			firstDate = IncreaseDateByOneDay(firstDate);
		}

		return includeEndDay ? ++difference * sawpValue : difference * sawpValue;


	}


	int CalculateDifferenceBetweenTwoDates(clsDate secondDate, bool includeEndDay = false) {
		return CalculateDifferenceBetweenTwoDates(*this, secondDate, includeEndDay);
	}


	static int CalculateMyAgeInDays(clsDate date) {
		clsDate dateFromSys;
		return CalculateDifferenceBetweenTwoDates(date, dateFromSys, true);
	}
	int CalculateMyAgeInDays() {
		return CalculateMyAgeInDays(*this);
	}

	static void MonthCalender(clsDate date) {

		short dayInMonth = DaysInMonth(date);//numberofdays
		short dayNumber = DayNumberInWeek(date._year, date._month, 1);//curr
		cout << "  ________________" << NameOfMonth(date._month) << "______________\n\n";
		cout << "  ";
		for (short index = 0; index < 7; index++) {
			cout << DayNameInWeek(index) << "  ";
		}
		cout << endl;
		int i;
		for (i = 0; i < dayNumber; i++)
			printf("     ");
		for (int j = 1; j <= dayInMonth; j++) {
			printf("%5d", j);
			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}

		cout << "\n  _________________________________\n";
	}

	void MonthCalender() {
		MonthCalender(*this);
	}

	static void YearCalender(clsDate date) {

		for (short counter = 1; counter <= 12; counter++) {
			MonthCalender(date);
			date._month += 1;
		}

	}

	void YearCalender() {
		YearCalender(*this);
	}


	static bool IsValidDate(clsDate date) {

		if ((((date._month < 1 || date._month>12)
			|| (date._days < 1 || date._days>31)) ||
			(DaysInMonth(date) < date._days))
			) {
			return false;
		}

		else {
			return true;
		}
	}
	bool IsValid() {

		return IsValidDate(*this);
	}

	static short HoursInMonth(clsDate date) {
		return DaysInMonth(date) * 24;
	}
	short HoursInMonth() {
		return  HoursInMonth(*this);
	}

	static int MinutesInMonth(clsDate date) {
		return HoursInMonth(date) * 60;
	}
	int MinutesInMonth() {
		return MinutesInMonth(*this);
	}

	static int SecondsInMonth(clsDate date) {
		return MinutesInMonth(date) * 60;
	}
	int SecondsInMonth() {
		return SecondsInMonth(*this);
	}


	static short TotalDaysFromBeginningYear(clsDate date) {
		short totalDays = 0;
		short month = date._month;
		date._month = 1;
		for (short counter = 1; counter <= month - 1; counter++) {

			totalDays += DaysInMonth(date);
			date._month++;

		}

		return (totalDays + date._days);

	}
	short TotalDaysFromBeginningYear() {
		return TotalDaysFromBeginningYear(*this);
	}

	static clsDate DateAfterAddedDays(clsDate date, short addsDays) {
		clsDate newDate = date;
		short totalDays = TotalDaysFromBeginningYear(newDate) + addsDays;
		short daysInMonth = 0;
		newDate._month = 1;
		while (true) {
			daysInMonth = DaysInMonth(newDate);
			if (totalDays > daysInMonth) {
				totalDays -= daysInMonth;
				newDate._month++;
				if (newDate._month > 12) {
					newDate._month = 1;
					newDate._year++;
				}

			}
			else {
				newDate._days = totalDays;
				break;
			}
		}
		return newDate;
	}
	clsDate DateAfterAddedDays(short addsDays) {
		return DateAfterAddedDays(*this, addsDays);
	}

	static bool  IsFirstDateEqualsSecondDate(clsDate firstDate, clsDate secondDate) {
		return (firstDate._year == secondDate._year) ? ((firstDate._month == secondDate._month) ?
			((firstDate._days == secondDate._days) ? true : false) : false) : false;
	}
	bool  IsFirstDateEqualsSecondDate(clsDate secondDate) {
		return IsFirstDateEqualsSecondDate(*this, secondDate);
	}

	static bool IsFirstDateAfterSecondDate(clsDate firstDate, clsDate secondDate) {
		return (!(IsFirstDateBeforeSecondDate(firstDate, secondDate)) && !(IsFirstDateEqualsSecondDate(firstDate, secondDate)));
	}
	bool IsFirstDateAfterSecondDate(clsDate secondDate) {
		return IsFirstDateAfterSecondDate(*this, secondDate);
	}

	static enDateCompare CompareDate(clsDate firstDate, clsDate secondDate) {
		if (IsFirstDateBeforeSecondDate(firstDate, secondDate)) {
			return enDateCompare::Before;
		}
		if (IsFirstDateEqualsSecondDate(firstDate, secondDate)) {
			return enDateCompare::Equal;
		}
		return enDateCompare::After;
	}
	enDateCompare CompareDate(clsDate secondDate) {
		return CompareDate(*this, secondDate);
	}

	//Increase

	static clsDate IncreaseDateByXDays(clsDate date, short addsDays) {
		clsDate newDate = date;
		short totalDays = TotalDaysFromBeginningYear(date) + addsDays;
		short daysInMonth = 0;
		newDate._month = 1;
		while (true) {
			daysInMonth = DaysInMonth(date);
			if (totalDays > daysInMonth) {
				totalDays -= daysInMonth;
				newDate._month++;
				if (newDate._month > 12) {
					newDate._month = 1;
					newDate._year++;
				}

			}
			else {
				newDate._days = totalDays;
				break;
			}
		}
		return newDate;
	}
	clsDate IncreaseDateByXDays(short addsDays) {
		return IncreaseDateByXDays(*this, addsDays);
	}

	static clsDate IncreaseDateOneWeek(clsDate date) {// or We can use that function IncreaseDateByXDays( date, 7) 
		clsDate newDate = date;
		short totalDays = TotalDaysFromBeginningYear(date) + 7;
		short daysInMonth = 0;
		newDate._month = 1;
		while (true) {
			daysInMonth = DaysInMonth(newDate);
			if (totalDays > daysInMonth) {
				totalDays -= daysInMonth;
				newDate._month++;
				if (newDate._month > 12) {
					newDate._month = 1;
					newDate._year++;
				}

			}
			else {
				newDate._days = totalDays;
				break;
			}
		}
		return newDate;
	}
	clsDate IncreaseDateOneWeek() {
		return IncreaseDateOneWeek(*this);
	}

	static clsDate IncreaseDateXWeeks(clsDate date, short Weeks) {
		clsDate newDate = date;
		for (short counter = 0; counter < Weeks; counter++) {
			newDate = IncreaseDateOneWeek(newDate);
		}

		return newDate;
	}

	clsDate IncreaseDateXWeeks(short Weeks) {
		return IncreaseDateXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateOneMonth(clsDate date) {
		clsDate newDate = date;
		if (newDate._month == 12) {
			newDate._month = 1;
			newDate._year++;
		}
		else {
			newDate._month++;
		}
		short numberOfDaysInMonth = DaysInMonth(date);
		if (date._days > numberOfDaysInMonth) {
			date._days = numberOfDaysInMonth;
		}
		return newDate;
	}

	clsDate IncreaseDateOneMonth() {
		return IncreaseDateOneMonth(*this);
	}


	static clsDate IncreaseDateXMonths(clsDate date, short months) {
		clsDate newDate = date;
		for (short counter = 0; counter < months; counter++) {
			newDate = IncreaseDateOneMonth(newDate);
		}

		return newDate;
	}

	clsDate IncreaseDateXMonths(short months) {

		return IncreaseDateXMonths(*this, months);
	}

	static clsDate IncreaseDateOneYear(clsDate date) {
		clsDate newDate = date;
		newDate._year++;
		return newDate;
	}
	clsDate IncreaseDateOneYear() {
		return IncreaseDateOneYear(*this);
	}

	static clsDate IncreaseDateXYears(clsDate date, short Years) {
		clsDate newDate = date;
		for (short counter = 0; counter < Years; counter++) {//or faster newDate.year+=Years;
			newDate = IncreaseDateOneYear(newDate);
		}

		return newDate;
	}
	clsDate IncreaseDateXYears(short Years) {
		return IncreaseDateXYears(*this, Years);
	}

	static clsDate IncreaseDateOneDecade(clsDate date) {
		clsDate newDate = date;
		newDate._year += 10;
		return newDate;
	}

	clsDate IncreaseDateOneDecade() {
		return IncreaseDateOneDecade(*this);
	}

	static clsDate IncreaseDateXDecade(clsDate date, short decades) {
		clsDate newDate = date;
		for (short counter = 0; counter < decades; counter++) {//or faster newDate.year+=Years;
			newDate = IncreaseDateOneDecade(newDate);
		}

		return newDate;
	}
	clsDate IncreaseDateXDecade(short decades) {
		return IncreaseDateXDecade(*this, decades);
	}

	static clsDate IncreaseDateOneCentury(clsDate date) {
		clsDate newDate = date;
		newDate._year += 100;
		return newDate;
	}
	clsDate IncreaseDateOneCentury() {
		return IncreaseDateOneCentury(*this);
	}

	static clsDate IncreaseDateOneMillennium(clsDate date) {
		clsDate newDate = date;
		newDate._year += 1000;
		return newDate;
	}
	clsDate IncreaseDateOneMillennium() {
		return  IncreaseDateOneMillennium(*this);
	}

	//Subtracting Date

	static clsDate SubtractingDateByOneDay(clsDate date) {
		clsDate dateAfterDay = date;
		if (date._month == 1 && date._days == 1) {
			dateAfterDay._year--;
			dateAfterDay._month = 12;
			dateAfterDay._days = DaysInMonth(date);
			return dateAfterDay;
		}
		else if (date._days == 1) {
			dateAfterDay._month--;
			dateAfterDay._days = DaysInMonth(date);
			return dateAfterDay;
		}
		else {
			dateAfterDay._days--;
			return dateAfterDay;
		}
	}
	clsDate SubtractingDateByOneDay() {
		return SubtractingDateByOneDay(*this);
	}

	static clsDate SubtractingDateByXDays(clsDate date, short subDays) {
		clsDate newDate = date;
		for (short counter = 0; counter < subDays; counter++) {
			newDate = SubtractingDateByOneDay(newDate);
		}
		return newDate;
	}
	clsDate SubtractingDateByXDays(short subDays) {
		return SubtractingDateByXDays(*this, subDays);
	}

	static clsDate SubtractingDateOneWeek(clsDate date) {
		clsDate newDate = date;
		for (short counter = 0; counter < 7; counter++) {
			newDate = SubtractingDateByOneDay(newDate);
		}

		return newDate;
	}
	clsDate SubtractingDateOneWeek() {
		return SubtractingDateOneWeek(*this);
	}

	static clsDate SubtractingDateXWeeks(clsDate date, short Weeks) {
		clsDate newDate = date;
		for (short counter = 0; counter < Weeks; counter++) {
			newDate = SubtractingDateOneWeek(newDate);
		}

		return newDate;
	}
	clsDate SubtractingDateXWeeks(short Weeks) {
		return SubtractingDateXWeeks(*this, Weeks);
	}

	static clsDate SubtractingDateOneMonth(clsDate date) {
		clsDate newDate = date;
		if (date._month == 1) {
			newDate._month = 12;
			newDate._year--;
		}
		else {
			newDate._month--;
		}
		short numberOfDaysInMonth = DaysInMonth(newDate);
		if (newDate._days > numberOfDaysInMonth) {
			newDate._days = numberOfDaysInMonth;
		}
		return newDate;
	}
	clsDate SubtractingDateOneMonth() {
		return SubtractingDateOneMonth(*this);
	}

	static clsDate SubtractingDateXMonths(clsDate date, short months) {
		clsDate newDate = date;
		for (short counter = 0; counter < months; counter++) {
			newDate = SubtractingDateOneMonth(newDate);
		}

		return newDate;
	}
	clsDate SubtractingDateXMonths(short months) {
		return SubtractingDateXMonths(*this, months);
	}

	static clsDate SubtractingDateOneYear(clsDate date) {
		clsDate newDate = date;
		newDate._year--;
		return newDate;
	}
	clsDate SubtractingDateOneYear() {
		return SubtractingDateOneYear(*this);
	}

	static clsDate SubtractingDateXYears(clsDate date, short Years) {
		clsDate newDate = date;
		for (short counter = 0; counter < Years; counter++) {//or faster newDate.year-=Years;
			newDate = SubtractingDateOneYear(newDate);
		}

		return newDate;
	}
	clsDate SubtractingDateXYears(short years) {
		return SubtractingDateXYears(*this, years);
	}

	static clsDate SubtractingDateOneDecade(clsDate date) {
		clsDate newDate = date;
		newDate._year -= 10;
		return newDate;
	}
	clsDate SubtractingDateOneDecade() {
		return SubtractingDateOneDecade(*this);
	}

	static clsDate SubtractingDateXDecade(clsDate date, short Years) {
		clsDate newDate = date;
		for (short counter = 0; counter < Years; counter++) {//or faster newDate.year-=Years;
			newDate = SubtractingDateOneDecade(newDate);
		}

		return newDate;
	}
	clsDate SubtractingDateXDecade(short years) {
		return SubtractingDateXDecade(*this, years);
	}

	static clsDate SubtractingDateOneCentury(clsDate date) {
		clsDate newDate = date;
		newDate._year -= 100;
		return newDate;
	}
	clsDate SubtractingDateOneCentury() {
		return  SubtractingDateOneCentury(*this);
	}

	static clsDate SubtractingDateOneMillennium(clsDate date) {
		clsDate newDate = date;
		newDate._year -= 1000;
		return newDate;
	}
	clsDate SubtractingDateOneMillennium() {
		return   SubtractingDateOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate date) {
		return(DayNumberInWeek(date._year, date._month, date._days) == 6);
	}
	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate date) {
		return(DayNumberInWeek(date._year, date._month, date._days) == 6 || DayNumberInWeek(date._year, date._month, date._days) == 5);
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate date) {
		return !(IsWeekEnd(date));
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate date) {//date._year, date._month, date._days
		return (6 - DayNumberInWeek(date._year, date._month, date._days));
	}
	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate date) {
		return  (DaysInMonth(date) - date._days);
	}
	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate date) {
		return  ((IsLeapYear(date) ? 366 : 365) - TotalDaysFromBeginningYear(date));
	}
	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	//format
	//String To Date 
	/*static clsDate StringToDate(string stringDate) {
		clsDate date;
		vector <string> textFromUser = Split(stringDate, "/");
		date._days = stoi(textFromUser[0]);
		date._month = stoi(textFromUser[1]);
		date._year = stoi(textFromUser[2]);
		return date;
	}*/

	static string DateToString(clsDate date) {
		string stDate = "";
		stDate += to_string(date._days) + "/";
		stDate += to_string(date._month) + "/";
		stDate += to_string(date._year);
		return stDate;
	}
	string DateToString() {
		return DateToString(*this);
	}


	static string FormatDate(clsDate date, string formatType = "dd/mm/yyyy") {
		string dateToStrWithFormat = "";
		dateToStrWithFormat = ReplaceWordInText(formatType, "dd", to_string(date._days));
		dateToStrWithFormat = ReplaceWordInText(dateToStrWithFormat, "mm", to_string(date._month));
		dateToStrWithFormat = ReplaceWordInText(dateToStrWithFormat, "yyyy", to_string(date._year));
		return dateToStrWithFormat;
	}
	string FormatDate(string formatType = "dd/mm/yyyy") {
		/*can use these formats...
		cout << "\n" << FormatDate(date, "yyyy/dd/mm") << endl;
		cout << "\n" << FormatDate(date, "mm/dd/yyyy") << endl;
		cout << "\n" << FormatDate(date, "mm-dd-yyyy") << endl;
		cout << "\n" << FormatDate(date, "dd-mm-yyyy") << endl;
		cout << "\n" << FormatDate(date, "Day:dd, Month:mm, Year:yyyy") << endl;*/

		return FormatDate(*this, formatType);
	}

};

