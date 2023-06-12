#include "CMS.h"

int main(int argc, const char* argv[])
{
	//int n_o_staffs = 0; 
	//staff** list_staffs = init_list_staffs(n_o_staffs);
	//display_list_staffs(list_staffs, n_o_staffs);

	//cout << "\n\n\n";
	//staff* staff = sign_in_staff(list_staffs, n_o_staffs);
	//if (staff != nullptr)
	//{
	//	int option = -1;
	//	cout << "Login successful";
	//	cout << "\nType 1: Display personal profile information.\nType 2: Change password.\nType 0: Sign out.\nEnter option: ";
	//	//cin >> option;
	//	while (!(cin >> option) || option < 0 || option>2)
	//		invalidInput();
	//	switch (option)
	//	{
	//	case 1:
	//	{
	//		cout << "\nPersonal profile information: ";
	//		display_staff(staff);
	//		break;
	//	}
	//	case 2:
	//	{
	//		if (change_password_staff(staff))
	//			cout << "Password change successful";
	//		break;
	//	}
	//	case 0:
	//	{
	//		bool signout = sign_out();
	//		break;
	//	}
	//	}
	//}
	display_frame();
	int n_o_students = 0;
	student** list_students = init_list_students(n_o_students);
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
	}
	system("pause");
	return 0;
}