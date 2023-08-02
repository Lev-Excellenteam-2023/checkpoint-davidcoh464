/**
 * @file School.h
 * @brief Defines a School data structure and associated functions for managing students.
 */

#pragma once
#include "StudentNode.h"
#include <stdbool.h>

 /**
  * @def Num_Of_Level
  * @brief The number of levels in the school.
  */
#define Num_Of_Level 12

  /**
   * @def Num_Of_Class
   * @brief The number of classes in each level.
   */
#define Num_Of_Class 10

   /**
    * @struct School
    * @brief Represents a school with student information organized by levels and classes.
    */
typedef struct School
{
    StudentNode* students[Num_Of_Level][Num_Of_Class]; ///< 2D array of students organized by levels and classes.
    unsigned long sumOfGrades[Num_Of_Level][Num_Of_Grades]; ///< Total sum of grades for each level and course.
    unsigned long numOfStudents[Num_Of_Level]; ///< Number of students in each level.
} School;

/**
 * @brief Creates a new School instance and initializes its data.
 * @return A pointer to the newly created School instance.
 */
School* createSchool();

/**
 * @brief Adds a student to the School at the specified level and class.
 * @param school The School instance.
 * @param level The level at which to add the student.
 * @param cls The class at which to add the student.
 * @param st The Student to add.
 */
void addStudent(School* school, int level, int cls, Student st);

/**
 * @brief Searches for a student by phone number within the School.
 * @param school The School instance.
 * @param phone The phone number to search for.
 * @param level Output parameter for the level of the found student.
 * @param cls Output parameter for the class of the found student.
 * @return A pointer to the found Student, or NULL if not found.
 */
Student* searchStudentByPhone(School* school, const char* phone, int* level, int* cls);

/**
 * @brief Prints information about all students in the School.
 * @param school The School instance.
 */
void printSchoolData(School* school);

/**
 * @brief Deletes a student from the School by phone number.
 * @param school The School instance.
 * @param phone The phone number of the student to delete.
 */
void deleteStudentByPhone(School* school, const char* phone);

/**
 * @brief Prints the top 10 students for a specific level and course.
 * @param school The School instance.
 * @param level The level to consider.
 * @param course The course index to consider.
 */
void printTop10(School* school, int level, int course);

/**
 * @brief Calculates the average grade for a specific level and course.
 * @param school The School instance.
 * @param level The level to consider.
 * @param course The course index to consider.
 * @return The calculated average grade.
 */
double getAverage(School* school, int level, int course);

/**
 * @brief Calculates the average grade across all courses for a specific level.
 * @param school The School instance.
 * @param level The level to consider.
 * @return The calculated average grade.
 */
double getLevelAverage(School* school, int level);

/**
 * @brief Prints information about underperformed students based on a given threshold.
 * @param school The School instance.
 * @param under_by The threshold for determining underperformance.
 */
void printUnderperformedStudents(School* school, int under_by);

/**
 * @brief Exports the School database to a file.
 * @param school The School instance.
 * @param filename The name of the file to export to.
 */
void exportDatabase(School* school, const char* filename);

/**
 * @brief Destroys a School instance and frees associated memory.
 * @param school The School instance to destroy.
 */
void destroySchool(School* school);
