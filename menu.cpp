#include "Lib.h"

int Point() //Отвечает за '->'
{
	c.Y = 1;
	int menu = 1;
	COORD temp = { 0, 0 };
	while (1)
	{
		SetConsoleCursorPosition(h, c);
		std::cout << "  ";
		SetConsoleCursorPosition(h, c);
		std::cout << point;
		temp.Y = c.Y;
		int key = _getch();
		if (key == 0 || key == 224)
			key = _getch();
		switch (key)
		{
		case 72: //72,75,77,80 - код для клавиш стрелок на клавиатуре
			if (c.Y != 1) //Стрелка вверх
			{
				c.Y--;
				menu--;
			}
			break;
		case 75: //Стрелка вниз
			if (c.Y != 1)
			{
				c.Y--;
				menu--;
			}
			break;
		case 77: //Стрелка вправо
			if (c.Y != stop)
			{
				c.Y++;
				menu++;
			}
			break;
		case 80: //Стрелка влево
			if (c.Y != stop)
			{
				c.Y++;
				menu++;
			}
			break;
		case 13:
			return menu;
		default: break;
		}
		SetConsoleCursorPosition(h, temp);
		std::cout << "  ";
		SetConsoleCursorPosition(h, c);
		std::cout << point;
	}
};
void FirstMenu() //Первый уровень меню
{
	system("cls");
	fmenu = 1;
	stop = 5;
	SetConsoleCursorPosition(h, m);
	std::cout << "____Menu____"
		<< "\n   Feed"
		<< "\n   Group"
		<< "\n   Student"
		<< "\n   DataBase"
		<< "\n   Exit";
	fmenu = Point();
	system("cls");
	std::cout << point;
	switch (fmenu)
	{
	case 1:
		SecondMenu();
	case 2:
		SecondMenu();
	case 3:
		SecondMenu();
	case 4:
		DBMenu();
	case 5:
		exit(1);
	}
};
void SecondMenu() //Второй уровень меню
{
	smenu = 1;
	SetConsoleCursorPosition(h, m);
	switch (fmenu)
	{
	case 1:
		stop = 5;
		std::cout << "____Feed____"
			<< "\n   Print an average grade"
			<< "\n   Print students if they aver. grade > an aver. grade of feed"
			<< "\n   Print excellent pupil"
			<< "\n   Show all groups"
			<< "\n   Back";
		break;
	case 2:
		stop = 4;
		std::cout << "____Group____"
			<< "\n   Add"
			<< "\n   Delete"
			<< "\n   Print"
			<< "\n   Back";
		break;
	case 3:
		stop = 7;
		std::cout << "____Student____"
			<< "\n   Add"
			<< "\n   Print"
			<< "\n   Delete"
			<< "\n   Print excellet pupil of group"
			<< "\n   Print losers of group"
			<< "\n   Print an average grade of group"
			<< "\n   Back";
		break;
	}
	SetConsoleCursorPosition(h, c);
	smenu = Point();
	double t;
	system("cls");
	switch (fmenu)
	{
	case 1:
		switch (smenu)
		{
		case 1:
			t = AverageGrade();
			if (t)
				std::cout << "The average grade is " << t << std::endl;
			_getch();
			system("cls");
			FirstMenu();
		case 2:
			HigherThanTheAverageGrade();
			FirstMenu();
		case 3:
			ExcellentPupil();
			FirstMenu();
		case 4:
			ShowAllGroups();
			FirstMenu();
		case 5:
			FirstMenu();
		}
	case 2:
		switch (smenu)
		{
		case 1:
			CreateGroup();
			FirstMenu();
		case 2:
			DeleteGroup();
			FirstMenu();
		case 3:
			PrintGroup();
			FirstMenu();
		case 4:
			FirstMenu();
		}
	case 3:
		switch (smenu)
		{
		case 1:
			AddStudent();
			FirstMenu();
		case 2:
			PrintStudent();
			FirstMenu();
		case 3:
			DeleteStudent();
			FirstMenu();
		case 4:
			ExcellentPupilOfGroup();
			FirstMenu();
		case 5:
			Losers();
			FirstMenu();
		case 6:
			t = AverageGradeOfGroup();
			if (t)
				std::cout << "Average grade of group is " << t << std::endl;
			_getch();
			system("cls");
			FirstMenu();
		case 7:
			FirstMenu();
		}
	}
};
void ListOfGroups()
{
	std::cout << "____Groups____" << std::endl;
	Group* p = start;
	if (p)
		while (p)
		{
			std::cout << p->number << std::endl;
			p = p->next;
		}
	else
		std::cout << "No groups" << std::endl;
};
void ListOfStudents(Group* p)
{
	Student* t = p->stud;
	std::cout << "____Group " << N << "____" << std::endl;
	while (t && t->prev != p->last)
	{
		std::cout << t->name << std::endl;
		t = t->next;
	}
};
int MenuGroup()
{
	system("cls");
	gmenu = 1;
	stop = amount + 1;
	SetConsoleCursorPosition(h, m);
	Group* p = start;
	if (p)
	{
		std::cout << "____Groups____" << std::endl;
		while (p)
		{
			std::cout << "   " << p->number << std::endl;
			p = p->next;
		}
		std::cout << "   Back";
	}
	else
	{
		std::cout << "Error! No group!";
		_getch();
		system("cls");
		gmenu = amount + 1;
		return gmenu;
	}
	gmenu = Point();
	system("cls");
	return gmenu;
};
Group* SearchGroupAuto()
{
	int menu = MenuGroup();
	if (menu == (amount + 1))
		SecondMenu();
	else
	{
		Group* p = start;
		while (menu - 1)
		{
			p = p->next;
			menu--;
		}
		N = p->number;
		fordel = p;
		return p;
	}
};
int MenuStudent(Group* p)
{
	stmenu = 1;
	SetConsoleCursorPosition(h, m);
	stop = p->count + 1;
	Student* t = p->stud;
	std::cout << "____Group " << N << "____" << std::endl;
	while (t && t->prev != p->last)
	{
		std::cout << "   " << t->name << std::endl;
		t = t->next;
	}
	std::cout << "   Back";
	stmenu = Point();
	system("cls");
	return stmenu;
};
Student* SearchStudentAuto(Group* p)
{
	int menu = MenuStudent(p);
	Student* t = p->stud;
	if (menu == (p->count + 1))
		t = NULL;
	else
		while (menu - 1)
		{
			t = t->next;
			menu--;
		}
	return t;
};