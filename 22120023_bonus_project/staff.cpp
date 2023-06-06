#include "CMS.h"

//staff* init_staff(string line)
//{
//	staff* a_s; // academic_staff
//	/*string ID, day, month, year;
//	getline(line, ID, ',');
//	list_staffs[i]->ID = stoi(ID);
//	csv >> list_staffs[i]->ID;
//
//	getline(csv, list_staffs[i]->name, ',');
//	getline(csv, list_staffs[i]->gender, ',');
//	getline(csv, day, ' ');
//	list_staffs[i]->d_o_b.d = stoi(day);
//	csv >> list_staffs[i]->d_o_b.d;
//	getline(csv, month, ' ');
//	list_staffs[i]->d_o_b.m = stoi(month);
//	csv >> list_staffs[i]->d_o_b.m;
//	getline(csv, year, ',');
//	list_staffs[i]->d_o_b.y = stoi(year);
//	csv >> list_staffs[i]->d_o_b.y;
//	getline(csv, list_staffs[i]->pass_word);*/
//}

staff** init_list_staffs(int n)
{
	fstream csv;
	csv.open("staff.txt", ios_base::in);
	if (!csv)
	{
		cout << "\nMo file CVS that bai!\n";
		return NULL;
	}
	staff** list_staffs = new staff * [n];
	string line;
	char c;
	getline(csv, line); // first line includes only the headings
	for (int i = 0; i < n; i++)
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

void display_list_staffs(staff** list_staffs, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "\nSTT: " << i + 1;
		cout << "\nID: " << list_staffs[i]->ID;
		cout << "\nName: " << list_staffs[i]->name;
		cout << "\nGender: " << list_staffs[i]->gender;
		cout << "\nDay of birth: " << list_staffs[i]->d_o_b.d << "/" << list_staffs[i]->d_o_b.m << "/" << list_staffs[i]->d_o_b.y << endl;
	}
}