/**
 * @file StudentNode.h
 * @brief Defines a linked list node for Student data and associated functions for node management.
 */

#pragma once

#include "Student.h"

 /**
  * @struct StudentNode
  * @brief Represents a node in a linked list containing Student data.
  */
typedef struct StudentNode
{
    Student data; ///< The Student data stored in the node.
    struct StudentNode* next; ///< Pointer to the next node in the linked list.
} StudentNode;

/**
 * @brief Creates a new StudentNode instance with provided Student data.
 * @param st The Student data to be stored in the node.
 * @return The created StudentNode instance.
 */
StudentNode* createStudentNode(Student st);

/**
 * @brief Destroys a StudentNode instance and frees associated memory.
 * @param node The StudentNode instance to destroy.
 */
void destroyStudentNode(StudentNode* node);
