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

void printData(School* school)
{
    for (int i = 0; i < Num_Of_Level; ++i)
    {
        for (int j = 0; j < Num_Of_Class; ++j)
        {
            StudentNode* head = school->students[i][j];
            while (head != NULL)
            {
                print_student(&head->data);
                head = head->next;
            }
        }
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
                school->students[i][j] = head->next;
                destroyStudentNode(head);
                return;
            }
            while (head != NULL && head->next != NULL)
            {
                if (strcmp(phone, head->next->data._phone) == 0)
                {
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

Student* searchStudentByPhone(School* school, const char* phone)
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