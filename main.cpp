#define AMOUNTofGRADES 7
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
using namespace std;
char point[] = "->";
int amount = 0, N, fmenu, smenu, stop, gmenu, stmenu, dbmenu, filemenu;
struct Group;
struct Student;
Group* start = NULL; //Начало всего потока
Group* finish = NULL; //Конец потока
Group* fordel = NULL; //Группа, где необходимо удалить студента
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD m = { 0, 0 }; //Положение меню
COORD c = { 0, 1 }; //Положение стрелки
void SecondMenu();
void LoadDBMenu();
void ListOfGroups();
void DBMenu();
void ListOfStudents(Group* p);
Group* SearchGroupAuto();
Student* SearchStudentAuto(Group* p);
struct Student //Структура студента
{
	string name;
	int number;
	string dateofbirth;
	string phone;
	int grade[AMOUNTofGRADES];
	Student* next;
	Student* prev;
};
struct Group //Структура группы
{
	int number;
	int count = 0;
	Group(int count)
	{
		number = count;
		stud = NULL;
		last = NULL;
	}
	Group* next;
	Group* prev;
	Student* stud; //Начало списка студентов
	Student* last;
};
Group* SearchGroup() //Поиск группы с определенным номером, возвращается указатель на эту группы
{
	cout << endl << "Enter number of group" << endl;
	cin >> N;
	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Error! Retype! \n";
		cin >> N;
	}
	Group* p = start;
	while (p)
	{
		if (p->number == N)
			break;
		else
			p = p->next;
	}
	fordel = p;
	return p;
};
bool Grades(Student* tmp, int G) //Проверка, что у студента все оценки равны определенному значению (2/5), возвращает false, если нет, true - да
{
	bool alpha = true;
	for (int i = 0; i < AMOUNTofGRADES; i++)
		if (tmp->grade[i] != G)
		{
			alpha = false;
			break;
		}
	return alpha;
};
bool AverageGrade(Student* tmp, double G) //Проверяет, что у студента его среднее арифметическое всех оценок больше какого-либо числа. Если не так, то возвращает false
{
	bool alpha = true;
	int t = 0;
	for (int i = 0; i < AMOUNTofGRADES; i++)
		t += tmp->grade[i];
	t /= AMOUNTofGRADES;
	if (t <= G)
		alpha = false;
	return alpha;
};
Group* CreateGroupAuto(int F) //Создание группы в результате считывания файла, т.е. от пользователя не требуется никакого ввода в консоль
{
	Group* p = NULL;
	if (finish)
	{
		p = new Group(F);
		p->prev = finish;
		finish->next = p;
		finish = p;
		finish->next = NULL;
	}
	else
	{
		start = new Group(F);
		start->prev = start->next = NULL;
		finish = p = start;
	}
	finish->stud = NULL;
	return p;
};
Student* CreateStudentAuto(Group* &p, istream &fin) //Аналагично с CreateGroupAuto
{
	Student* tmp = NULL;
	if (p->last)
	{
		tmp = new Student;
		tmp->prev = p->last;
		p->last->next = tmp;
		p->last = tmp;
	}
	else
	{
		p->stud = new Student;
		p->stud->prev = NULL;
		p->last = p->stud;
	}
	p->last->next = NULL;
	string tname;
	fin >> p->last->name;
	fin >> tname;
	p->last->name += " ";
	p->last->name += tname;
	fin >> p->last->number;
	fin >> p->last->dateofbirth;
	fin >> p->last->phone;
	for (int i = 0; i < AMOUNTofGRADES; i++)
		fin >> p->last->grade[i];
	if (!p->stud)
		p->stud = tmp = p->last;
	return tmp;
};
void CreateGroup() //Создает группу при условии, что она еще не создана
{
	system("cls");
	int beta = 1;
	while (beta)
	{
		ListOfGroups();
		Group* p = SearchGroup();
		if (p)
		{
			cout << "Error! The group " << N << " is already created!" << endl;
		}
		else
		{
			++amount;
			if (finish)
			{
				p = new Group(N);
				p->prev = finish;
				finish->next = p;
				finish = p;
				finish->next = NULL;
			}
			else
			{
				start = new Group(N);
				start->prev = start->next = NULL;
				finish = start;
			}
			finish->stud = NULL;
			finish->count = 0;
			if (amount > 1)
			{
				Group* key, *run, *swap = NULL;
				int temp;
				key = finish;
				temp = key->number;
				run = start;
				while (temp > run->number && run->next != 0)
					run = run->next;
				if (run != key)
					swap = run;
				if (swap)
				{
					finish = finish->prev;
					finish->next = NULL;
					Group* tnext = NULL, *tprev = NULL;
					if (swap != start)
					{
						Group* t = swap->prev;
						t->next = key;
						key->prev = t;
					}
					else
					{
						key->prev = NULL;
						start = key;
					}
					key->next = swap;
					swap->prev = key;
				}
			}
			cout << "Success! The group is created!" << endl;
		}
		_getch();
		system("cls");
		cout << "Create one more group? Y-1/N-0" << endl;
		cin >> beta;
		while (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error! Retype!" << endl;
			cin >> beta;
		}
		system("cls");
	}
	system("cls");
};
void ShowAllGroups() //Показывает номера всех созданных групп, где в скобках указано количество студентов в группе. Также указано общее число студентов в потоке
{
	if (start)
	{
		int all = 0;
		Group* p = start;
		cout << "Groups: " << endl;
		while (p)
		{
			all += p->count;
			cout << p->number << " ( " << p->count << " )" << endl;;
			p = p->next;
		}
		cout << "All students in DataBase: " << all << endl;
		cout << "Success! The task is completed!" << endl;
	}
	else
		cout << "Error! Database is empty!" << endl;
	_getch();
	system("cls");
};
void Push() //Позволяет добавить студента в группу, проверяя при этом группу на существование
{
	Group* p = SearchGroupAuto();
	ListOfStudents(p);
	short int beta = 1;
	while (beta)
	{
		Student* tmp;
		p->count++;
		if (p->last)
		{
			tmp = new Student;
			tmp->prev = p->last;
			p->last->next = tmp;
			p->last = tmp;
		}
		else
		{
			p->last = new Student;
			p->last->prev = NULL;
		}
		p->last->next = NULL;
		cout << endl << "Enter name of student" << endl;
		cin.clear();
		cin.ignore();
		getline(cin, p->last->name, '\n');
		cout << "Enter student ID" << endl;
		cin >> p->last->number;
		while (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error! Retype!" << endl;
			cin >> p->last->number;
		}
		cout << "Enter date of birth" << endl;
		cin >> p->last->dateofbirth;
		cout << "Enter phone number" << endl;
		cin >> p->last->phone;
		cout << "Enter student grades (" << AMOUNTofGRADES << ")" << endl;
		for (int i = 0; i < AMOUNTofGRADES; i++)
		{
			cin >> p->last->grade[i];
			while (!cin || p->last->grade[i] < 2 || p->last->grade[i]>5)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Error! Retype! " << endl;
				cin >> p->last->grade[i];;
			}
		}
		if (!p->stud)
			p->stud = p->last;
		if (p->count > 1)
		{
			Student* key, *run, *swap = NULL;
			string temp;
			key = p->last;
			temp = key->name;
			run = p->stud;
			while (temp > run->name && run->next != 0)
				run = run->next;
			if (run != key)
				swap = run;
			if (swap)
			{
				p->last = p->last->prev;
				p->last->next = NULL;
				Student* tnext = NULL, *tprev = NULL;
				if (swap != p->stud)
				{
					Student* t = swap->prev;
					t->next = key;
					key->prev = t;
				}
				else
				{
					key->prev = NULL;
					p->stud = key;
				}
				key->next = swap;
				swap->prev = key;
			}
		}
		system("cls");
		cout << "Add one more student? Y-1/N-0\n";
		cin >> beta;
		while (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error! Retype!" << endl;
			cin >> beta;
		}
		system("cls");
	}
	system("cls");
};
void PrintGroup() //Выводит в консоль всю группу, проверяет группу на существование и заполненность
{
	Group* p = SearchGroupAuto();
	Student* tmp = p->stud;
	if (tmp)
	{
		cout << "____Group " << N << "____" << endl;
		int C = p->count;
		while (C)
		{
			cout << endl;
			cout << "Name: " << tmp->name << endl << "Student ID: " << tmp->number << endl << "Date of birth: " << tmp->dateofbirth << endl << "Phone: " << tmp->phone << endl << "Grades: ";
			for (int i = 0; i < AMOUNTofGRADES; i++)
				cout << tmp->grade[i] << " ";
			tmp = tmp->next;
			cout << endl;
			--C;
		}
		cout << endl << "Success! The task is completed!" << endl;
	}
	else
		cout << "Error! The group is empty!" << endl;
	_getch();
	system("cls");
};
void DeleteGroup() //Удаляет полностью группу, если она существует
{
	Group* p = SearchGroupAuto();
	Student* tmp = p->stud;
	while (p->stud)
	{
		tmp = p->stud;
		p->stud = tmp->next;
		delete tmp;
	}
	if (p->prev && p->next)
	{
		Group* ptemp = p->prev;
		Group* ntemp = p->next;
		ptemp->next = ntemp;
		ntemp->prev = ptemp;
	}
	else
	{
		if (p->prev && !p->next)
		{
			finish = p->prev;
			finish->next = NULL;
		}
		if (!p->prev && p->next)
		{
			start = p->next;
			start->prev = NULL;
		}
		if (!p->prev && !p->next)
			finish = start = NULL;
	}
	delete p;
	--amount;
	cout << "Success! The group is deleted!" << endl;
	_getch();
	system("cls");
};
void DeleteStudent() //Удаляет студента, если он существует
{
	Student* tmp = NULL;
	while (!tmp)
	{
		Group* p = SearchGroupAuto();
		tmp = SearchStudentAuto(p);
	}
	if (tmp->prev && tmp->next)
	{
		Student* ptemp = tmp->prev;
		Student* ntemp = tmp->next;
		ptemp->next = ntemp;
		ntemp->prev = ptemp;
	}
	if (tmp->prev && !tmp->next)
	{
		fordel->last = tmp->prev;
		fordel->last->next = NULL;
	}
	if (!tmp->prev && tmp->next)
	{
		fordel->stud = tmp->next;
		fordel->stud = tmp->next;
		fordel->stud->prev = NULL;
	}
	if (!tmp->prev && !tmp->next)
		fordel->last = fordel->stud = NULL;
	fordel->count--;
	delete tmp;
	cout << "Success! Student is deleted!";
	_getch();
	system("cls");
};
void PrintStudent() //Выводит все поля определенного студента
{
	Student* tmp = NULL;
	while (!tmp)
	{
		Group* p = SearchGroupAuto();
		tmp = SearchStudentAuto(p);
	}
	cout << endl;
	cout << "Name: " << tmp->name << endl << "Student ID: " << tmp->number << endl << "Date of birth: " << tmp->dateofbirth << endl << "Phone: " << tmp->phone << endl << "Grades: ";
	for (int i = 0; i < AMOUNTofGRADES; i++)
		cout << tmp->grade[i] << " ";
	cout << endl;
	tmp = tmp->next;
	cout << endl << "Success! The task is completed!" << endl;
	_getch();
	system("cls");
};
void Losers() //Выводит двоечников в группе
{
	Group* p = SearchGroupAuto();
	Student* tmp = p->stud;
	if (tmp)
	{
		bool beta = false;
		int C = p->count;
		while (C)
		{
			if (Grades(tmp, 2))
			{
				beta = true;
				cout << endl;
				cout << "Name: " << tmp->name << endl << "Student ID: " << tmp->number << endl << "Date of birth: " << tmp->dateofbirth << endl << "Phone: " << tmp->phone << endl << "Grades: ";
				for (int i = 0; i < AMOUNTofGRADES; i++)
					cout << tmp->grade[i] << " ";
				cout << endl;
			}
			tmp = tmp->next;
			--C;
		}
		if (beta)
			cout << "Success! The task is completed!" << endl;
		else
			cout << "No one:\\" << endl;
	}
	else
		cout << "Error! The group is empty!" << endl;
	_getch();
	system("cls");
};
void ExcellentPupilOfGroup() //Выводит отличников в группе
{
	Group* p = SearchGroupAuto();
	Student* tmp = p->stud;
	if (tmp)
	{
		bool beta = false;
		int C = p->count;
		while (C)
		{
			if (Grades(tmp, 5))
			{
				beta = true;
				cout << endl;
				cout << "Name: " << tmp->name << endl << "Student ID: " << tmp->number << endl << "Date of birth: " << tmp->dateofbirth << endl << "Phone: " << tmp->phone << endl << "Grades: ";
				for (int i = 0; i < AMOUNTofGRADES; i++)
					cout << tmp->grade[i] << " ";
				cout << endl;
			}
			tmp = tmp->next;
			--C;
		}
		if (beta)
			cout << "Success! The task is completed!" << endl;
		else
			cout << "No one:\\" << endl;
	}
	else
		cout << "Error! The group is empty!" << endl;
	_getch();
	system("cls");
};
void SaveDB() //Сохраняет всю базу данных в файл с именем, равному текущей дате
{
	string date, time;
	Group* p = start;
	Student* t;
	date = __DATE__;
	date += " ";
	time = __TIME__;
	date += time;
	string bdate = date + ".bin";
	ofstream bout(bdate.c_str(), ios::binary | ios::out);
	string fdate = date + ".txt";
	ofstream fout(fdate.c_str());
	fout << amount << endl;
	bout.write((char*)&amount, sizeof(int));
	while (p)
	{
		fout << p->number << endl;
		fout << p->count << endl;
		int C = p->count;
		bout.write((char*)p, sizeof(Group));
		t = p->stud;
		while (C)
		{
			bout.write((char*)&t->name, sizeof(t->name));
			bout.write((char*)&t->number, sizeof(int));
			bout.write((char*)&t->dateofbirth, sizeof(t->dateofbirth));
			bout.write((char*)&t->phone, sizeof(t->phone));
			bout.write((char*)&t->grade, sizeof(t->grade));
			fout << t->name << endl << t->number << endl << t->dateofbirth << endl << t->phone << endl;
			for (int i = 0; i < AMOUNTofGRADES; i++)
				fout << t->grade[i] << " ";
			fout << "\n";
			t = t->next;
			C--;
		}
		p = p->next;
	}
	fout.close();
	bout.close();
	system("cls");
	cout << "Success! DB is saved! File name is " << date << ".\n";
	_getch();
	system("cls");
};
double AverageGradeOfGroup() //Находит средную арифметическую оценку группы
{
	double aver = 0;
	Group* p = SearchGroupAuto();
	if (p->stud)
	{
		Student* tmp;
		tmp = p->stud;
		int C = p->count;
		while (tmp)
		{
			for (int i = 0; i < AMOUNTofGRADES; i++)
				aver += tmp->grade[i];
			tmp = tmp->next;
		}
		aver /= C*AMOUNTofGRADES;
		system("cls");
	}
	else
		cout << "Error! The group is empty! \n";
	return aver;
};
double AverageGrade() //Вычисляет среднее арифметическое потока
{
	double aver = 0;
	if (start)
	{
		if (!start->stud && start->next == NULL)
		{
			cout << "Error! Database is empty!" << endl;
		}
		else
		{
			int C, all = 0;
			Group* p = start;
			Student* t;
			while (p)
			{
				t = p->stud;
				C = p->count;
				all += C;
				while (C)
				{
					for (int i = 0; i < AMOUNTofGRADES; i++)
						aver += t->grade[i];
					t = t->next;
					C--;
				}
				p = p->next;
			}
			aver = aver / (AMOUNTofGRADES*all);
		}
	}
	else
		cout << "Error! Database is empty!" << endl;
	return aver;
};
void ExcellentPupil() //Выводит отличников всего потока
{
	if (start)
	{
		if (!start->stud && start->next == NULL)
		{
			cout << "Error! Database is empty!" << endl;
		}
		else
		{
			bool beta = false;
			int C;
			Group* p = start;
			while (p)
			{
				Student* tmp;
				tmp = p->stud;
				C = p->count;
				while (C)
				{
					if (Grades(tmp, 5))
					{
						beta = true;
						cout << endl;
						cout << "Name: " << tmp->name << endl << "Student ID: " << tmp->number << endl << "Date of birth: " << tmp->dateofbirth << endl << "Phone: " << tmp->phone << endl << "Grades: ";
						for (int i = 0; i < AMOUNTofGRADES; i++)
							cout << tmp->grade[i] << " ";
						cout << endl;
					}
					C--;
					tmp = tmp->next;
				}
				p = p->next;
			}
			if (beta)
				cout << "Success! The task is completed!" << endl;
			else
				cout << "No one:\\" << endl;
		}
	}
	else
		cout << "Error! Database is empty!" << endl;
	_getch();
	system("cls");
};
void HigherThanTheAverageGrade() //Выводит студентов, у которых средних балл выше среднего балла потока
{
	if (start)
	{
		if (!start->stud && start->next == NULL)
		{
			cout << "Error! Database is empty!" << endl;
		}
		else
		{
			bool beta = false;
			int C;
			Group* p = start;
			double aver = AverageGrade();
			while (p)
			{
				Student* tmp;
				tmp = p->stud;
				C = p->count;
				while (C)
				{
					if (AverageGrade(tmp, aver))
					{
						beta = true;
						cout << endl;
						cout << "Name: " << tmp->name << endl << "Student ID: " << tmp->number << endl << "Date of birth: " << tmp->dateofbirth << endl << "Phone: " << tmp->phone << endl << "Grades: ";
						for (int i = 0; i < AMOUNTofGRADES; i++)
							cout << tmp->grade[i] << " ";
						cout << endl;
					}
					tmp = tmp->next;
					C--;
				}
				p = p->next;
			}
			if (beta)
				cout << "Success! The task is completed!" << endl;
			else
				cout << "No one:\\" << endl;
		}
	}
	else
		cout << "Error! Database is empty!" << endl;
	_getch();
	system("cls");
};
int Point() //Отвечает за '->'
{
	c.Y = 1;
	int menu = 1;
	COORD temp = { 0, 0 };
	while (1)
	{
		SetConsoleCursorPosition(h, c);
		cout << "  ";
		SetConsoleCursorPosition(h, c);
		cout << point;
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
		cout << "  ";
		SetConsoleCursorPosition(h, c);
		cout << point;
	}
};
void FirstMenu() //Первый уровень меню
{
	system("cls");
	fmenu = 1;
	stop = 5;
	SetConsoleCursorPosition(h, m);
	cout << "____Menu____"
		<< "\n   Feed"
		<< "\n   Group"
		<< "\n   Student"
		<< "\n   DataBase"
		<< "\n   Exit";
	fmenu = Point();
	system("cls");
	cout << point;
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
		cout << "____Feed____"
			<< "\n   Print an average grade"
			<< "\n   Print students if they aver. grade > an aver. grade of feed"
			<< "\n   Print excellet pupil"
			<< "\n   Show all groups"
			<< "\n   Back";
		break;
	case 2:
		stop = 4;
		cout << "____Group____"
			<< "\n   Add"
			<< "\n   Delete"
			<< "\n   Print"
			<< "\n   Back";
		break;
	case 3:
		stop = 7;
		cout << "____Student____"
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
				cout << "The average grade is " << t << endl;
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
			Push();
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
				cout << "Average grade of group is " << t << endl;
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
	cout << "____Groups____" << endl;
	Group* p = start;
	if (p)
		while (p)
		{
			cout << p->number << endl;
			p = p->next;
		}
	else
		cout << "No groups" << endl;
};
void ListOfStudents(Group* p)
{
	Student* t = p->stud;
	cout << "____Group " << N << "____" << endl;
	while (t && t->prev != p->last)
	{
		cout << t->name << endl;
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
		cout << "____Groups____" << endl;
		while (p)
		{
			cout << "   " << p->number << endl;
			p = p->next;
		}
		cout << "   Back";
	}
	else
	{
		cout << "Error! No group!";
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
	cout << "____Group " << N << "____" << endl;
	while (t && t->prev != p->last)
	{
		cout << "   " << t->name << endl;
		t = t->next;
	}
	cout << "   Back";
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
void LoadDBMenu()
{
	string date;
	WIN32_FIND_DATA f;
	HANDLE file;
	ifstream bin, fin;
	filemenu = 1;
	int amountoffiles = 0;
	stop = 3;
	SetConsoleCursorPosition(h, m);
	cout << "____Load DataBase____\n"
		<< "   File (.txt)\n"
		<< "   Binary file (.bin)\n"
		<< "   Back";
	int menu = Point();
	if (menu != 3)
	{
		system("cls");
		SetConsoleCursorPosition(h, m);
		switch (menu)
		{
		case 1:
			cout << "____Files____" << endl;
			file = FindFirstFile("./*.txt", &f);
			if (file != INVALID_HANDLE_VALUE)
			{
				do
				{
					amountoffiles++;
					cout << "   " << f.cFileName << endl;
				} while (FindNextFile(file, &f));
				cout << "   Back";
			}
			break;
		case 2:
			cout << "____Files____" << endl;
			file = FindFirstFile("./*.bin", &f);
			if (file != INVALID_HANDLE_VALUE)
			{
				do
				{
					amountoffiles++;
					cout << "   " << f.cFileName << endl;
				} while (FindNextFile(file, &f));
				cout << "   Back";
			}
			break;
		}
		stop = amountoffiles + 1;
		filemenu = Point();
		system("cls");
		if (filemenu == amountoffiles + 1)
			LoadDBMenu();
		switch (menu)
		{
		case 1:
			file = FindFirstFile("./*.txt", &f);
			if (file != INVALID_HANDLE_VALUE)
			{
				for (int i = 1; i < filemenu; i++)
					FindNextFile(file, &f);
				date = f.cFileName;
			}
			fin.open(date.c_str());
			fin >> amount;
			int C;
			for (int i = 0; i < amount; i++)
			{
				fin >> C;
				Group* p = CreateGroupAuto(C);
				fin >> p->count;
				for (int j = 0; j < p->count; j++)
					CreateStudentAuto(p, fin);
			}
			fin.close();
			break;
		case 2:
			file = FindFirstFile("./*.bin", &f);
			if (file != INVALID_HANDLE_VALUE)
			{
				for (int i = 1; i < filemenu; i++)
					FindNextFile(file, &f);
				date = f.cFileName;
			}
			bin.open(date.c_str(), ios::binary | ios::in);
			bin.read((char*)&amount, sizeof(int));
			Group* p = NULL;
			Student* t = NULL;
			Student* trash = NULL;
			for (int i = 0; i < amount; i++)
			{
				Group* tmp = p;
				p = new Group(000);
				if (i == 0)
				{
					bin.read((char*)p, sizeof(Group));
					start = p;
					start->prev = NULL;
				}
				else
				{
					bin.read((char*)p, sizeof(Group));
					p->prev = tmp;
					tmp->next = p;
				}
				finish = p;
				finish->next = NULL;
				for (int j = 0; j < p->count; j++)
				{
					Student* s = trash;
					trash = new Student;
					t = new Student;
					bin.read((char*)&t->name, sizeof(t->name));
					bin.read((char*)&t->number, sizeof(int));
					bin.read((char*)&t->dateofbirth, sizeof(t->dateofbirth));
					bin.read((char*)&t->phone, sizeof(t->phone));
					bin.read((char*)&t->grade, sizeof(t->grade));
					trash->name = t->name;
					trash->number = t->number;
					trash->dateofbirth = t->dateofbirth;
					trash->phone = t->phone;
					for (int m = 0; m < AMOUNTofGRADES; m++)
						trash->grade[m] = t->grade[m];
					if (j == 0)
					{
						p->stud = trash;
						trash->prev = NULL;
					}
					else
					{
						trash->prev = s;
						s->next = trash;
					}
					p->last = trash;
					trash->next = NULL;
				}
			}
			bin.close();
			break;
		}
		cout << "Success! DB is loaded!" << endl;
		_getch();
		system("cls");
		FirstMenu();
	}
	else
		DBMenu();
};
void DBMenu()
{
	system("cls");
	dbmenu = 1;
	stop = 3;
	SetConsoleCursorPosition(h, m);
	cout << "____DataBase____"
		<< "\n   Load"
		<< "\n   Save"
		<< "\n   Back";
	dbmenu = Point();
	system("cls");
	cout << point;
	switch (dbmenu)
	{
	case 1:
		LoadDBMenu();
	case 2:
		SaveDB();
		FirstMenu();
	case 3:
		FirstMenu();
	}
};
void main()
{
	FirstMenu();
};
