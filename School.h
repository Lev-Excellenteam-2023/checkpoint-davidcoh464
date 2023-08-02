#pragma once
#include "StudentNode.h"
#include<stdbool.h>

#define Num_Of_Level 12
#define Num_Of_Class 10

typedef struct School
{
	StudentNode* students[Num_Of_Level][Num_Of_Class];
	unsigned long sumOfGrades[Num_Of_Level][Num_Of_Grades];
	unsigned long numOfStudents[Num_Of_Level];
}School;

School* createSchool();
void addStudent(School* school, int level, int cls, Student st);
Student* searchStudentByPhone(School* school, const char* phone, int *level, int *cls);
void printSchoolData(School * school);
void deleteStudentByPhone(School* school, const char* phone);
void printTop10(School* school, int level, int course);
double getAverage(School* school, int level, int course);
void destroySchool(School* school);