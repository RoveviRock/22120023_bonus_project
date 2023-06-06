#ifndef _course_management_system_h_
#define _course_management_system_h_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
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
	int ID = 0;
	string name;
	string gender;
	birth d_o_b; // day of birth
	string pass_word;
} staff;

//typedef struct STUDENT
//{
//	int student_ID = 0;
//	string first_name;
//	string last_name;
//	string gender;
//	birth d_o_b; // day of birth
//	int social_ID = 0;
//	string pass_word;
//} student;
//
//typedef struct SCHOOL_YEAR
//{
//	int y = 0; // start_year
//	int semester = 0; // 1:Fall; 2:Summer; 3:Autumn;
//} school_year;
//
//typedef struct COURSE
//{
//	int ID = 0;
//	string course_name;
//	string class_name;
//	staff staff_name;
//	int num_of_credits = 0;
//	//school_year 
//} course;

staff** init_list_staffs(int n);

void display_list_staffs(staff** list_staffs, int n);

#endif // !_course_management_system_h_

