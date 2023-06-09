#include "CMS.h"

void invalidInput()
{
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "The entered data is invalid\nPlease re-enter: ";
}

staff** init_list_staffs(int& n_o_s)
{
	string count_line;
	int count = 0;
	fstream csv;
	csv.open("staff.txt", ios_base::in);
	if (!csv)
	{
		cout << "\nMo file CSV that bai!\n";
		return NULL;
	}
	else
	{
		while (getline(csv, count_line) && !csv.eof())
			count++;
	}
	n_o_s = count - 1; // first line includes only the headings
	staff** list_staffs = new staff * [n_o_s];
	csv.clear(); // xoa co loi truoc khi su dung seekg(), vi viec doc den cuoi file co the gay ra co loi 'eofbit' va 'failbit'
	csv.seekg(0, ios::beg);
	string line;
	char c;
	getline(csv, line); // first line includes only the headings
	for (int i = 0; i < n_o_s; i++)
	{
		list_staffs[i] = new staff;
		csv >> list_staffs[i]->ID;
		csv >> c; // read ','
		getline(csv, list_staffs[i]->name, ',');
		getline(csv, list_staffs[i]->gender, ',');
		csv >> list_staffs[i]->d_o_b.d;
		csv >> list_staffs[i]->d_o_b.m;
		csv >> list_staffs[i]->d_o_b.y;
		csv >> c; // read ','
		getline(csv, list_staffs[i]->pass_word);
	}
	csv.close();
	return list_staffs;
}

//bool sign_in_staff(staff** list_staffs, int n_o_s)
//{
//	bool check = false;
//	int ID = 0;
//	string pass_word;
//	cout << "Enter staff ID: ";
//	while (!(cin >> ID))
//		invalidInput();
//	for (int i = 0; i < n_o_s; i++)
//	{
//		if (ID == list_staffs[i]->ID)
//		{
//			cout << "Enter password: ";
//			while (!(getline(cin, pass_word)))
//				invalidInput();
//			while (pass_word != list_staffs[i]->pass_word)
//			{
//				int option = -1;
//				cout << "Password is not correct\nType 1: Re-enter password.\nType 0: Forgot password.\nEnter option: ";
//				while (!(cin >> option) || option < 0 || option>1)
//					invalidInput();
//				switch (option)
//				{
//				case 1:
//				{
//					cout << "Re-enter password: ";
//					while (!(getline(cin, pass_word)))
//						invalidInput();
//					break;
//				}
//				case 0:
//				{
//					cout << "Sign in failed\n";
//					return false;
//					//break;
//				}
//				}
//			}
//			return true;
//		}
//	}
//	return false;
//}

staff* sign_in_staff(staff** list_staffs, int n_o_s)
{
	staff* staff = nullptr;
	bool check = false;
	int ID = 0;
	string pass_word;
	cout << "Enter staff ID: ";
	while (!(cin >> ID))
		invalidInput();
	for (int i = 0; i < n_o_s; i++)
	{
		if (ID == list_staffs[i]->ID)
		{
			cin.ignore(1000, '\n');
			cout << "Enter password: ";
			while (!(getline(cin, pass_word)))
				invalidInput();
			while (pass_word != list_staffs[i]->pass_word)
			{
				int option = -1;
				cout << "Password is not correct\nType 1: Re-enter password.\nType 0: Forgot password.\nEnter option: ";
				while (!(cin >> option) || option < 0 || option>1)
					invalidInput();
				switch (option)
				{
				case 1:
				{
					cin.ignore(1000, '\n');
					cout << "Re-enter password: ";
					while (!(getline(cin, pass_word)))
						invalidInput();
					break;
				}
				case 0:
				{
					cout << "Sign in failed\n";
					//return staff;
					return nullptr;
					//break;
				}
				}
			}
			/*staff = list_staffs[i];
			return staff;*/
			return list_staffs[i];
		}
	}
	return nullptr;
	//return staff;
}


bool sign_out_staff()
{
	int option = -1;
	cout << "Are you sure you want to sign out?\nType 1: Sign out.\nType 0: No.\nEnter option: ";
	while (!(cin >> option) || option < 0 || option>1)
		invalidInput();
	switch (option)
	{
	case 1:
	{
		return true;
		//break;
	}
	case 0:
	{
		return false;
		//break;
	}
	}
	return true;
}

void display_staff(staff* staff)
{
	cout << "\nID: " << staff->ID;
	cout << "\nName: " << staff->name;
	cout << "\nGender: " << staff->gender;
	cout << "\nDay of birth: " << staff->d_o_b.d << "/" << staff->d_o_b.m << "/" << staff->d_o_b.y << endl;
}

void display_profile(staff* staff)
{
	cout << "\nPersonal profile information: ";
	display_staff(staff);
}

void display_list_staffs(staff** list_staffs, int n_o_s)
{
	for (int i = 0; i < n_o_s; i++)
	{
		cout << "\nSTT: " << i + 1;
		display_staff(list_staffs[i]);
		/*cout << "\nID: " << list_staffs[i]->ID;
		cout << "\nName: " << list_staffs[i]->name;
		cout << "\nGender: " << list_staffs[i]->gender;
		cout << "\nDay of birth: " << list_staffs[i]->d_o_b.d << "/" << list_staffs[i]->d_o_b.m << "/" << list_staffs[i]->d_o_b.y << endl;*/
	}
}