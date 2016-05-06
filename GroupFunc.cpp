#include "Lib.h"

Group* SearchGroup() //Поиск группы с определенным номером, возвращается указатель на эту группы
{
	std::cout << std::endl << "Enter number of group" << std::endl;
	std::cin >> N;
	while (!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Error! Retype! \n";
		std::cin >> N;
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
			std::cout << "Error! The group " << N << " is already created!" << std::endl;
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
			std::cout << "Success! The group is created!" << std::endl;
		}
		_getch();
		system("cls");
		std::cout << "Create one more group? Y-1/N-0" << std::endl;
		std::cin >> beta;
		while (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Error! Retype!" << std::endl;
			std::cin >> beta;
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
		std::cout << "____Group " << N << "____" << std::endl;
		int C = p->count;
		while (C)
		{
			std::cout << std::endl;
			std::cout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
			for (int i = 0; i < AMOUNTofGRADES; i++)
				std::cout << tmp->grade[i] << " ";
			tmp = tmp->next;
			std::cout << std::endl;
			--C;
		}
		std::cout << std::endl << "Success! The task is completed!" << std::endl;
	}
	else
		std::cout << "Error! The group is empty!" << std::endl;
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
	std::cout << "Success! The group is deleted!" << std::endl;
	_getch();
	system("cls");
};
double AverageGradeOfGroup() //Находит средную арифметическую оценку группы
{
	double aver = 0;
	Group* p = SearchGroupAuto();
	if (p->stud)
	{
		aver = p->averg;
		system("cls");
	}
	else
		std::cout << "Error! The group is empty! \n";
	return aver;
};