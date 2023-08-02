#include"School.h"


School* createSchool()
{
	School* newSchool = (School*)malloc(sizeof(School));
    if (newSchool == NULL)
    {
        printf("Memory allocation failed for School.\n");
        return NULL;
    }

	for (int i = 0; i < Num_Of_Level; ++i)
	{
		for (int j = 0; j < Num_Of_Class; ++j)
		{
			newSchool->students[i][j] = NULL;
		}
        newSchool->numOfStudents[i] = 0;
        for (int k = 0; k < Num_Of_Grades; ++k)
        {
            newSchool->sumOfGrades[i][k] = 0;
        }
	}
	return newSchool;
}


void addStudent(School* school, int level, int cls, Student st)
{
    --cls;
    --level;
    if (level >= Num_Of_Level || level < 0 || cls >= Num_Of_Class || cls < 0)
    {
        printf("Error\n");
        return;
    }
    school->numOfStudents[level]++;
    for (int i = 0; i < Num_Of_Grades; ++i)
    {
        school->sumOfGrades[level][i] += st._grades[i];
    }

    if (school->students[level][cls] == NULL)
    {
        school->students[level][cls] = createStudentNode(st);
        return;
    }
    StudentNode* head = school->students[level][cls];
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = createStudentNode(st);
}

void printSchoolData(School* school)
{
    for (int i = 0; i < Num_Of_Level; ++i)
    {
        for (int j = 0; j < Num_Of_Class; ++j)
        {
            StudentNode* head = school->students[i][j];
            while (head != NULL)
            {
                printf("Level: %d, Class: %d, ", i + 1, j + 1);
                print_student(&(head->data));
                head = head->next;
            }
        }
    }
}

void removeStudentGradeAndPrint(School* school, Student* st, int level, int cls)
{
    printf("Delete student in Level: %d, Class: %d, ", level + 1, cls + 1);
    print_student(st);
    school->numOfStudents[level]--;
    for (int course = 0; course < Num_Of_Grades; ++course)
    {
        school->sumOfGrades[level][course] -= st->_grades[course];
    }
}

void deleteStudentByPhone(School* school, const char* phone)
{
    for (int i = 0; i < Num_Of_Level; ++i)
    {
        for (int j = 0; j < Num_Of_Class; ++j)
        {
            StudentNode* head = school->students[i][j];
            if (head != NULL && strcmp(head->data._phone, phone) == 0)
            {
                removeStudentGradeAndPrint(school, &head->data, i, j);
                school->students[i][j] = head->next;
                destroyStudentNode(head);
                return;
            }
            while (head != NULL && head->next != NULL)
            {
                if (strcmp(phone, head->next->data._phone) == 0)
                {
                    removeStudentGradeAndPrint(school, &head->next->data, i, j);
                    StudentNode* next = head->next->next;
                    destroyStudentNode(head->next);
                    head->next = next;
                    return;
                }
                head = head->next;
            }
        }
    }
    printf("Phone not found.\n");
}

Student* searchStudentByPhone(School* school, const char* phone, int* level, int* cls)
{
    for (int i = 0; i < Num_Of_Level; ++i)
    {
        for (int j = 0; j < Num_Of_Class; ++j)
        {
            StudentNode* current = school->students[i][j];
            while (current != NULL)
            {
                if (strcmp(phone, current->data._phone) == 0)
                {
                    if (level != NULL)
                        *level = i + 1;
                    if (cls != NULL)
                        *cls = j + 1;
                    return &(current->data);
                }
                current = current->next;
            }
        }
    }
    return NULL;
}

void destroySchool(School* school)
{
    if (school == NULL)
        return;

    // Free the memory for each StudentNode in the two-dimensional array
    for (int i = 0; i < Num_Of_Level; ++i)
    {
        for (int j = 0; j < Num_Of_Class; ++j)
        {
            StudentNode* current = school->students[i][j];
            while (current != NULL)
            {
                StudentNode* next = current->next;
                destroyStudentNode(current); // Call the destructor for each StudentNode
                current = next;
            }
        }
    }
    // Finally, free the memory for the School itself
    free(school);
}

void printTop10(School* school, int level, int course)
{
    --level;
    if (level >= Num_Of_Level || level < 0 || course < 0 || course >= Num_Of_Grades)
    {
        printf("Error\n");
        return;
    }

    int topGrades[10]; // Array to store the top 10 grades
    for (int i = 0; i < 10; ++i)
    {
        topGrades[i] = 0;
    }

    Student* topStudents[10]; // Array to store pointers to the top 10 students
    for (int i = 0; i < 10; ++i)
    {
        topStudents[i] = NULL;
    }

    for (int cls = 0; cls < Num_Of_Class; ++cls)
    {
        StudentNode* current = school->students[level][cls];
        while (current != NULL)
        {
            int studentGrade = current->data._grades[course];

            // Compare with the top 10 grades
            for (int i = 0; i < 10; ++i)
            {
                if (studentGrade > topGrades[i])
                {
                    // Shift the lower grades down the list
                    for (int j = 9; j > i; --j)
                    {
                        topGrades[j] = topGrades[j - 1];
                        topStudents[j] = topStudents[j - 1];
                    }

                    // Insert the new top grade and student
                    topGrades[i] = studentGrade;
                    topStudents[i] = &(current->data);
                    break;
                }
            }

            current = current->next;
        }
    }

    printf("Top 10 Students in Level %d and Course %d:\n", level + 1, course);
    for (int i = 0; i < 10; ++i)
    {
        if (topStudents[i] != NULL)
        {
            print_student(topStudents[i]);
        }
    }
}

double getAverage(School* school, int level, int course)
{
    --level;
    if (level < 0 || level >= Num_Of_Level || course < 0 || course >= Num_Of_Grades)
    {
        printf("Error invalid input.\n");
        return -1.0;
    }
    if (school->numOfStudents[level] == 0)
    {
        printf("There are no students in level %d.\n", level + 1);
        return -1.0;
    }
    return (double)school->sumOfGrades[level][course] / school->numOfStudents[level];
}

double getLevelAverage(School* school, int level)
{
    double avg = 0.0;
    for (int course = 0; course < Num_Of_Grades; ++course)
    {
        avg += getAverage(school, level, course);
    }
    return avg / Num_Of_Grades;
}

void printUnderperformedStudents(School* school, int under_by)
{
    for (int level = 0; level < Num_Of_Level; ++level)
    {
        double min_avg = getLevelAverage(school, level + 1) - under_by;
        for (int cls = 0; cls < Num_Of_Class; ++cls)
        {
            StudentNode* head = school->students[level][cls];
            while (head != NULL)
            {
                double avgStudent = 0.0;
                for (int course = 0; course < Num_Of_Grades; ++course) 
                {
                    avgStudent += head->data._grades[course];
                }
                avgStudent /= Num_Of_Grades;
                if (avgStudent < min_avg)
                {
                    printf("Level: %d, Class: %d, ", level + 1, cls + 1);
                    print_student(&(head->data));
                }
                head = head->next;
            }
        }
    }
}

void exportDatabase(School* school, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int level = 0; level < Num_Of_Level; ++level)
    {
        for (int cls = 0; cls < Num_Of_Class; ++cls)
        {
            StudentNode* head = school->students[level][cls];
            while (head != NULL)
            {
                fprintf(file, "%s %s %s ", head->data._first_name, head->data._last_name, head->data._phone);
                fprintf(file, "%d %d", level + 1, cls + 1);
                for (int course = 0; course < Num_Of_Grades; ++course)
                {
                    fprintf(file, " %d", head->data._grades[course]);
                }
                fprintf(file, "\n");
                head = head->next;
            }
        }
    }

    fclose(file);
}
