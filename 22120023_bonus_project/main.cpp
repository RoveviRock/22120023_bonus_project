#include "CMS.h"

int main(int argc, const char* argv[])
{
	display_frame();
	int n_o_staffs = 0; 
	staff** list_staffs = init_list_staffs(n_o_staffs);
	int n_o_students = 0;
	student** list_students = init_list_students("student.txt", n_o_students);
	school_year sch_y;
	classes** list_classes = nullptr;
	semester sem;
	int opt = -1;	//option
	while(opt != 0)
	{
		menu_common_1();
		while (!(cin >> opt) || opt < 0 || opt>2)
			invalidInput();
		system("cls");
		display_frame();
		cin.ignore(1000, '\n');
		switch (opt)
		{
		case 1:
		{
			working_console_staff(list_staffs, n_o_staffs, opt, sch_y, list_classes, sem, list_students, n_o_students);
			break;
		}
		case 2:
		{
			working_console_student(list_students, n_o_students, opt);
			break;
		}
		case 0:
		{
			system("cls");
			display_frame();
			break;
		}
		}
	}
	system("pause");
	return 0;
}