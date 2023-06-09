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

	cout << "\n\n\n";
	staff* staff = sign_in_staff(list_staffs, n_o_s);
	if (staff != nullptr)
	{
		int option = -1;
		cout << "Login successful";
		cout << "\nType 1: Display personal profile information.\nType 0: Sign out.\nEnter option: ";
		cin >> option;
		/*while (!(cin >> option) || option < 0 || option>1)
			invalidInput();*/
		switch (option)
		{
		case 1:
		{
			display_profile(staff);
			break;
		}
		case 0:
		{
			bool sign_out = sign_out_staff();
			break;
		}
		}
	}
	system("pause");
	return 0;
}