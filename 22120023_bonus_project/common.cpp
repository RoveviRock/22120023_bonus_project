#include "CMS.h"

void GotoXY(int x, int y) 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void display_frame()
{
	int x = 0, y = 0, w = 90, h = 3;
	if (w <= 1 || h <= 1)
		return;
	//Frame
	textColor(3);
	for (int ix = x; ix <= x + w; ix++)
	{
		GotoXY(ix, y); cout << char(205);
		GotoXY(ix, y + h); cout << char(205);
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		GotoXY(x, iy); cout << char(186);
		GotoXY(x + w, iy); cout << char(186);
	}
	GotoXY(x, y); cout << char(201); 
	GotoXY(x + w, y); cout << char(187);	 
	GotoXY(x, y + h); cout << char(200);
	GotoXY(x + w, y + h); cout << char(188);
	//Background
	textColor(27);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			GotoXY(ix, iy); cout << " ";
		}
	}
	//Text
	string text1 = "COURSE MANAGEMENT SYSTEM";
	string text2 = "22120023    -    Le Nguyen Gia Bao    -    22CTT2";
	GotoXY((w - text1.length()) / 2, 1);
	cout << text1;
	GotoXY((w - text2.length()) / 2, 2);
	cout << text2;
	GotoXY(x, h + 1);
	textColor(7);
}

//void cleanConsole()
//{
//	HANDLE hOut;
//	COORD Position;
//	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	Position.X = 0;
//	Position.Y = 0;
//	SetConsoleCursorPosition(hOut, Position);
//}

void invalidInput()
{
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "The entered data is invalid\nPlease re-enter: ";
}

bool sign_out()
{
	system("cls");
	display_frame();
	int option = -1;
	cout << "Are you sure you want to sign out?\nType 1: Sign out.\nType 0: No.\n\nEnter option: ";
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

void menu_common_1()
{
	cout << "You are a staff or a student?\nType 1: Staff.\nType 2: Student.\nType 0: Exit the system.\n\nPlease type: ";
}

void menu_common_2()
{
	cout << "\nContinue or sign out?\nType 1: Continue.\nType 0: Sign out.\n\nEnter option: ";
}