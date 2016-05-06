#include "lib.h"

char point[] = "->";
int amount = 0, N, fmenu, smenu, stop, gmenu, stmenu, dbmenu, filemenu;
COORD m = { 0, 0 }; //Ïîëîæåíèå ìåíþ
COORD c = { 0, 1 }; //Ïîëîæåíèå ñòðåëêè
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
Group* start = NULL; //Íà÷àëî âñåãî ïîòîêà
Group* finish = NULL; //Êîíåö ïîòîêà
Group* fordel = NULL; //Ãðóïïà, ãäå íåîáõîäèìî óäàëèòü ñòóäåíòà
void main()
{
	FirstMenu();
};
