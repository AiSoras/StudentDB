#include "Lib.h"

void ShowAllGroups() //Показывает номера всех созданных групп, где в скобках указано количество студентов в группе. Также указано общее число студентов в потоке
{
	if (start)
	{
		int all = 0;
		Group* p = start;
		std::cout << "Groups: " << std::endl;
		while (p)
		{
			all += p->count;
			std::cout << p->number << " ( " << p->count << " )" << std::endl;;
			p = p->next;
		}
		std::cout << "All students in DataBase: " << all << std::endl;
		std::cout << "Success! The task is completed!" << std::endl;
	}
	else
		std::cout << "Error! Database is empty!" << std::endl;
	_getch();
	system("cls");
};
double AverageGrade() //Вычисляет среднее арифметическое потока
{
	double aver = 0;
	if (start)
	{
		if (!start->stud && start->next == NULL)
		{
			std::cout << "Error! Database is empty!" << std::endl;
		}
		else
		{
			Group* p = start;
			while (p)
			{
				aver += p->averg;
				p = p->next;
			}
			aver = aver / amount;
			if (smenu == 1)
			{
				std::string type, date, time;
				type = "AG ";
				date = __DATE__;
				date += " ";
				time = __TIME__;
				type += date;
				type += time;
				std::string fdate = type + ".txt";
				std::ofstream fout(fdate.c_str());
				fout << "THe average grade of feed: ";
				fout << "\n" << aver;
				fout.close();
				std::cout << "Success! The file is created! Name is " << type << ".\n";
			}
		}
	}
	else
		std::cout << "Error! Database is empty!" << std::endl;
	return aver;
};
void ExcellentPupil() //Выводит отличников всего потока
{
	if (start)
	{
		if (!start->stud && start->next == NULL)
		{
			std::cout << "Error! Database is empty!" << std::endl;
		}
		else
		{
			std::ofstream fout;
			std::string type, date, time;
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
						if (!beta)
						{
							type = "EP ";
							date = __DATE__;
							date += " ";
							time = __TIME__;
							type += date;
							type += time;
							std::string fdate = type + ".txt";
							fout.open(fdate.c_str());
							fout << "Excellent pupil of feed: ";
						}
						beta = true;
						fout << std::endl;
						std::cout << std::endl;
						fout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
						std::cout << "Name: " << tmp->name << std::endl << "Student ID: " << tmp->number << std::endl << "Date of birth: " << tmp->dateofbirth << std::endl << "Phone: " << tmp->phone << std::endl << "Grades: ";
						for (int i = 0; i < AMOUNTofGRADES; i++)
						{
							std::cout << tmp->grade[i] << " ";
							fout << tmp->grade[i] << " ";
						}
						std::cout << std::endl;
						fout << std::endl;
					}
					C--;
					tmp = tmp->next;
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