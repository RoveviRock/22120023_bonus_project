#include "CMS.h"

int main(int argc, const char* argv[])
{
	int n_o_s = 0; // num of staffs
	/*int count = 0;
	string line;
	fstream csv;
	csv.open("staff.txt", ios_base::in);
	if (!csv)
	{
		cout << "\nMo file CSV that bai!\n";
		return NULL;
	}
	else
	{
		while (getline(csv, line) && !csv.eof())
			count++;
	}
	csv.close();
	n_o_s = count - 1;*/
	staff** list_staffs = init_list_staffs(n_o_s);
	display_list_staffs(list_staffs, n_o_s);
	system("pause");
	return 0;
}