#include "CMS.h"

int main(int argc, const char* argv[])
{
	//int n_o_s = 0; 
	//staff** list_staffs = init_list_staffs(n_o_s);
	//display_list_staffs(list_staffs, n_o_s);

	//cout << "\n\n\n";
	//staff* staff = sign_in_staff(list_staffs, n_o_s);
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
	//		display_profile_staff(staff);
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
	//		bool sign_out = sign_out_staff();
	//		break;
	//	}
	//	}
	//}
	//display_list_staffs(list_staffs, n_o_s);

	int n_o_students = 0;
	student** list_students = init_list_students(n_o_students);
	display_list_students(list_students, n_o_students);
	system("pause");
	return 0;
}