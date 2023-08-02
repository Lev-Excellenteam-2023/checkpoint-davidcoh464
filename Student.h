/**
 * @file Student.h
 * @brief Defines a Student data structure and associated functions for student management.
 */

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * @def Num_Of_Grades
  * @brief The number of grades a student can have.
  */
#define Num_Of_Grades 10

  /**
   * @struct Student
   * @brief Represents a student with grade and personal information.
   */
typedef struct Student
{
    int _grades[Num_Of_Grades]; ///< Array of grades for the student's courses.
    char* _first_name; ///< Pointer to the student's first name.
    char* _last_name; ///< Pointer to the student's last name.
    char _phone[11]; ///< Array to store the student's phone number (including null terminator).
} Student;

/**
 * @brief Creates a new Student instance with provided information.
 * @param first_name The first name of the student.
 * @param last_name The last name of the student.
 * @param phone The phone number of the student.
 * @param grades An array of grades for the student's courses.
 * @return The created Student instance.
 */
Student create_student(const char* first_name, const char* last_name, const char* phone, int grades[]);


/**
 * @brief Prints the details of a student to the standard output.
 * @param student Pointer to the Student instance to be printed.
 */
void print_student(const Student* student);

/**
 * @brief Destroys a Student instance and frees associated memory.
 * @param student The Student instance to destroy.
 */
void destroy_student(Student student);
