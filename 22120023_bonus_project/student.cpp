#include "CMS.h"

student** init_list_students(int& n_o_students)
{
	string count_line;
	int count = 0;
	fstream csv;
	csv.open("student.txt", ios_base::in);
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
	n_o_students = count - 1; // first line includes only the headings
	student** list_students = new student * [n_o_students];
	csv.clear(); // xoa co loi truoc khi su dung seekg(), vi viec doc den cuoi file co the gay ra co loi 'eofbit' va 'failbit'
	csv.seekg(0, ios::beg);
	string line;
	char c;
	getline(csv, line); // first line includes only the headings
	for (int i = 0; i < n_o_students; i++)
	{
		list_students[i] = new student;
		getline(csv, list_students[i]->student_ID, ',');
		getline(csv, list_students[i]->first_name, ',');
		getline(csv, list_students[i]->last_name, ',');
		getline(csv, list_students[i]->gender, ',');
		csv >> list_students[i]->d_o_b.d;
		csv >> list_students[i]->d_o_b.m;
		csv >> list_students[i]->d_o_b.y;
		csv >> c; // read ','
		getline(csv, list_students[i]->social_ID, ',');
		getline(csv, list_students[i]->pass_word);
	}
	csv.close();
	return list_students;
}

int find_pos_student_ID(student** list_students, string ID, int a, int b)	//a is the first element's position, b is the last element's position
{
	if (ID<list_students[a]->student_ID || ID>list_students[b]->student_ID)
		return -1;
	int mid = int((a + b) / 2);
	if (ID == list_students[mid]->student_ID)
		return mid;
	else if (ID < list_students[mid]->student_ID)
		return find_pos_student_ID(list_students, ID, a, mid - 1);
	else
		return find_pos_student_ID(list_students, ID, mid + 1, b);
}

student* sign_in_student(student** list_students, int n_o_students)
{
	student* student = nullptr;
	string ID;
	string pass_word;
	cout << "Enter student ID: ";
	while (!(getline(cin, ID)))
		invalidInput();
	int pos = find_pos_student_ID(list_students, ID, 0, n_o_students - 1);
	if (pos != -1)
	{
		cout << "Enter password: ";
		while (!(getline(cin, pass_word)))
			invalidInput();
		while (pass_word != list_students[pos]->pass_word)
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
		return list_students[pos];
	}
	/*for (int i = 0; i < n_o_students; i++)
	{
		if (ID == list_students[i]->student_ID)
		{
			cin.ignore(1000, '\n');
			cout << "Enter password: ";
			while (!(getline(cin, pass_word)))
				invalidInput();
			while (pass_word != list_students[i]->pass_word)
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
			return list_students[i];
		}
	}*/
	return nullptr;
}

bool change_password_student(student* student)
{
	cin.ignore(1000, '\n');
	string pass_word;
	cout << "Enter old password: ";
	while (!(getline(cin, pass_word)))
		invalidInput();
	while (pass_word != student->pass_word)
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
	while (!(getline(cin, student->pass_word)))
		invalidInput();
	return true;
}

void display_student(student* student)
{
	cout << "\nStudent ID: " << student->student_ID;
	cout << "\nFirst Name: " << student->first_name;
	cout << "\nLast Name: " << student->last_name;
	cout << "\nGender: " << student->gender;
	cout << "\nDay of birth: " << student->d_o_b.d << "/" << student->d_o_b.m << "/" << student->d_o_b.y;
	cout << "\nSocial ID: " << student->social_ID << endl;
}

void display_list_students(student** list_students, int n_o_students)
{
	for (int i = 0; i < n_o_students; i++)
	{
		cout << "\nSTT: " << i + 1;
		display_student(list_students[i]);
	}
}