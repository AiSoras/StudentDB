#ifndef STRUCT_H
#define STRUCT_H
struct Student //Структура студента
{
	std::string name;
	int number;
	std::string dateofbirth;
	std::string phone;
	int grade[AMOUNTofGRADES];
	Student* next;
	Student* prev;
	double averg = 0;
};
struct Group //Структура группы
{
	int number;
	int count = 0;
	Group(int count)
	{
		number = count;
		averg = 0;
		stud = NULL;
		last = NULL;
	}
	Group* next;
	Group* prev;
	Student* stud; //Начало списка студентов
	Student* last;
	double averg;
};
#endif