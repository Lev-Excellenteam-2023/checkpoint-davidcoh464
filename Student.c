#include "Student.h"
#define _CRT_SECURE_NO_WARNINGS

Student create_student(const char* first_name, const char* last_name, int phone, int grades[]) 
{
    Student new_student;

    // Copy grades
    for (int i = 0; i < Num_Of_Grades; i++) {
        new_student._grades[i] = grades[i];
    }

    // Allocate memory for first name and last name and copy the provided strings
    new_student._first_name = (char*)malloc(strlen(first_name) + 1);
    new_student._last_name = (char*)malloc(strlen(last_name) + 1);

    if (new_student._first_name == NULL || new_student._last_name == NULL) {
        printf("Memory allocation failed for name.\n");
        free(new_student._first_name); // Free any previously allocated memory
        free(new_student._last_name);  // Free any previously allocated memory
        new_student._first_name = NULL; // Set to NULL to avoid issues with dangling pointers
        new_student._last_name = NULL;  // Set to NULL to avoid issues with dangling pointers
    }
    else {
        strcpy(new_student._first_name, first_name);
        strcpy(new_student._last_name, last_name);
    }
    new_student._phone = phone;
    return new_student;
}

void destroy_student(Student student) {
    free(student._first_name);
    free(student._last_name);
}
