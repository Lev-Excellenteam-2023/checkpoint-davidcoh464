#include"School.h"
#include <stdbool.h>

School* read_data() {
	FILE* file = fopen("students_with_class.txt", "r");
	if (file == NULL)
	{
		printf("Error opening the file.\n");
		return NULL;
	}
	School* school = createSchool();
	char first_name[50];
	char last_name[50];
	int phone;
	int cls;
	int level;
	int grade[10];
	while (fscanf(file, "%s %s %d %d %d %d %d %d %d %d %d %d %d %d %d",
		first_name, last_name, &phone, &level, &cls,
		&grade[0], &grade[1], &grade[2], &grade[3], &grade[4],
		&grade[5], &grade[6], &grade[7], &grade[8], &grade[9]) == 15)
	{
		addStudent(school, level, cls, create_student(first_name, last_name, phone, grade));
	}

	fclose(file);
	return school;
}



int main() 
{
	School * school = read_data();
	if (school != NULL) {
		printData(school);
		destroySchool(school);
	}
	return 0;
}