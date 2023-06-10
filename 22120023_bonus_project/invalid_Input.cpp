#include "CMS.h"

void invalidInput()
{
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "The entered data is invalid\nPlease re-enter: ";
}