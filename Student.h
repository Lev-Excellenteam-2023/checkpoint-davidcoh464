#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Num_Of_Grades 10

typedef struct Student 
{
	int _grades[Num_Of_Grades];
	char* _first_name;
	char* _last_name;
	int _phone;
}Student;

Student create_student(const char* first_name, const char* last_name, int phone, int grades[]);
void destroy_student(Student student);