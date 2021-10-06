#include <iostream>
#include "List.cpp"
using namespace std;

List<char> add (List<char> x, List<char> y);
List<char> subtract (List<char> x, List<char> y);
List<char> multiply (List<char> x, List<char> y);
List<char> divide (List<char> x, List<char> y);
int compare (List<char> x, List<char>);

class ExtremeFloat : public List<char> {
public:
	ExtremeFloat ();
	ExtremeFloat (string);
	ExtremeFloat (List<char> &number);
	~ExtremeFloat ();

	bool isFloat;
	bool isNegative;
private:
	void trim (List<char> * number);
};

// constructor of the ExtremeFloat object
ExtremeFloat::ExtremeFloat () {
	isNegative = false;
	isFloat = false;
}

// alternate constructor of ExtremeFloat object
ExtremeFloat::ExtremeFloat (string str) {
	isNegative = false;
	isFloat = false;
	if (str.size() != 0) {
		for (int i = 0; i < str.size(); i++) {
			List::insertLast (str[i]);
		}
	}
}