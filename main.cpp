#include "Lib.h"

char point[] = "->";
int amount = 0, N, fmenu, smenu, stop, gmenu, stmenu, dbmenu, filemenu;
COORD m = { 0, 0 }; //��������� ����
COORD c = { 0, 1 }; //��������� �������
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
Group* start = NULL; //������ ����� ������
Group* finish = NULL; //����� ������
Group* fordel = NULL; //������, ��� ���������� ������� ��������
void main()
{
	FirstMenu();
};