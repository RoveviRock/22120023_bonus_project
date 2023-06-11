#include "CMS.h"

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
		getline(csv, list_staffs[i]->ID, ',');
		/*csv >> list_staffs[i]->ID;
		csv >> c;*/ // read ','
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

staff* sign_in_staff(staff** list_staffs, int n_o_s)
{
	staff* staff = nullptr;
	bool check = false;
	string ID;
	string pass_word;
	cout << "Enter staff ID: ";
	while (!(getline(cin, ID)))
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
					return nullptr;
				}
				}
			}
			return list_staffs[i];
		}
	}
	return nullptr;
}

bool change_password_staff(staff* staff)
{
	cin.ignore(1000, '\n');
	string pass_word;
	cout << "Enter old password: ";
	while (!(getline(cin, pass_word)))
		invalidInput();
	while (pass_word != staff->pass_word)
	{
		int option = -1;
		cout << "Old password is not correct\nType 1: Re-enter old password.\nType 0: Forgot old password.\nEnter option: ";
		while (!(cin >> option) || option < 0 || option>1)
			invalidInput();
		switch (option)
		{
		case 1:
		{
			cin.ignore(1000, '\n');
			cout << "Re-enter old password: ";
			while (!(getline(cin, pass_word)))
				invalidInput();
			break;
		}
		case 0:
		{
			cout << "Password change failed\n";
			return false;
		}
		}
	}
	cout << "Enter new password: ";
	while (!(getline(cin, staff->pass_word)))
		invalidInput();
	return true;
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
	}
	case 0:
	{
		return false;
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

void display_profile_staff(staff* staff)
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
	}
}