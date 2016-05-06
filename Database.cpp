#include "Lib.h"

void SaveDB() //Ñîõðàíÿåò âñþ áàçó äàííûõ â ôàéë ñ èìåíåì, ðàâíîìó òåêóùåé äàòå
{
	std::string date, time, type;
	Group* p = start;
	Student* t;
	type = "DB ";
	date = __DATE__;
	date += " ";
	time = __TIME__;
	type += date;
	type += time;
	std::string bdate = type + ".bin";
	std::ofstream bout(bdate.c_str(), std::ios::binary | std::ios::out);
	std::string fdate = type + ".txt";
	std::ofstream fout(fdate.c_str());
	fout << amount << std::endl;
	bout.write((char*)&amount, sizeof(int));
	while (p)
	{
		fout << p->number << std::endl;
		fout << p->count << std::endl;
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
			fout << t->name << std::endl << t->number << std::endl << t->dateofbirth << std::endl << t->phone << std::endl;
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
	std::cout << "Success! The DB is saved! File name is " << type << ".\n";
	_getch();
	system("cls");
};
void LoadDBMenu()
{
	std::string date;
	WIN32_FIND_DATA f;
	HANDLE file;
	std::ifstream bin, fin;
	filemenu = 1;
	int amountoffiles = 0;
	stop = 3;
	SetConsoleCursorPosition(h, m);
	std::cout << "____Load DataBase____\n"
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
			file = FindFirstFile("./DB*.txt", &f);
			if (file != INVALID_HANDLE_VALUE)
			{
				std::cout << "____Files____" << std::endl;
				do
				{
					amountoffiles++;
					std::cout << "   " << f.cFileName << std::endl;
				} while (FindNextFile(file, &f));
				std::cout << "   Back";
			}
			else
			{
				std::cout << "No files\n";
				_getch();
			}
			break;
		case 2:
			file = FindFirstFile("./DB*.bin", &f);
			if (file != INVALID_HANDLE_VALUE)
			{
				std::cout << "____Files____" << std::endl;
				do
				{
					amountoffiles++;
					std::cout << "   " << f.cFileName << std::endl;
				} while (FindNextFile(file, &f));
				std::cout << "   Back";
			}
			else
			{
				std::cout << "No files\n";
				_getch();
			}
			break;
		}
		if (amountoffiles)
		{
			stop = amountoffiles + 1;
			filemenu = Point();
		}
		else
			LoadDBMenu();
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
			bin.open(date.c_str(), std::ios::binary | std::ios::in);
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
		std::cout << "Success! DB is loaded!" << std::endl;
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
	std::cout << "____DataBase____"
		<< "\n   Load"
		<< "\n   Save"
		<< "\n   Back";
	dbmenu = Point();
	system("cls");
	std::cout << point;
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
