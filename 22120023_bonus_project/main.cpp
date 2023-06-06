#include "CMS.h"

int main(int argc, const char* argv[])
{
	int count = 0;
	string line;
	fstream csv;
	csv.open("staff.txt", ios_base::in);
	if (!csv)
	{
		cout << "\nMo file CVS that bai!\n";
		return NULL;
	}
	else
	{
		while (getline(csv, line) && !csv.eof())
			count++;
	}
	csv.close();
	staff** list_staffs = init_list_staffs(count - 1);
	display_list_staffs(list_staffs, count - 1);
	system("pause");
	return 0;
}