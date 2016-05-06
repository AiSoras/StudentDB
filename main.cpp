#include "Lib.h"

char point[] = "->";
int amount = 0, N, fmenu, smenu, stop, gmenu, stmenu, dbmenu, filemenu;
COORD m = { 0, 0 }; //Положение меню
COORD c = { 0, 1 }; //Положение стрелки
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
Group* start = NULL; //Начало всего потока
Group* finish = NULL; //Конец потока
Group* fordel = NULL; //Группа, где необходимо удалить студента
void main()
{
	FirstMenu();
};