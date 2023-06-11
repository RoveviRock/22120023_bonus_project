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