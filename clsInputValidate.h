#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
using namespace std;
//All members in class are static

class clsInputValidate
{

public:
	//template function: 
	//template <typename T> T MaxNumber(T number, T number2){};
	// *********
	// 
	//MaxNumber <int>(1,5){}
	// template <typename T> static bool IsNumberBetween(T Number, T From, T To)
	// IsNumberBetween(1,3);
	// *********
	
	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static  bool IsNumberBetween(int Number, int From, int To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsFirstDateAfterSecondDate(Date, From) || clsDate::IsFirstDateEqualsSecondDate(Date, From))
			&&
			(clsDate::IsFirstDateBeforeSecondDate(Date, To) || clsDate::IsFirstDateEqualsSecondDate(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsFirstDateAfterSecondDate(Date, To) || clsDate::IsFirstDateEqualsSecondDate(Date, To))
			&&
			(clsDate::IsFirstDateBeforeSecondDate(Date, From) || clsDate::IsFirstDateEqualsSecondDate(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string stringText = "";
		getline(cin >> ws, stringText);
		return stringText;
	}
};

