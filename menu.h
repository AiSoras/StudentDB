#ifndef MENU_H
#define MENU_H
int Point();
void FirstMenu();
void SecondMenu();
void ListOfGroups();
void ListOfStudents(Group*);
int MenuGroup();
Group* SearchGroupAuto();
int MenuStudent(Group*);
Student* SearchStudentAuto(Group*);
#endif