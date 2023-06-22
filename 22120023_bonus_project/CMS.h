#ifndef _course_management_system_h_
#define _course_management_system_h_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

#define max_num_of_students 50

typedef struct DATE_OF_BIRTH
{
	int d = 0, m = 0, y = 0;
} birth;

//typedef struct SESSION
//{
//	string d_o_w; // day of week: MON/TUE/WED/THU/FRI/SAT
//	string lesson; // S1:7h30; S2:9h30; S3:13h30; S4:15h30;
//} session;

typedef struct STAFF
{
	string ID;
	string name;
	string gender;
	birth d_o_b; // day of birth
	string pass_word;
} staff;

typedef struct STUDENT
{
	string student_ID;
	string first_name;
	string last_name;
	string gender;
	birth d_o_b; // day of birth
	string social_ID;
	string pass_word;
} student;

typedef struct SCHOOL_YEAR
{
	int start_y = 0;
	int end_y = 0;
} school_year;

typedef struct CLASSES
{
	school_year sch_y;
	string name_cla;	//class
	int n_o_stu_in_cla = 0;	// num of students in class
	student** list_stu_of_class;
} classes;

typedef struct COURSE
{
	int ID = 0;
	string course_name;
	string class_name;
	staff staff_name;
	int num_of_credits = 0;
	//school_year 
} course;

typedef struct SEMESTER
{
	school_year sch_y;	//school_year
	int semester = 0; // 1:Fall; 2:Summer; 3:Autumn;
} semester;

//COMMON
void GotoXY(int x, int y);
void textColor(int color);
void display_frame();
//void cleanConsole();
void invalidInput();
bool sign_out();
void menu_common_1();
void menu_common_2();

//STAFF
staff** init_list_staffs(int& n_o_staffs);
staff* sign_in_staff(staff** list_staffs, int n_o_staffs);
bool change_password_staff(staff* staff);
void display_staff(staff* staff);
void display_profile_staff(staff* staff);
void display_list_staffs(staff** list_staffs, int n_o_staffs);
school_year create_school_year();
classes** create_classes(school_year sch_y, int& n_o_cla);
void menu_staff_1();
void working_console_staff(staff** list_staffs, int n_o_staffs, int& opt);

//STUDENT
student** init_list_students(string file_name, int& n_o_students);
student* sign_in_student(student** list_students, int n_o_students);
bool change_password_student(student* student);
void display_student_personal(student* student);
void display_student_frame(student* student);
void display_list_students(student** list_students, int n_o_students);
void menu_student_1();
void working_console_student(student** list_students, int n_o_students, int& opt);

#endif // !_course_management_system_h_

