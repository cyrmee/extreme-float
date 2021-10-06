#include <iostream>
#include <string>
#include "List.cpp"
using namespace std;

int maxDecDigits = 0;
int posDecPt = 0;
int carry = 0;

int countDigits (string num);
int returnDecimalIndex (string num);
int compare (string first, string second);

bool isNumber (string num);

void fillZerosToIntegeralPart (string &num, string &b);
void fillZerosToDecimalPart (string &num, string &b);
void trim (string &num);
void menu ();

string convertToFloat (string num);
string decimalPart (string num);
string integeralPart (string num);
string removeSign (string num);
string add (string first, string second, int carry);
string addDecimalPart (string a, string b);
string addIntgeralPart (string a, string b, int carry);

bool isNegative (string num) {
	for (size_t i = 0; i < num.size (); i++) {
		if (num[i] == '-')
			return true;
	}
	return false;
}

bool isFloat (string num) {
	int temp = 0;
outer: for (size_t i = 0; i < num.size (); i++) {
	if (num[i] == '.') {
		for (size_t j = i + 1; j < num.size (); j++) {
			temp++;
		}
		if (temp > maxDecDigits)
			maxDecDigits = temp;
		return true;
	}
}
	   return false;
}

string convertToFloat (string num) {
	if (isFloat (num)) {
		return num;
	}
	else {
		num += '.';
		for (size_t i = 0; i < maxDecDigits; i++) {
			num += '0';
		}
		return num;
	}
}

int returnDecimalIndex (string num) {
	for (size_t i = 0; i < num.size (); i++) {
		if (num[i] == '.') {
			return i;
		}
	}
}

bool isNumber (string num) {
	bool isNumber = false;
	int cntNegSigns = 0, cntDecPts = 0;
	for (size_t i = 0; i < num.size (); i++) {
		if (num[i] >= '0' && num[i] <= '9' || num[i] == '-' || num[i] == '.') {
			if (num[i] == '.') cntDecPts++;
			else if (num[i] == '-') cntNegSigns++;
			isNumber = true;
		}
		else return false;
	}
	if (cntDecPts > 1 || cntNegSigns > 1) isNumber = false;
	return isNumber;
}

void fillZerosToDecimalPart (string &num, string &b) {
	if (num.size () > b.size ()) {
		maxDecDigits = num.size ();
		for (size_t i = b.size (); i < num.size (); i++) {
			b += "0";
		}
	}
	else if (b.size() > num.size()) {
		maxDecDigits = b.size();
		for (size_t i = num.size(); i < b.size(); i++) {
			num += "0";
		}
	}
}

void fillZerosToIntegeralPart (string &num, string &b) {
	if (num.size () > b.size ()) {
		List<char> temp (b);
		//temp.display ();
		for (size_t i = b.size (); i < num.size (); i++) {
			temp.insertFirst ('0');
		}
		b = "";
		for (size_t i = 0; i < num.size (); i++) {
			b += temp.removeFirst ();
		}
	}
	else if (b.size () > num.size ()) {
		List<char> temp (num);
		//temp.display ();
		for (size_t i = num.size (); i < b.size (); i++) {
			temp.insertFirst ('0');
		}
		num = "";
		for (size_t i = 0; i < b.size (); i++) {
			num += temp.removeFirst ();
		}
	}
}

string decimalPart (string num) {
	string decPart = "";
	int posOfDec;
	if (isFloat(num)) {
		posOfDec = returnDecimalIndex(num);
		for (size_t i = posOfDec; i < num.size (); i++) {
			if (num[i] != '.')
				decPart += num[i];
		}
	}
	return decPart;
}

string integeralPart (string num) {
	string intPart = "";
	int posOfDec;
	if (isFloat(num)) {
		posOfDec = returnDecimalIndex(num);
		for (size_t i = 0; i < posOfDec; i++) {
			intPart += num[i];
		}
	}
	if (intPart == "") intPart = "0";
	return intPart;
}

string removeSign (string num) {
	string temp = "";
	for (size_t i = 0; i < num.size (); i++) {
		if (num[i] != '-')
			temp += num[i];
	}
	return temp;
}

int countDigits (string num) {
	int count = 0;
	for (size_t i = 0; i < num.size() ; i++) {
		if (num[i] >= '1' && num[i] <= '9')
			count++;
	}
	return count;
}

void trim (string &num) {
	List<char> temp(num);
	temp.trim ();
	num = temp.toString ();
}

int compare (string first, string second) {
	int temp = 0;
	if (!isNegative (first) && !isNegative(second)) {
		for (size_t i = 0; i < first.size (); i++) {
			if (first[i] != '.' && second[i] != '.') {
				if (int (first[i] - 48) > int (second[i] - 48)) temp = 1;
				else if (int (first[i] - 48) < int (second[i] - 48)) temp = -1;
				break;
			}
		}
	}
	else if (isNegative (first) && isNegative (second)) {
		for (size_t i = 0; i < first.size (); i++) {
			if (first[i] != '.' && second[i] != '.' && first[i] != '-' && second[i] != '-') {
				if (int (first[i] - 48) < int (second[i] - 48)) temp = 1;
				else if (int (first[i] - 48) > int (second[i] - 48)) temp = -1;
				break;
			}
		}
	}
	else if (isNegative (first) && !isNegative (second)) temp = -1;
	else temp = 1;
	return temp;
}

string add (string first, string second, int carry = 0) {
	List<char> result;

	int temp = 0;
	string tempSum = "";
	for (int i = first.size () - 1; i >= 0; i--) {
		// add to the first of result result
		temp = int(first[i] - 48) + int(second[i] - 48) + carry;
		tempSum = to_string (temp);
		if (tempSum.size () >= 2) {
			carry = int(tempSum[0] - 48);
			result.insertFirst (tempSum[1]);
		}
		else {
			carry = 0;
			result.insertFirst (tempSum[0]);
		}
		if (carry == 1 && i == 0) {
			result.insertFirst (to_string(carry)[0]);
		}
	}
	return result.toString();
}

string addIntgeralPart (string a, string b, int carry = 0) {
	List<char> temp(add (a, b, carry));
	return temp.toString ();
}

string addDecimalPart (string a, string b) {
	List<char> temp (add (a, b));
	return temp.toString ();
}

//string compare (string first, string second) {
//	string temp = "";
//	for (int i = 0; i < first.size (); i++) {
//		if (int (first[i] - 48) > int (second[i] - 48)) {
//			selectedString = 'first';
//			temp = first;
//			break;
//		}
//		else if (int.Parse (first[i].ToString ()) < int.Parse (second[i].ToString ())) {
//			selectedString = "second";
//			temp = second;
//			break;
//		}
//		else {
//			if (i == first.Length)
//				temp = string.Empty;
//		}
//	}
//	return temp;
//}

// Operation Validator


void menu () {
	string firstNum, secondNum;
	char choice;
	cout << "Choose from the following operations: " << endl
		<< "1. Addition" << endl
		<< "2. Subtraction" << endl
		<< "3. Multiplication" << endl
		<< "4. Division" << endl
		<< "5. Comparison" << endl
		<< "0. To exit the program." << endl << endl
		<< "	> ";
	cin >> choice;
	cout << endl << "First Number: " << endl;
	cin >> firstNum;
	cout << "Second Number:" << endl;
	cin >> secondNum;

	List<char> fNum (firstNum);
	List<char> sNum (secondNum);
	List<char> result;

	switch (choice) {
		case '1': {
			if (fNum.isNumber () && sNum.isNumber ()) {
				bool d = isFloat (firstNum);
				bool o = isFloat (secondNum);

				if (!d && o) {
					fNum.empty ();
					fNum.fromString (convertToFloat (firstNum));
					firstNum = convertToFloat (firstNum);
				}
				else if (!o && d) {
					sNum.empty ();
					sNum.fromString (convertToFloat (secondNum));
					secondNum = convertToFloat (secondNum);
				}

				/*fNum.display ();
				cout << " " << fNum.isNegative << " " << fNum.count << endl;
				sNum.display ();
				cout << " " << sNum.isNegative << " " << sNum.count << endl;*/

				if (fNum.isNegative && sNum.isNegative) {
					result.isNegative = true;
				}
				else if (!fNum.isNegative && !sNum.isNegative) {
					result.isNegative = false;
				}
				else if (!fNum.isNegative && sNum.isNegative) {
					// call subtract function
				}
				else {
					// call subtract function
				}

				string fNumDec = decimalPart (fNum.toString ());
				string fNumInt = integeralPart (fNum.toString ());
				string sNumDec = decimalPart (sNum.toString ());
				string sNumInt = integeralPart (sNum.toString ());


				fillZerosToIntegeralPart (fNumInt, sNumInt);
				fillZerosToDecimalPart (fNumDec, sNumDec);

				string decimalSum, integeralSum;
				decimalSum = addDecimalPart (fNumDec, sNumDec);
				integeralSum = "";
				if (decimalSum.size () > maxDecDigits) {
					integeralSum = addIntgeralPart (fNumInt, sNumInt, 1);
					List<char> temp (decimalSum);
					temp.removeFirst ();
					decimalSum = temp.toString ();
				}
				else {
					integeralSum = addIntgeralPart (fNumInt, sNumInt);
				}

				for (int i = 0; i < integeralSum.size (); i++) {
					result.insertLast (integeralSum[i]);
				}
				result.insertLast ('.');
				for (int i = 0; i < decimalSum.size (); i++) {
					result.insertLast (decimalSum[i]);
				}

				if (result.isNegative) {
					cout << "Sum = -";
					result.display ();
					cout << endl;
				}
				else {
					cout << "Sum = ";
					result.display ();
					cout << endl;
				}
			}
			else cout << "Both inputs must be numbers" << endl;
			break;
		}
		case '2': {
			if (fNum.isNumber () && sNum.isNumber ()) {
				bool d = isFloat (firstNum);
				bool o = isFloat (secondNum);

				if (!d && o) {
					fNum.empty ();
					fNum.fromString (convertToFloat (firstNum));
					firstNum = convertToFloat (firstNum);
				}
				else if (!o && d) {
					sNum.empty ();
					sNum.fromString (convertToFloat (secondNum));
					secondNum = convertToFloat (secondNum);
				}

				if (fNum.isNegative && sNum.isNegative) {
					result.isNegative = true;
				}
				else if (!fNum.isNegative && !sNum.isNegative) {
					result.isNegative = false;
				}
				else if (!fNum.isNegative && sNum.isNegative) {
					// call subtract function
				}
				else {
					// call subtract function
				}

				string fNumDec = decimalPart (fNum.toString ());
				string fNumInt = integeralPart (fNum.toString ());
				string sNumDec = decimalPart (sNum.toString ());
				string sNumInt = integeralPart (sNum.toString ());


				fillZerosToIntegeralPart (fNumInt, sNumInt);
				fillZerosToDecimalPart (fNumDec, sNumDec);


				
			}
			else cout << "Both inputs must be numbers" << endl;
			break;
		}
		case '3': break;
		case '4': break;
		case '5': break;
		case '0': exit (0); break;
		default:
			cout << "Invalid choice." << endl;
			system ("pause");
			system ("cls");
			break;
	}
}

int main () {
	/*string firstNum, secondNum, operation;
	ExtremeFloat result;
	do {
		operation = menu (firstNum, secondNum);
		result = calculator (firstNum, secondNum, operation);
	} while (true);*/

	/*List<char> list ("-0.6905");
	list.display ();
	cout << endl << list.isNegative << endl << list.isFloat << endl;
	list.trim ();
	list.display ();
	string temp = list.toString ();
	cout << endl << list.isNegative << endl << list.isFloat << endl;
	cout << endl << list.count << endl;

	list.empty ();
	cout << endl << list.isNegative << endl << list.isFloat << endl;
	cout << endl << list.count << endl;

	cout << endl << temp << endl;*/


	string a = "123000";
	string b = "223";

	/*menu ();*/

	List<char> list;
	list.inser

	/*List<char> list (a);
	list.display ();
	cout << endl;
	list.trim ();
	cout << endl;
	list.display ();*/


	/*fillZerosToIntegeralPart (a, b);

	int res = compare (a, b);
	if (res == 1) {
		cout << a << " is greater than " << b;
	}
	else if (res == -1) {
		cout << b << " is greater than " << a;
	}
	else {
		cout << a << " = " << b;
	}
	cout << endl;*/

	/*List<char> list (a);
	list.display ();
	cout << endl;
	for (size_t i = 0; i < b.size (); i++) {
		cout << int (b[i] - 48);
	}
	cout << endl;*/

	/*cout << a << endl;
	trim (a);
	cout << a << endl;

	bool d = isFloat (a);
	bool o = isFloat (b);

	if (!d && o) {
		a = convertToFloat (a);
	}
	else if (!o && d) {
		b = convertToFloat (b);
	}

	string aDec = decimalPart (a);
	string aInt = integeralPart (a);
	string bDec = decimalPart (b);
	string bInt = integeralPart (b);

	cout << a << " " << b << endl;
	fillZerosToIntegeralPart (aInt, bInt);
	fillZerosToDecimalPart (aDec, bDec);
	cout << endl << maxDecDigits << endl;
	cout << aInt << "." << aDec << " " << bInt << "." << bDec << endl;*/

	system ("pause");
	return 0;
}