#pragma once

#include "Student.h"

typedef struct StudentNode
{
    Student data;
    struct StudentNode* next;
}StudentNode;

StudentNode* createStudentNode(Student st);
void destroyStudentNode(StudentNode* node);