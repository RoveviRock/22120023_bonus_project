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
			cout << "\nPassword is not correct\nType 1: Re-enter password.\nType 0: Forgot password.\n\nEnter option: ";
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
				system("cls");
				display_frame();
				cout << "Sign in failed\n";
				return nullptr;
			}
			}
		}
		return list_staffs[pos];
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
		cout << "\nOld password is not correct\nType 1: Re-enter old password.\nType 0: Forgot old password.\n\nEnter option: ";
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
			system("cls");
			display_frame();
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
	cout << "\nAre you sure you want to sign out?\nType 1: Sign out.\nType 0: No.\n\nEnter option: ";
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
	school_year sch_y;
	cout << "Enter start year of school year: ";
	while (!(cin >> sch_y.start_y) || sch_y.start_y < 1000)
		invalidInput();
	sch_y.end_y = sch_y.start_y + 1;
	return sch_y;
}

classes** create_classes(school_year sch_y, int& n_o_cla)
{
	cout << "Enter number of classes: ";
	while (!(cin >> n_o_cla) || n_o_cla < 1)
		invalidInput();
	classes** list_classes;
	list_classes = new classes * [n_o_cla];
	int i = 0;
	cin.ignore(1000, '\n');
	while (i < n_o_cla)
	{
		list_classes[i] = new classes;
		list_classes[i]->sch_y = sch_y;
		cout << "Enter name of class " << i + 1 << "(APCS1/APCS2/CTT2/CTT3/CLC1/CLC2/VP/...): ";
		while (!(getline(cin, list_classes[i]->name_cla)))
			invalidInput();
		list_classes[i]->name_cla = to_string(sch_y.start_y % 100) + list_classes[i]->name_cla;
		string file_name = list_classes[i]->name_cla + ".txt";
		list_classes[i]->list_stu_of_class = init_list_students(file_name, list_classes[i]->n_o_stu_in_cla);
		i++;
	}
	return list_classes;
}

void menu_staff_1()
{
	cout << "\nType 1: Display personal profile information.";
	cout << "\nType 2: Change password.";
	cout << "\nType 3: Management school year.";
	cout << "\nType 0: Sign out.\n\nEnter option: ";
}

void working_console_staff(staff** list_staffs, int n_o_staffs)
{
	staff* staff = sign_in_staff(list_staffs, n_o_staffs);
	if (staff != nullptr)
	{
		system("cls");
		display_frame();
		cout << "Login successful";
		int option = -1;
		while (option != 0)
		{
			menu_staff_1();
			while (!(cin >> option) || option < 0 || option>3)
				invalidInput();
			switch (option)
			{
			case 1:
			{
				system("cls");
				display_frame();
				cout << "Personal profile information: ";
				display_staff(staff);
				break;
			}
			case 2:
			{
				system("cls");
				display_frame();
				if (change_password_staff(staff))
				{
					system("cls");
					display_frame();
					cout << "Password change successful";
				}
				break;
			}
			case 3:
			{
				system("cls");
				display_frame();
				school_year sch_y = create_school_year();
				int n_o_cla = 0;
				classes** list_classes = create_classes(sch_y, n_o_cla);
				system("cls");
				display_frame();
				for (int i = 0; i < n_o_cla; i++)
				{
					cout << "Class " << list_classes[i]->name_cla << " list of students:\n";
					display_list_students(list_classes[i]->list_stu_of_class, list_classes[i]->n_o_stu_in_cla);
					cout << "\n\n";
				}
				break;
			}
			case 0:
			{
				if (!sign_out())
					option = -1;
				break;
			}
			}
			if (option != -1 && option != 0)
			{
				menu_common();
				while (!(cin >> option) || option < 0 || option>1)
					invalidInput();
				if (option == 0)
					if (!sign_out())
						option = -1;
			}
			system("cls");
			display_frame();
		}
	}
}
