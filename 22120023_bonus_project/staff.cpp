#include "CMS.h"

staff** init_list_staffs(int& n_o_staffs)
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
	n_o_staffs = count - 1; // first line includes only the headings
	staff** list_staffs = new staff * [n_o_staffs];
	csv.clear(); // xoa co loi truoc khi su dung seekg(), vi viec doc den cuoi file co the gay ra co loi 'eofbit' va 'failbit'
	csv.seekg(0, ios::beg);
	string line;
	char c;
	getline(csv, line); // first line includes only the headings
	for (int i = 0; i < n_o_staffs; i++)
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

int find_pos_staff_ID(staff** list_staffs, string ID, int a, int b)	//a is the first element's position, b is the last element's position
{
	if (ID<list_staffs[a]->ID || ID>list_staffs[b]->ID)
		return -1;
	int mid = int((a + b) / 2);
	if (ID == list_staffs[mid]->ID)
		return mid;
	else if (ID < list_staffs[mid]->ID)
		return find_pos_staff_ID(list_staffs, ID, a, mid - 1);
	else
		return find_pos_staff_ID(list_staffs, ID, mid + 1, b);
}

staff* sign_in_staff(staff** list_staffs, int n_o_staffs)
{
	staff* staff = nullptr;
	string ID;
	string pass_word;
	cout << "Enter staff ID: ";
	while (!(getline(cin, ID)))
		invalidInput();
	int pos = find_pos_staff_ID(list_staffs, ID, 0, n_o_staffs - 1);
	if (pos != -1)
	{
		cout << "Enter password: ";
		while (!(getline(cin, pass_word)))
			invalidInput();
		while (pass_word != list_staffs[pos]->pass_word)
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
		return list_staffs[pos];
	}
	/*for (int i = 0; i < n_o_staffs; i++)
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
	}*/
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

void display_list_staffs(staff** list_staffs, int n_o_staffs)
{
	for (int i = 0; i < n_o_staffs; i++)
	{
		cout << "\nSTT: " << i + 1;
		display_staff(list_staffs[i]);
	}
}

school_year create_school_year()
{
	//cout << "Number of classes to create: ";
	//int n_o_sch_y;	// num of school years
	//cin >> n_o_sch_y;
	school_year sch_y;
	cout << "Enter year start: ";
	while (!(cin >> sch_y.start_y) || sch_y.start_y < 1000)
		invalidInput();
	sch_y.end_y = sch_y.start_y + 1;
	return sch_y;
}

//void create_class();