#pragma once
#include "StudentNode.h"

#define Num_Of_Level 12
#define Num_Of_Class 10

typedef struct School
{
	StudentNode* students[Num_Of_Level][Num_Of_Class];
}School;

School* createSchool();
void addStudent(School* school, int level, int cls, Student st);
Student* searchStudentByPhone(School* school, const char* phone);
void printData(School * school);
void deleteStudentByPhone(School* school, const char* phone);
void destroySchool(School* school);