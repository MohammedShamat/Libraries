#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;


class clsString
{
private:
	string _value;

	static bool _IsLowerLetter(char readChar) {
		return islower(readChar);
	}

	static char _InvertCharacter(char charFromUser) {
		return _IsLowerLetter(charFromUser) ? toupper(charFromUser) : tolower(charFromUser);

	}

	static bool _IsVowelLetter(char& letter) {
		//letter = tolower(letter);
		return ('a' == letter || 'e' == letter || 'o' == letter || 'i' == letter || 'u' == letter ||
			'A' == letter || 'E' == letter || 'O' == letter || 'I' == letter || 'U' == letter);
	}

	static vector<string> _SplitVe(string fromUser, string delimit) {
		vector <string> textFromUser;
		short position = 0;
		string tempWord = "";
		while ((position = fromUser.find(delimit)) != std::string::npos) {
			tempWord = fromUser.substr(0, position);
			if (tempWord != "") {
				textFromUser.push_back(tempWord);
			}
			fromUser.erase(0, position + delimit.length());
		}
		if (fromUser != "") {
			textFromUser.push_back(fromUser);
		}
		return textFromUser;
	}

	static void _PrintVector(vector <string>& textFromUser) {
		for (string& copy : textFromUser) {
			cout << copy << endl;
		}
	}

public:
	clsString() {
		_value = "";
	}

	clsString(string value) {
		this->_value = value;
	}

	void SetValue(string value) {
		this->_value = value;
	}

	string GetValue() {
		return _value;
	}

	__declspec(property(get = GetValue, put = SetValue))string value;

	//Count Words
	static short CountWords(string text) {
		string delim = " ";
		short counter = 0;
		short pos = 0;
		string tempWord;
		while ((pos = text.find(delim)) != std::string::npos) {
			tempWord = text.substr(0, pos);
			if (tempWord != "") {
				counter++;
			}
			text.erase(0, pos + delim.length());
		}
		if (text != "") {
			counter++;
		}
		return counter;
	}

	short CountWords() {
		return CountWords(_value);
	}

	//Print First Letter in each word in text
	static void PrintFirstLetterInText(string userString) {
		char space = 32;
		bool isFirstLetter = true;
		for (short index = 0; userString.length() > index; index++) {
			if (userString[index] != space && isFirstLetter) {
				cout << userString[index] << endl;
			}
			isFirstLetter = (userString[index] == space) ? true : false;

		}
	}
	void PrintFirstLetterInText() {
		PrintFirstLetterInText(_value);
	}

	//Change first letter in string to upper letter
	static void ChangeFirstLetterToUpper(string userString) {
		char space = 32;
		bool isFirstLetter = true;
		for (short index = 0; userString.length() > index; index++) {
			if (userString[index] != space && isFirstLetter) {
				userString[index] = toupper(userString[index]);
			}

			isFirstLetter = (userString[index] == space) ? true : false;
		}
		cout << userString;

	}
	void ChangeFirstLetterToUpper() {
		ChangeFirstLetterToUpper(_value);
	};

	//Change First Letter In String To Lower Letter
	static void ChangeFirstLetterInStringToLowerLetter(string userString) {
		char space = 32;
		bool isFirstLetter = true;
		for (short index = 0; userString.length() > index; index++) {
			if (userString[index] != space && isFirstLetter) {
				userString[index] = tolower(userString[index]);
			}

			isFirstLetter = (userString[index] == space) ? true : false;
		}
		cout << userString;

	}
	void ChangeFirstLetterInStringToLowerLetter() {
		ChangeFirstLetterInStringToLowerLetter(_value);
	}

	//Change Every Letter In String To Lower
	static void ChangeEveryLetterInStringToLowerLetter(string userString) {
		char space = 32;
		for (short index = 0; userString.length() > index; index++) {
			if (userString[index] != space) {
				userString[index] = tolower(userString[index]);
			}
		}
		cout << userString << endl;

	}
	void ChangeEveryLetterInStringToLowerLetter() {
		ChangeEveryLetterInStringToLowerLetter(_value);
	}

	//Change Every Letter In String To Upper
	static string UpperAllString(string userString) {
		char space = 32;
		for (short index = 0; userString.length() > index; index++) {
			if (userString[index] != space) {
				userString[index] = toupper(userString[index]);
			}
		}
		return userString;

	}
	void UpperAllString() {
		UpperAllString(_value);
	}

	//Inverting all letters case
	static string InvertString(string textFromUser) {
		for (short index = 0; index < textFromUser.length(); index++) {
			textFromUser[index] = _InvertCharacter(textFromUser[index]);
		}
		return textFromUser;
	}
	string InvertString() {
		return InvertString(_value);
	}

	//Count lower letter in text
	static short LowerLettersInString(string textFromUser) {
		short lowerLetters = 0;
		for (short index = 0; index < textFromUser.length(); index++) {
			if (islower(textFromUser[index])) {
				lowerLetters++;
			}
		}
		return lowerLetters;
	}
	short LowerLettersInString() {
		return LowerLettersInString(_value);
	}

	//Count Capital letter in text 
	static short CapitalLettersInString(string textFromUser) {
		short capitalLetters = 0;
		for (short index = 0; index < textFromUser.length(); index++) {
			if (isupper(textFromUser[index])) {
				capitalLetters++;
			}
		}
		return capitalLetters;
	}
	short CapitalLettersInString() {
		return CapitalLettersInString(_value);
	}

	//Length Text
	static short LengthString(string textFromUser) {
		return textFromUser.length();
	}
	short LengthString() {
		return LengthString(_value);
	}

	//Count Capital or Lower or both letter in text 
	enum TypeOfLetter { Lower = 0, Upper = 1, AllType = 2 };
	static short CountLetter(string textFromUser, TypeOfLetter whatWantToCount = TypeOfLetter::AllType) {
		short counter = 0;
		if (whatWantToCount == TypeOfLetter::AllType) {
			return textFromUser.length();
		}
		for (short index = 0; index < textFromUser.length(); index++) {
			if (isupper(textFromUser[index]) && whatWantToCount == TypeOfLetter::Upper) {
				counter++;
			}
			if (islower(textFromUser[index]) && whatWantToCount == TypeOfLetter::Lower) {
				counter++;
			}
		}
		return counter;
	}

	short CountLetter() {
		return CountLetter(_value);
	}

	//Count Of Letter case 

	static short CountOfCharacter(string textFromUser, char valueFromUser) {
		short counter = 0;
		for (short index = 0; index < textFromUser.length(); index++) {
			if (textFromUser[index] == valueFromUser) {
				counter++;
			}
		}
		return counter;
	}
	short CountOfCharacter(char valueFromUser) {
		return CountOfCharacter(_value, valueFromUser);
	}

	//Count all vowels in text

	static short CountVowelLetterInText(string textFromUser) {
		short counter = 0;
		for (short index = 0; index < textFromUser.length(); index++) {
			if (_IsVowelLetter(textFromUser[index])) {
				counter++;
			}
		}
		return counter;
	}
	short CountVowelLetterInText() {
		return CountVowelLetterInText(_value);
	}

	//Print All Vowel Letter In Text

	static void PrintAllVowelLettersInText(string textFromUser) {

		for (short index = 0; index < textFromUser.length(); index++) {
			if (_IsVowelLetter(textFromUser[index])) {
				cout << textFromUser[index] << "\t";
			}
		}
	}

	void PrintAllVowelLettersInText() {
		PrintAllVowelLettersInText(_value);
	}

	//Print Each Word In String
	static void PrintEachWordInString(string fromUser) {
		string delim = " ";
		short pos = 0;
		string tempWord;
		while ((pos = fromUser.find(delim)) != std::string::npos) {
			tempWord = fromUser.substr(0, pos);
			if (tempWord != "") {
				cout << tempWord << endl;
			}
			fromUser.erase(0, pos + delim.length());
		}
		if (fromUser != "") {
			cout << fromUser << endl;
		}
	}
	void PrintEachWordInString() {
		PrintEachWordInString(_value);
	}

	//Count Each Words In String

	static short CountEachWordsInString(string fromUser) {
		string delim = " ";
		short counter = 0;
		short pos = 0;
		string tempWord;
		while ((pos = fromUser.find(delim)) != std::string::npos) {
			tempWord = fromUser.substr(0, pos);
			if (tempWord != "") {
				counter++;
			}
			fromUser.erase(0, pos + delim.length());
		}
		if (fromUser != "") {
			counter++;
		}
		return counter;
	}
	short CountEachWordsInString() {
		return CountEachWordsInString(_value);
	}

	//Split string

	static  vector<string> Split(string text, string delimit) {
		vector <string> vSplit = _SplitVe(text, delimit);
		return vSplit;
	}
	vector<string> Split(string delimit) {
		return Split(_value, delimit);
	}

	//TrimText
	static string TrimLeftText(string fromUser) {
		for (short index = 0; index < fromUser.length(); index++) {
			if (fromUser[index] != ' ') {
				return fromUser.substr(index, fromUser.length() - index);
			}
		}
		return "";
	}
	static string TrimRightText(string fromUser) {
		for (short index = fromUser.length(); index > 0; index--) {
			if (fromUser[index] != ' ') {
				return fromUser.substr(0, index + 1);
			}
		}
		return "";
	}
	static string TrimText(string fromUser) {

		return TrimLeftText(TrimRightText(fromUser));
	}
	string TrimLeftText() {
		return TrimLeftText(_value);
	}
	string TrimRightText() {
		return TrimRightText(_value);
	}
	string TrimText() {
		return TrimLeftText(TrimRightText(_value));
	}

	//Join String
	static string JoinString(vector <string> vOfString, string delimit) {
		string joinText = "";
		for (string& tempText : vOfString) {
			joinText = joinText + tempText + delimit;
		}
		return joinText.substr(0, joinText.length() - delimit.length());
	}

	//Join String overloading with array
	static string JoinString(string arrOfString[], short arrLength, string delimit) {
		string joinText = "";
		for (short index = 0; index < arrLength; index++) {
			if (index != 0 && index != arrLength) {
				joinText.append(delimit);
			}
			joinText.append(arrOfString[index]);
		}
		return joinText;
	}
	//Reverse String

	static string ReverseWordInText(string fromUser) {
		vector<string> VectorString = _SplitVe(fromUser, " ");
		string tempText = "";
		vector<string>::iterator StringIter = VectorString.end();
		while (StringIter != VectorString.begin()) {
			--StringIter;
			tempText += *StringIter + " ";

		}
		tempText = tempText.substr(0, tempText.length() - 1);
		return tempText;
	}

	string ReverseWordInText() {
		return ReverseWordInText(_value);
	}

	//Replace Word In Text without built fun

	static string ReplaceWordInText(string fromUser, string word, string replaceWord, bool matchCase = true) {
		short pos = 0;
		if (matchCase) {
			while (((pos = fromUser.find(word)) != std::string::npos)) {
				fromUser.erase(pos, word.length());
				fromUser.insert(pos, replaceWord);
			};
		}
		else {
			word[0] = toupper(word[0]);
			while (((pos = fromUser.find(word)) != std::string::npos)) {
				fromUser.erase(pos, word.length());
				fromUser.insert(pos, replaceWord);
			};
		}


		return fromUser;
	}
	string ReplaceWordInText(string word, string replaceWord, bool matchCase = true) {
		return ReplaceWordInText(_value, word, replaceWord, matchCase);
	};

	//Punctuations Text
	static string RemovePunctuationsText(string fromUser, char delimiter) {
		for (short index = 0; index < fromUser.length(); index++) {
			if (fromUser[index] == delimiter) {
				fromUser[index] = 00;
			}
		}
		return fromUser;
	}

	static string RemoveEveryPunctuationsInText(string fromUser) {
		string tempText = "";
		for (short index = 0; index < fromUser.length(); index++) {
			if (!ispunct(fromUser[index])) {
				tempText += fromUser[index];
			}
		}
		return tempText;
	}

	string RemovePunctuationsText(char delimiter) {
		return RemovePunctuationsText(_value, delimiter);
	}

	string RemoveEveryPunctuationsInText() {
		return RemoveEveryPunctuationsInText(_value);
	}


};

