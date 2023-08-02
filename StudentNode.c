#include"StudentNode.h"

StudentNode* createStudentNode(Student st)
{
	StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
	if (node == NULL)
	{
		printf("Memory allocation failed for StudentNode.\n");
		return NULL;
	}
	node->data = st;
	node->next = NULL;
	return node;
}

void destroyStudentNode(StudentNode* node)
{
	if (node == NULL)
		return;
	destroy_student(node->data);
	free(node);
}