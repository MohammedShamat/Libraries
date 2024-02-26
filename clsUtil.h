#pragma once
#include <iostream>
#include"clsDate.h"
using namespace std;


//All members in class are static

class clsUtil
{
private:
	static const short _Encryptionkey = 2;
	enum _PerfectOrNot {
		perfect = 1,
		NotPerfect = 2,
	};

	enum _TypeNumber {
		primeNumber = 1,
		notPrimeNumber = 2,
	};

	enum _PalindromeNumber {
		Palindrome = 1,
		NotPalindrome = 2,
	};



	static _PerfectOrNot _CheckTypeNumberPerfect(int number) {
		int sum = 0;
		for (int counter = 1; counter < number; counter++) {

			if (number % counter == 0) {
				sum += counter;
			}

		}
		if (number == sum) {
			return _PerfectOrNot::perfect;
		}
		else {
			return _PerfectOrNot::NotPerfect;
		}
	}

	static _TypeNumber _CheckTypeNumberPrime(int number) {

		int halfOfRound = round(number / 2);
		for (short counter = 2; counter <= halfOfRound; counter++) {
			if (number % counter == 0) {
				return _TypeNumber::notPrimeNumber;
			}

		}
		return _TypeNumber::primeNumber;

	}

	static _PalindromeNumber _IsPalindromeNumber(int number) {

		if (ReversedNumber(number) == number)
			return _PalindromeNumber::Palindrome;

		else
			return _PalindromeNumber::NotPalindrome;
	}

	static short GetRandomOperationType() {
		short op = RandomNumber(1, 4);
		return op;
	}

public:

	static void Srand() {
		srand((unsigned)time(NULL));
	}

	enum CharType {
		SmallLetter = 1,
		CapitalLetter = 2,
		SpecialCharacter = 3,
		DigitNumber = 4,
		MixChars = 5,
	};

	static int RandomNumber(short from, short to) {
		int number = rand() % (to - from + 1) + from;
		return number;

	}

	static char GetRandomCharacter(CharType tyepOfChar) {
		switch (tyepOfChar)
		{
		case CharType::SmallLetter:
			return char(RandomNumber(97, 122));

		case CharType::CapitalLetter:
			return char(RandomNumber(65, 90));

		case CharType::DigitNumber:
			return char(RandomNumber(48, 57));

		case CharType::SpecialCharacter:
			return char(RandomNumber(33, 47));

		case CharType::MixChars:
			return GetRandomCharacter((CharType)GetRandomOperationType());
		}
	}

	static bool IsPerfectNumber(int number) {

		switch (_CheckTypeNumberPerfect(number))
		{
		case _PerfectOrNot::perfect:
			return true;
			break;
		case _PerfectOrNot::NotPerfect:
			return false;
			break;

		}
	}

	static bool IsPrimeNumber(int number) {

		switch (_CheckTypeNumberPrime(number))
		{
		case _TypeNumber::notPrimeNumber:
			return false;
			break;
		case _TypeNumber::primeNumber:
			return true;
			break;
		}

	}

	static void PrintAllPrimeNumbersFrom1ToN(int number) {
		for (int loop = 1; loop <= number; loop++) {

			if (IsPrimeNumber(loop)) {
				cout << "The number is prime : " << loop << endl;

			};
		}
	}

	static void PrintAllPerfectNumbersFrom1ToN(int number) {
		for (int loop = 1; loop <= number; loop++) {

			if (IsPerfectNumber(loop)) {
				cout << "The Number is Perfect : " << loop << endl;

			};
		}
	}

	static void PrintDigitsReverse(int number) {
		int reverse = 0;
		while (number > 0) {
			reverse = number % 10;
			cout << reverse << endl;
			number = number / 10;
		}
	}

	static int ReversedNumber(int number) {

		int numberTemp = 0;

		int reverseNumber = 0;

		while (number > 0) {
			numberTemp = number % 10;

			number = number / 10;
			reverseNumber = reverseNumber * 10 + numberTemp;
		}

		return reverseNumber;
	}

	static short FindHowmanyANumberFrequency(int number, short frequency) {

		int remainder = 0;
		short counter = 0;
		while (number > 0) {
			remainder = number % 10;

			number = number / 10;
			if (remainder == frequency) {
				counter++;
			}

		}

		return counter;
	}

	static void PrintAllDigitFrequncy(int number) {

		for (short count = 0; count <= 9; count++) {
			if (FindHowmanyANumberFrequency(number, count) != 0) {
				cout << "digits " << count << " Frequncy is "
					<< FindHowmanyANumberFrequency(number, count)
					<< " times" << endl;
			}
		}
	}

	static bool IsPalindromeNumber(int number) {
		return (_IsPalindromeNumber(number) == _PalindromeNumber::Palindrome);
	}

	static string EncryptionText(string textFromUser) {

		for (short indexOfString = 0; indexOfString <= textFromUser.length(); indexOfString++) {

			textFromUser[indexOfString] = char((int)textFromUser[indexOfString] + _Encryptionkey);

		}
		return textFromUser;
	}

	static string DecryptionText(string text) {

		for (short indexOfString = 0; indexOfString <= text.length(); indexOfString++) {

			text[indexOfString] = char((int)text[indexOfString] - _Encryptionkey);

		}
		return text;

	}

	static string GenerateWord(CharType typeOfChar, short length) {

		string word = "";
		for (short counter = 1; counter <= length; counter++) {
			word = word + GetRandomCharacter(typeOfChar);
		}
		return word;
	}


	static string GenerateKey(CharType typeOfChar) {
		string key = "";
		string underScore = "-";
		key = GenerateWord(typeOfChar, 4) + underScore;
		key = key + GenerateWord(typeOfChar, 4) + underScore;
		key = key + GenerateWord(typeOfChar, 4) + underScore;
		key = key + GenerateWord(typeOfChar, 4);
		return key;
	}

	static void GenerateKeys(CharType typeOfChar,int numberOfKeys) {
		for (int counter = 1; counter <= numberOfKeys; counter++) {
			cout << "Key [" << counter << "] : " << GenerateKey(typeOfChar) << endl;
		}
	}

	static void Sawp(int& first, int& second) {
		int temp = first;
		first = second;
		second = temp;
	}

	static void Sawp(string& first, string& second) {
		string temp = first;
		first = second;
		second = temp;
	}

	static void Sawp(double& first, double& second) {
		double temp = first;
		first = second;
		second = temp;
	}
	
	static void Sawp(clsDate& first, clsDate& second) {
		clsDate::SwapDate(first, second);
	}

	static void ShuffleArray(int arr[], int length) {

		for (int index = 0; index < length; index++) {

			Sawp(arr[RandomNumber(1, length) - 1], arr[RandomNumber(1, length) - 1]);
		}
		cout << endl;

	}

	static void PrintTheIntArray(int arr[], int length) {

		for (int index = 0; index < length; index++) {
			cout << arr[index] << " ";
		}

	}

	static string Tabs(short NumberOfTabs)
	{
		string tab = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			tab = tab + "\t";
			cout << tab;
		}
		return tab;

	}

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}


};

