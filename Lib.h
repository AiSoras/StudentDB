#ifndef LIB_H
#define LIB_H
#define AMOUNTofGRADES 7
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include "structs.h"
#include "StudentFunc.h"
#include "FeedFunc.h"
#include "GroupFunc.h"
#include "menu.h"
#include "Database.h"
extern char point[];
extern int amount, N, fmenu, smenu, stop, gmenu, stmenu, dbmenu, filemenu;
extern COORD m; //��������� ����
extern COORD c; //��������� �������
extern HANDLE h;
extern Group* start; //������ ����� ������
extern Group* finish; //����� ������
extern Group* fordel; //������, ��� ���������� ������� ��������
#endif