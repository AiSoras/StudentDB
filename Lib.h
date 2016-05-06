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
extern COORD m; //Положение меню
extern COORD c; //Положение стрелки
extern HANDLE h;
extern Group* start; //Начало всего потока
extern Group* finish; //Конец потока
extern Group* fordel; //Группа, где необходимо удалить студента
#endif