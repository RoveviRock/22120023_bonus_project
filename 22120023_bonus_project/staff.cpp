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
	cout << "\nType 3: Create a school year and several classes.";
	cout << "\nType 4: Management a semester.";
	cout << "\nType 5: Exit the system.";
	cout << "\nType 0: Sign out.\n\nEnter option: ";
}

void menu_staff_2()
{
	cout << "\nType 1: Create current semester.";
	cout << "\nType 2: Add a course.";
	cout << "\nType 3: Display the list of courses.";
	cout << "\nType 4: Update course information.";
	cout << "\nType 5: Add a student to the course.";
	cout << "\nType 6: Remove a student from the course.";
	cout << "\nType 7: Delete a course.";
	cout << "\nType 8: Back to main menu.";
	cout << "\nType 9: Exit the system.";
	cout << "\nType 0: Sign out.\n\nEnter option: ";
}

course* create_course()
{
	cin.ignore(1000, '\n');
	course* cou = new course;
	cout << "Enter course ID: ";
	while (!(getline(cin, cou->ID)))
		invalidInput();
	cout << "Enter course name: ";
	while (!(getline(cin, cou->course_name)))
		invalidInput();
	cout << "Enter class name: ";
	while (!(getline(cin, cou->class_name)))
		invalidInput();
	cout << "Enter teacher name: ";
	while (!(getline(cin, cou->staff_name.name)))
		invalidInput();
	cout << "Enter the day of the week and the sesion that the course will be performed:\n";
	cout << "Enter the day of the week (MON/TUE/WED/THU/FRI/SAT): ";
	while (!(getline(cin, cou->ses.d_o_w)))
		invalidInput();
	cout << "Enter the sesion (S1:7h30; S2:9h30; S3:13h30; S4:15h30;): ";
	while (!(getline(cin, cou->ses.lesson)))
		invalidInput();
	cout << "Enter number of credits: ";
	while (!(cin >> cou->num_of_credits) || cou->num_of_credits < 1)
		invalidInput();
	string file_name = cou->ID + ".txt";
	cou->list_stu_of_cou = init_list_students(file_name, cou->n_o_stu_in_cou);
	return cou;
}

void display_course(course* course)
{
	cout << "\nCourse ID: " << course->ID;
	cout << "\nCourse name: " << course->course_name;
	cout << "\nClass name: " << course->class_name;
	cout << "\nTeacher name: " << course->staff_name.name;
	cout << "\nNumber of credits: " << course->num_of_credits;
	cout << "\nThe day of the week and the sesion that the course will be performed: " << course->ses.d_o_w << ", " << course->ses.lesson;
	cout << "\nCourse " << course->course_name << " list of students:\n";
	display_list_students(course->list_stu_of_cou, course->n_o_stu_in_cou);
	cout << "\n\n";
}

void display_list_courses(course** list_courses, int n_o_cou)
{
	for (int i = 0; i < n_o_cou; i++)
	{
		cout << "\nCourse " << i + 1 << ":";
		display_course(list_courses[i]);
		cout << endl;
	}
}

void management_semester(int& option, int& option_2, int& opt, school_year& sch_y, classes**& list_classes, semester& sem, student** list_students, int n_o_students)
{
	system("cls");
	display_frame();
	switch (option_2)
	{
	case 1:
	{
		if (sch_y.start_y == 0)
			cout << "School year has not been created\nPlease continue, type 8 to back to main menu then type 3 to create a school year\n";
		else
		{
			cout << "Semester 1(Fall) or 2(Summer) or 3(Autumn)?\n\nType 1/2/3: ";
			while (!(cin >> sem.semester) || sem.semester < 1 || sem.semester > 3)
				invalidInput();
			cout << "\nThis semester belongs to the school year " << sch_y.start_y << "-" << sch_y.end_y << endl;
			cout << "Enter start day of this semester (dd/mm/yyyy) (standard input required): ";
			while (!(cin >> sem.start_d >> sem.start_m >> sem.start_y))
				invalidInput();
			cout << "Enter end day of this semester (dd/mm/yyyy) (standard input required): ";
			while (!(cin >> sem.end_d >> sem.end_m >> sem.end_y))
				invalidInput();
			sem.list_courses = nullptr;
		}
		break;
	}
	case 2:
	{
		if (sem.semester != 1 && sem.semester != 2 && sem.semester != 3)
			cout << "Semester has not been created\nPlease continue and type 1 to create a semester\n";
		else
		{
			if (sem.n_o_cou == 0)
			{
				sem.n_o_cou++;
				sem.list_courses = new course * [sem.n_o_cou];
				sem.list_courses[0] = create_course();
			}
			else
			{
				sem.n_o_cou++;
				course** new_list_courses = new course * [sem.n_o_cou];
				copy(sem.list_courses, sem.list_courses + sem.n_o_cou - 1, new_list_courses);
				new_list_courses[sem.n_o_cou - 1] = create_course();
				delete[] sem.list_courses;
				sem.list_courses = new_list_courses;
			}
		}
		break;
	}
	case 3:
	{
		display_list_courses(sem.list_courses, sem.n_o_cou);
		break;
	}
	case 4:
	{
		if (sem.n_o_cou == 0)
			cout << "Courses have not been created\nPlease continue and type 3 to add a course\n";
		else
		{
			string cou_ID;
			cin.ignore(1000, '\n');
			cout << "Enter the ID of the course to update information: ";
			while (!(getline(cin, cou_ID)))
				invalidInput();
			bool found = false;
			for (int i = 0; i < sem.n_o_cou; i++)
			{
				if (cou_ID == sem.list_courses[i]->ID)
				{
					found = true;
					int option_3 = -1;
					while (option_3 != 0)
					{
						system("cls");
						display_frame();
						cout << "\nType 1: Update class name.";
						cout << "\nType 2: Update teacher name.";
						cout << "\nType 3: Update the day of the week and the sesion.";
						cout << "\nType 4: Update number of credits.";
						cout << "\nType 0: Done.\n\nEnter option: ";
						while (!(cin >> option_3) || option_3 < 0 || option_3>4)
							invalidInput();						
						cin.ignore(1000, '\n');
						switch (option_3)
						{
						case 1:
						{
							cout << "Enter new class name: ";
							while (!(getline(cin, sem.list_courses[i]->class_name)))
								invalidInput();
							break;
						}
						case 2:
						{
							cout << "Enter new teacher name: ";
							while (!(getline(cin, sem.list_courses[i]->staff_name.name)))
								invalidInput();							
							break;
						}
						case 3:
						{
							cout << "Enter the new day of the week (MON/TUE/WED/THU/FRI/SAT): ";
							while (!(getline(cin, sem.list_courses[i]->ses.d_o_w)))
								invalidInput();
							cout << "Enter the new sesion (S1:7h30; S2:9h30; S3:13h30; S4:15h30;): ";
							while (!(getline(cin, sem.list_courses[i]->ses.lesson)))
								invalidInput();							
							break;
						}
						case 4:
						{
							cout << "Enter number of credits: ";
							while (!(cin >> sem.list_courses[i]->num_of_credits) || sem.list_courses[i]->num_of_credits < 1)
								invalidInput();
							break;
						}
						case 0:
						{
							break;
						}
						}
					}
				}
			}
			if (!found)
				cout << "\nThe course with the ID entered does not exist\n";
		}
		break;
	}
	case 5:
	{
		if (sem.n_o_cou == 0)
			cout << "Courses have not been created\nPlease continue and type 3 to add a course\n";
		else
		{
			string cou_ID;
			cin.ignore(1000, '\n');
			cout << "Enter the ID of the course to add a student: ";
			while (!(getline(cin, cou_ID)))
				invalidInput();
			bool found = false;
			for (int i = 0; i < sem.n_o_cou; i++)
			{
				if (cou_ID == sem.list_courses[i]->ID)
				{
					found = true;
					string stu_ID;
					cout << "Enter student ID of the student added to this course: ";
					while (!(getline(cin, stu_ID)))
						invalidInput();
					int pos = find_pos_student_ID(list_students, stu_ID, 0, n_o_students - 1);
					int pos_2 = find_pos_student_ID(sem.list_courses[i]->list_stu_of_cou, stu_ID, 0, sem.list_courses[i]->n_o_stu_in_cou - 1);
					if (pos != -1 && pos_2 == -1)
					{
						sem.list_courses[i]->n_o_stu_in_cou++;
						student** new_list_stu_o_cou = new student * [sem.list_courses[i]->n_o_stu_in_cou];
						//copy(sem.list_courses[i]->list_stu_of_cou, sem.list_courses[i]->list_stu_of_cou + sem.list_courses[i]->n_o_stu_in_cou - 1, new_list_stu_o_cou);
						if (stu_ID < sem.list_courses[i]->list_stu_of_cou[0]->student_ID)
						{
							copy(sem.list_courses[i]->list_stu_of_cou, sem.list_courses[i]->list_stu_of_cou + sem.list_courses[i]->n_o_stu_in_cou - 1, new_list_stu_o_cou + 1);
							new_list_stu_o_cou[0] = list_students[pos];
						}
						else if (stu_ID > sem.list_courses[i]->list_stu_of_cou[sem.list_courses[i]->n_o_stu_in_cou - 2]->student_ID)
						{
							copy(sem.list_courses[i]->list_stu_of_cou, sem.list_courses[i]->list_stu_of_cou + sem.list_courses[i]->n_o_stu_in_cou - 1, new_list_stu_o_cou);
							new_list_stu_o_cou[sem.list_courses[i]->n_o_stu_in_cou - 1] = list_students[pos];
						}
						else //if(stu_ID > sem.list_courses[i]->list_stu_of_cou[0]->student_ID && stu_ID < sem.list_courses[i]->list_stu_of_cou[sem.list_courses[i]->n_o_stu_in_cou - 2]->student_ID)
						{
							//copy(sem.list_courses[i]->list_stu_of_cou, sem.list_courses[i]->list_stu_of_cou + sem.list_courses[i]->n_o_stu_in_cou - 1, new_list_stu_o_cou);
							for (int j = 0; j < sem.list_courses[i]->n_o_stu_in_cou - 1; j++)
							{
								if (stu_ID > sem.list_courses[i]->list_stu_of_cou[j - 1]->student_ID && stu_ID < sem.list_courses[i]->list_stu_of_cou[j]->student_ID)
								{
									copy(sem.list_courses[i]->list_stu_of_cou, sem.list_courses[i]->list_stu_of_cou + j, new_list_stu_o_cou);
									copy(sem.list_courses[i]->list_stu_of_cou + j, sem.list_courses[i]->list_stu_of_cou + sem.list_courses[i]->n_o_stu_in_cou - 1, new_list_stu_o_cou + j + 1);
									new_list_stu_o_cou[j] = list_students[pos];
									j = sem.list_courses[i]->n_o_stu_in_cou - 1;
								}
							}
						}
						//new_list_stu_o_cou[sem.list_courses[i]->n_o_stu_in_cou - 1] = list_students[pos];
						delete[] sem.list_courses[i]->list_stu_of_cou;
						sem.list_courses[i]->list_stu_of_cou = new_list_stu_o_cou;
					}
					else if (pos != -1 && pos_2 != -1)
						cout << "\nThis student already exists in the course\n";
					else if (pos == -1 && pos_2 == -1)
						cout << "\nStudent ID does not exist\n";
				}
			}
			if (!found)
				cout << "\nThe course with the ID entered does not exist\n";
		}
		break;
	}
	case 6:
	{
		break;
	}
	case 7:
	{
		break;
	}
	case 8:
	{
		option_2 = 0;
		option = -1;
		break;
	}
	case 9:
	{
		option_2 = 0;
		option = 0;
		opt = 0;
		break;
	}
	case 0:
	{
		if (!sign_out())
			option_2 = -1;
		break;
	}
	}
	if (option_2 != -1 && option_2 != 0)
	{
		menu_common_2();
		while (!(cin >> option_2) || option_2 < 0 || option_2>1)
			invalidInput();
		if (option_2 == 0)
		{
			if (!sign_out())
				option_2 = -1;
			else
				option = 0;
		}
	}
	system("cls");
	display_frame();
}

void working_console_staff(staff** list_staffs, int n_o_staffs, int& opt, school_year& sch_y, classes**& list_classes, semester& sem, student** list_students, int n_o_students)
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
			while (!(cin >> option) || option < 0 || option>5)
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
				if (sch_y.start_y != 0)
					cout << "School year has been created\n";
				else
				{
					sch_y = create_school_year();
					int n_o_cla = 0;
					list_classes = create_classes(sch_y, n_o_cla);
					system("cls");
					display_frame();
					for (int i = 0; i < n_o_cla; i++)
					{
						cout << "Class " << list_classes[i]->name_cla << " list of students:\n";
						display_list_students(list_classes[i]->list_stu_of_class, list_classes[i]->n_o_stu_in_cla);
						cout << "\n\n";
					}
				}
				break;
			}
			case 4:
			{
				system("cls");
				display_frame();
				int option_2 = -1;
				while (option_2 != 0)
				{
					menu_staff_2();
					while (!(cin >> option_2) || option_2 < 0 || option_2>9)
						invalidInput();
					management_semester(option, option_2, opt, sch_y, list_classes, sem, list_students, n_o_students);
				}
				break;
			}
			case 5:
			{
				option = 0;
				opt = 0;
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
				menu_common_2();
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
