#include "lib.h"

bool Grades(Student* tmp, int G) //Ïðîâåðêà, ÷òî ó ñòóäåíòà âñå îöåíêè ðàâíû îïðåäåëåííîìó çíà÷åíèþ (2/5), âîçâðàùàåò false, åñëè íåò, true - äà
{                       // Îòäåëüíÿ ôóíêöèÿ, ò.ê. äëÿ áîëüøîãî êîëè÷åñòâà îöåíîê îêðóãëåíèå ñðåäíåãî çíà÷åíèÿ ìîæåò ïðèâåñòè ê íåòî÷íîñòè
	bool alpha = true;
	for (int i = 0; i < AMOUNTofGRADES; i++)
		if (tmp->grade[i] != G)
		{
			alpha = false;
			break;
		}
	return alpha;
};
bool AverageGrade(Student* tmp, double G) //Ïðîâåðÿåò, ÷òî ó ñòóäåíòà åãî ñðåäíåå àðèôìåòè÷åñêîå âñåõ îöåíîê áîëüøå êàêîãî-ëèáî ÷èñëà. Åñëè íå òàê, òî âîçâðàùàåò false
{
	bool alpha = true;
	if (tmp->averg <= G)
		alpha = false;
	return alpha;
};
Student* CreateStudentAuto(Group* &p, std::istream &fin) //Àíàëàãè÷íî ñ CreateGroupAuto
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
	int sum = 0;
	p->last->next = NULL;
	std::string tname;
	fin >> p->last->name;
	fin >> tname;
	p->last->name += " ";
	p->last->name += tname;
	fin >> p->last->number;
	fin >> p->last->dateofbirth;
	fin >> p->last->phone;
	for (int i = 0; i < AMOUNTofGRADES; i++)
	{
		fin >> p->last->grade[i];
		sum += p->last->grade[i];
	}
	p->last->averg = sum / AMOUNTofGRADES;
	p->last->averg = round(p->last->averg * 100) / 100;
	p->averg *= (p->count - 1);
	p->averg += p->last->averg;
	p->averg /= p->count;
	if (!p->stud)
		p->stud = tmp = p->last;
	return tmp;
};
void AddStudent() //Ïîçâîëÿåò äîáàâèòü ñòóäåíòà â ãðóïïó, ïðîâåðÿÿ ïðè ýòîì ãðóïïó íà ñóùåñòâîâàíèå
{
	Group* p = SearchGroupAuto();
	ListOfStudents(p);
	short int beta = 1;
	std::cout << std::endl;
	while (beta)
	{
		int sum = 0;
		bool alpha = true;
		Student* tmp = new Student;
		std::cout << "Group " << p->number << std::endl;
		std::cout << "Enter name of student" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		std::getline(std::cin, tmp->name, '\n');
		std::cout << "Enter student ID" << std::endl;
		std::cin >> tmp->number;
		while (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Error! Retype!" << std::endl;
			std::cin >> p->last->number;
		}
		std::cout << "Enter date of birth" << std::endl;
		std::cin >> tmp->dateofbirth;
		std::cout << "Enter phone number" << std::endl;
		std::cin >> tmp->phone;
		std::cout << "Enter student grades (" << AMOUNTofGRADES << ")" << std::endl;
		for (int i = 0; i < AMOUNTofGRADES; i++)
		{
			std::cin >> tmp->grade[i];
			while (!std::cin || tmp->grade[i] < 2 || tmp->grade[i]>5)
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Error! Retype! " << std::endl;
				std::cin >> tmp->grade[i];;
			}
			sum += tmp->grade[i];
		}
		tmp->averg = sum / AMOUNTofGRADES;
		tmp->averg = round(tmp->averg * 100) / 100;
		Student* trash = p->stud; 
		while (trash)
		{
			if (tmp->number == trash->number)
			{
				alpha = false;
				break;
			}
			trash = trash->next;
		}
		if (alpha)
		{
			p->count++;
			if (p->last)
			{
				tmp->prev = p->last;
				p->last->next = tmp;
				p->last = tmp;
			}
			else
			{
				p->last = tmp;
				p->last->prev = NULL;
			}
			p->last->next = NULL;
			p->averg *= (p->count-1);
			p->averg += tmp->averg;
			p->averg /= p->count;
			if (!p->stud)
				p->stud = p->last;
			if (p->count > 1)
			{
				Student* key, *run, *swap = NULL;
				std::string temp;
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
		}
		else
		{
			std::cout << "Error! Student with this student ID is already added!\n";
			delete tmp;
			_getch();
		}
		system("cls");
		std::cout << "Add one more student? Y-1/N-0\n";
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
void DeleteStudent() //Óäàëÿåò ñòóäåíòà, åñëè îí ñóùåñòâóåò
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
	std::cout << "Success! Student is deleted!";
	_getch();
	system("cls");
};
void PrintStudent() //Âûâîäèò âñå ïîëÿ îïðåäåëåííîãî ñòóäåíòà
{
	Student* tmp = NULL;
	Group* p;
	while (!tmp)
	{
		p = SearchGroupAuto();
		tmp = SearchStudentAuto(p);
	}
	std::cout << "Group " << p->number << std::endl;
	std::cout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
	for (int i = 0; i < AMOUNTofGRADES; i++)
		std::cout << tmp->grade[i] << " ";
	std::cout << std::endl;
	tmp = tmp->next;
	std::cout << std::endl << "Success! The task is completed!" << std::endl;
	_getch();
	system("cls");
};
void Losers() //Âûâîäèò äâîå÷íèêîâ â ãðóïïå
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
				if (!beta)
					std::cout << "Group " << p->number;
				beta = true;
				std::cout << std::endl;
				std::cout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
				for (int i = 0; i < AMOUNTofGRADES; i++)
					std::cout << tmp->grade[i] << " ";
				std::cout << std::endl;
			}
			tmp = tmp->next;
			--C;
		}
		if (beta)
			std::cout << "Success! The task is completed!" << std::endl;
		else
			std::cout << "No one:\\" << std::endl;
	}
	else
		std::cout << "Error! The group is empty!" << std::endl;
	_getch();
	system("cls");
};
void ExcellentPupilOfGroup() //Âûâîäèò îòëè÷íèêîâ â ãðóïïå
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
				if (!beta)
					std::cout << "Group " << p->number;
				beta = true;
				std::cout << std::endl;
				std::cout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
				for (int i = 0; i < AMOUNTofGRADES; i++)
					std::cout << tmp->grade[i] << " ";
				std::cout << std::endl;
			}
			tmp = tmp->next;
			--C;
		}
		if (beta)
			std::cout << "Success! The task is completed!" << std::endl;
		else
			std::cout << "No one:\\" << std::endl;
	}
	else
		std::cout << "Error! The group is empty!" << std::endl;
	_getch();
	system("cls");
};
void HigherThanTheAverageGrade() //Âûâîäèò ñòóäåíòîâ, ó êîòîðûõ ñðåäíèõ áàëë âûøå ñðåäíåãî áàëëà ïîòîêà
{
	if (start)
	{
		if (!start->stud && start->next == NULL)
		{
			std::cout << "Error! Database is empty!" << std::endl;
		}
		else
		{
			std::string type, date, time;
			std::ofstream fout;
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
						if (!beta)
						{
							type = "HTTAG ";
							date = __DATE__;
							date += " ";
							time = __TIME__;
							type += date;
							type += time;
							std::string fdate = type + ".txt";
							fout.open(fdate.c_str());
							fout << "Student who average grade is higher than the average grade of feed: ";
						}
						beta = true;
						fout << std::endl;
						std::cout << std::endl;
						fout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
						std::cout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
						for (int i = 0; i < AMOUNTofGRADES; i++)
							std::cout << tmp->grade[i] << " ";
						std::cout << std::endl;
						fout << std::endl;
					}
					tmp = tmp->next;
					C--;
				}
				p = p->next;
			}
			if (beta)
			{
				std::cout << "Success! The task is completed!" << std::endl;
				std::cout << "Success! The file is created! Name is " << type << ".\n";
				fout.close();
			}
			else
				std::cout << "No one:\\" << std::endl;
		}
	}
	else
		std::cout << "Error! Database is empty!" << std::endl;
	_getch();
	system("cls");
};
