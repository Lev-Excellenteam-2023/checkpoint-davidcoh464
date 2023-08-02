#include"School.h"

/**
 * Displays the main menu for the school management system and handles user input.
 */
void menu();

/**
 * Reads student data from a file and creates a School structure.
 *
 * @param file_name The name of the file containing student data.
 * @return A pointer to the created School structure, or NULL if an error occurred.
 */
School* read_data_from_file(const char* file_name);

/**
 * Checks if a given string contains only digits.
 *
 * @param a The input string to check.
 * @return true if the string contains only digits, false otherwise.
 */
bool contains_only_digits(const char* a);

/**
 * Prompts the user to input details for a new student and adds the student to the school.
 *
 * @param school Pointer to the School structure.
 */
void insertNewStudent(School* school);

/**
 * Prompts the user to input a student's phone number and deletes the student with that phone number from the school.
 *
 * @param school Pointer to the School structure.
 */
void deleteStudent(School* school);

/**
 * Prompts the user to input a student's phone number and searches for the student in the school.
 *
 * @param school Pointer to the School structure.
 */
void searchStudent(School* school);

/**
 * Prompts the user to input a student's phone number, searches for the student, and allows editing their grades.
 *
 * @param school Pointer to the School structure.
 */
void editStudentGrade(School* school);

/**
 * Prints the details of all students in the school.
 *
 * @param school Pointer to the School structure.
 */
void printAllStudents(School* school);

/**
 * Prints the top N students for each course in a given school.
 *
 * @param school Pointer to the School structure.
 */
void printTopNStudentsPerCourse(School* school);

/**
 * Prints the average grade for each course in a given school.
 *
 * @param school Pointer to the School structure.
 */
void printAverage(School* school);



enum menu_inputs
{
	Insert = 0,
	Delete = 1,
	Edit = 2,
	Search = 3,
	Showall = 4,
	Top10 = 5,
	UnderperformedStudents = 6,
	Average = 7,
	Export = 8,
	Exit = 9
};


int main() 
{
	menu();
	return 0;
}

bool contains_only_digits(const char* a)
{
	for (int i = 0; a[i] != '\0'; i++) {
		if (a[i] < '0' || a[i] > '9')
			return false;
	}
	return true;
}

School* read_data_from_file(const char* file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL)
	{
		printf("Error opening the file.\n");
		return NULL;
	}
	School* school = createSchool();
	char first_name[50];
	char last_name[50];
	char phone[11];
	int cls;
	int level;
	int grade[10];
	while (fscanf(file, "%49s %49s %10s %d %d %d %d %d %d %d %d %d %d %d %d",
		first_name, last_name, phone, &level, &cls,
		&grade[0], &grade[1], &grade[2], &grade[3], &grade[4],
		&grade[5], &grade[6], &grade[7], &grade[8], &grade[9]) == 15)
	{
		addStudent(school, level, cls, create_student(first_name, last_name, phone, grade));
	}

	fclose(file);
	return school;
}

void insertNewStudent(School* school)
{
	char first_name[50];
	char last_name[50];
	char phone[11];
	int cls;
	int level;
	int grade[10];

	while (1)
	{
		printf("Enter Level: ");
		if (scanf("%d", &level) == 1 && level > 0 && level <= Num_Of_Level)
			break;
		else
		{
			printf("Invalid input. Please enter a valid level.\n");
			while (getchar() != '\n'); // Clear the input buffer
		}
	}

	while (1)
	{
		printf("Enter Class: ");
		if (scanf("%d", &cls) == 1 && cls > 0 && cls <= Num_Of_Class)
			break;
		else
		{
			printf("Invalid input. Please enter a valid class.\n");
			while (getchar() != '\n'); // Clear the input buffer
		}
	}

	printf("Enter First Name: ");
	(void)scanf("%49s", first_name);

	printf("Enter Last Name: ");
	(void)scanf("%49s", last_name);

	while (1)
	{
		printf("Enter Phone: ");
		(void)scanf("%10s", phone);
		if (contains_only_digits(phone))
		{
			if (searchStudentByPhone(school, phone, NULL, NULL) != NULL)
			{
				printf("Student alredy exist\n");
			}
			else
				break;
		}
		printf("Invalid input. Please enter a valid phone.\n");
		while (getchar() != '\n'); // Clear the input buffer
	}
	// Data validation for Grades
	printf("Enter %d Grades: ", Num_Of_Grades);
	for (int i = 0; i < Num_Of_Grades; i++)
	{
		while (1)
		{
			if (scanf("%d", &grade[i]) == 1 && grade[i] >= 0 && grade[i] <= 100)
			{
				break;
			}
			else
			{
				printf("Invalid input. Please enter a valid grade.\n");
				while (getchar() != '\n'); // Clear the input buffer
			}
		}
	}
	addStudent(school, level, cls, create_student(first_name, last_name, phone, grade));
}

void deleteStudent(School* school)
{
	char phone[11];
	while (1)
	{
		printf("Enter the student phone: ");
		(void)scanf("%10s", phone);
		if (contains_only_digits(phone) == true)
			break;
		printf("Invalid input. Please enter a valid phone.\n");
		while (getchar() != '\n'); // Clear the input buffer
	}
	deleteStudentByPhone(school, phone);
}

void searchStudent(School* school)
{
	char phone[11];
	while (1)
	{
		printf("Enter the student phone to search: ");
		(void)scanf("%10s", phone);
		if (contains_only_digits(phone))
			break;
		printf("Invalid input. Please enter a valid phone.\n");
		while (getchar() != '\n'); // Clear the input buffer
	}
	int* level = (int*)malloc(sizeof(int));
	int* cls = (int*)malloc(sizeof(int));
	Student* st = searchStudentByPhone(school, phone, level, cls);
	if (st != NULL && level != NULL && cls != NULL)
	{
		printf("Level: %d, Class: %d, ", *level, *cls);
		print_student(st);
	}
	else
	{
		printf("Phone not found.\n");
	}
	free(level);
	free(cls);
}

void editStudentGrade(School* school)
{
	char phone[11];
	while (1)
	{
		printf("Enter the student phone: ");
		(void)scanf("%10s", phone);
		if (contains_only_digits(phone))
			break;
		printf("Invalid input. Please enter a valid phone.\n");
		while (getchar() != '\n'); // Clear the input buffer
	}
	int* level = (int*)malloc(sizeof(int));
	int* cls = (int*)malloc(sizeof(int));
	Student* st = searchStudentByPhone(school, phone, level, cls);
	if (st != NULL && level != NULL && cls != NULL)
	{
		printf("Level: %d, Class: %d, ", *level, *cls);
		print_student(st);
		// Prompt the user to change some grades in the range of 10
		printf("Enter the number of grades to change (up to 10): ");
		int numGrades;
		if (scanf("%d", &numGrades) == 1 && numGrades >= 0 && numGrades <= Num_Of_Grades) 
		{
			for (int i = 0; i < numGrades; i++) 
			{
				int gradeNum;
				printf("Enter the grade index to change (1-10): ");
				if (scanf("%d", &gradeNum) == 1 && gradeNum >= 1 && gradeNum <= Num_Of_Grades) 
				{
					int newGrade;
					printf("Enter the new grade for subject %d: ", gradeNum);
					if (scanf("%d", &newGrade) == 1 && newGrade >= 0 && newGrade <= 100) 
					{
						school->sumOfGrades[*level][gradeNum - 1] += (newGrade - st->_grades[gradeNum - 1]);
						st->_grades[gradeNum - 1] = newGrade;
					}
					else 
					{
						--i;
						printf("Invalid grade. Grade not changed.\n");
					}
				}
				else 
				{
					--i;
					printf("Invalid grade number. Skipping this grade.\n");
				}
			}
			printf("Grades updated successfully.\n");
			print_student(st);
		}
		else 
		{
			printf("Invalid number of grades. No grades updated.\n");
		}
	}
	else 
	{
		printf("Phone not found.\n");
	}
	free(level);
	free(cls);
}

void printAllStudents(School* school)
{
	printSchoolData(school);
}

void printTopNStudentsPerCourse(School* school)
{
	int level, course;
	printf("Enter the level: ");
	(void)scanf("%d", &level);
	printf("\nEnter the course index (0-9): ");
	(void)scanf("%d", &course);
	printTop10(school, level, course);
}

void printAverage(School* school)
{
	int level, course;
	printf("Enter the level: ");
	(void)scanf("%d", &level);
	printf("\nEnter the course index (0-9): ");
	(void)scanf("%d", &course);
	double avg = getAverage(school, level, course);
	if (avg != -1)
		printf("Average in level %d, course %d is %f", level, course, avg);
}

void menu() {
	char file_name[] = "students_with_class.txt";
	School* school = read_data_from_file(file_name);
	if (school == NULL)
	{
		printf("Error\n");
		return;
	}
	int input;
	do {
		printf("\n|School Manager<::>Home|\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\t[0] |--> Insert\n");
		printf("\t[1] |--> Delete\n");
		printf("\t[2] |--> Edit\n");
		printf("\t[3] |--> Search\n");
		printf("\t[4] |--> Show All\n");
		printf("\t[5] |--> Top 10 students per course\n");
		printf("\t[6] |--> Underperformed students\n");
		printf("\t[7] |--> Average per course\n");
		printf("\t[8] |--> Export\n");
		printf("\t[9] |--> Exit\n");
		printf("\n\tPlease Enter Your Choice (0-9): ");

		if (scanf("%d", &input) != 1) {
			// Invalid input, clear the input buffer
			while (getchar() != '\n');
			printf("\nInvalid input. Please enter a number between 0 and 9.\n");
			continue;
		}

		switch (input) {
		case Insert:
			insertNewStudent(school);
			break;
		case Delete:
			deleteStudent(school);
			break;
		case Edit:
			editStudentGrade(school);
			break;
		case Search:
			searchStudent(school);
			break;
		case Showall:
			printAllStudents(school);
			break;
		case Top10:
			printTopNStudentsPerCourse(school);
			break;
		case UnderperformedStudents:
			printUnderperformedStudents(school, 15);
			break;
		case Average:
			printAverage(school);
			break;
		case Export:
			exportDatabase(school, "dataExport.txt");
			break;
		case Exit:
			destroySchool(school);
			break;
		default:
			printf("\nThere is no item with symbol \"%d\". Please enter a number between 0 and 9!\n", input);
			break;
		}

		// Clear the input buffer
		while (getchar() != '\n');
	} while (input != Exit);
}
