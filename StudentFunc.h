#ifndef STUDENT_H
#define STUDENT_H
bool Grades(Student*, int);
bool AverageGrade(Student*, double);
Student* CreateStudentAuto(Group*&, std::istream&);
void AddStudent();
void DeleteStudent();
void PrintStudent();
void Losers();
void ExcellentPupilOfGroup();
void HigherThanTheAverageGrade();
#endif