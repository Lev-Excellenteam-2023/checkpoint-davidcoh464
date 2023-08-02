#include "Student.h"

Student create_student(const char* first_name, const char* last_name, const char* phone, int grades[])
{
    Student new_student;

    // Copy grades
    for (int i = 0; i < Num_Of_Grades; i++) {
        new_student._grades[i] = grades[i];
    }

    // Allocate memory for first name and last name and copy the provided strings
    new_student._first_name = (char*)malloc(strlen(first_name) + 1);
    new_student._last_name = (char*)malloc(strlen(last_name) + 1);

    if (new_student._first_name == NULL || new_student._last_name == NULL)
    {
        printf("Memory allocation failed for name.\n");
        free(new_student._first_name);
        free(new_student._last_name);
        new_student._first_name = NULL;
        new_student._last_name = NULL;
    }
    else
    {
        strcpy(new_student._first_name, first_name);
        strcpy(new_student._last_name, last_name);
    }
    strcpy(new_student._phone, phone);
    return new_student;
}

void print_student(const Student* student)
{
    if (student == NULL)
    {
        printf("Student pointer is NULL.\n");
        return;
    }

    printf("First Name: %s, ", student->_first_name);
    printf("Last Name: %s, ", student->_last_name);
    printf("Phone: %s, ", student->_phone);

    printf("Grades: ");
    for (int i = 0; i < Num_Of_Grades; i++)
    {
        printf("%d, ", student->_grades[i]);
    }
    printf("\n");
}

void destroy_student(Student student) 
{
    free(student._first_name);
    free(student._last_name);
}
