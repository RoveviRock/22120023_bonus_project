#include "CMS.h"

int main(int argc, const char* argv[])
{
	display_frame();
	int n_o_staffs = 0; 
	staff** list_staffs = init_list_staffs(n_o_staffs);
	int n_o_students = 0;
	student** list_students = init_list_students("student.txt", n_o_students);
	int opt = -1;	//option
	cout << "You are a staff or a student?\nType 1: Staff.\nType 2: Student.\n\nPlease type: ";
	while (!(cin >> opt) || opt < 1 || opt>2)
		invalidInput();
	system("cls");
	display_frame();
	if (opt == 1)
	{
		cin.ignore(1000, '\n');
		working_console_staff(list_staffs, n_o_staffs);
	}
	
	/*display_frame();
	
	display_list_students(list_students, n_o_students);
	cout << "\n\n\n";
	student* student = sign_in_student(list_students, n_o_students);
	if (student != nullptr)
	{
		int option = -1;
		cout << "Login successful";
		cout << "\nType 1: Display personal profile information.\nType 2: Change password.\nType 0: Sign out.\nEnter option: ";
		while (!(cin >> option) || option < 0 || option>2)
			invalidInput();
		switch (option)
		{
		case 1:
		{
			cout << "\nPersonal profile information: ";
			display_student(student);
			break;
		}
		case 2:
		{
			if (change_password_student(student))
				cout << "Password change successful";
			break;
		}
		case 0:
		{
			bool signout = sign_out();
			break;
		}
		}
	}*/
	system("pause");
	return 0;
}