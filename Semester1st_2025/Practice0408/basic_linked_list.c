#include <stdio.h>
#include <malloc.h>

// ����� ����
typedef struct node
{
	int data; // ������
	struct node* link; // �ڽŰ� �Ȱ��� �ڷᱸ���� ����Ŵ
}  node;

// ��� ���
typedef struct listType
{
	int length; // ����� ����
	struct node* head; // ù ��° ��带 ����Ű�� ������
} listType;

int main(void)
{
	listType* list;
	node* newNode1;
	node* newNode2;
	node* newNode3;
	int index;
	node* nptr; // ��� Ž�� ������

	// ��� ����� ����
	list = (listType*)malloc(sizeof(listType));
	// ��� ����� �ʱ�ȭ
	list->length = 0; // 0��
	list->head = NULL; // ����Ű�� ��尡 ����.

	// ù ���� ��� ����
	newNode1 = (node*)malloc(sizeof(node));
	newNode1->data = 10;
	newNode1->link = NULL;
	list->head = newNode1; // ����� ù ��° ��带 ����Ŵ
	list->length++;

	// �� ��° ��� ����
	newNode2 = (node*)malloc(sizeof(node));
	newNode2->data = 20;
	newNode2->link = NULL;
	newNode1->link = newNode2;
	list->length++;

	// �� ��° ��� ����
	newNode3 = (node*)malloc(sizeof(node));
	newNode3->data = 30;
	newNode3->link = NULL;
	newNode2->link = newNode3;
	list->length++;

	// ����� Ž��
	// ��� : Linked List = [10->20->30]
	// for��
	nptr = list->head; // Ž���������� �ʱ�ȭ : ù��° ��带 ����Ŵ
	printf("Linked list = [");
	for (index = 0; index < list->length; index++)
	{
		// Ž�� �����͸� Ȱ���Ͽ� ��忡 ����
		printf("%d", nptr->data); // ������ ���
		nptr = nptr->link; // ���� ���� �̵�
		// �߰��� '->' ǥ��
		if (index != list->length-1)
			printf("->");
	}
	printf("]\n");

	// while��
	nptr = list -> head;
	printf("Linked list = [");
	while (nptr != NULL) // if(nptr)
	{
		printf("%d", nptr->data);
		nptr = nptr->link; // Ž�������� �̵�
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");

	// ����� ���� : ��� ���� �Ϲݳ���� �޸� ��ȯ
	// �տ������� �ϳ��� ���� �� ������ ����
	// ù ��° ��� ����
	list->head = newNode2;
	free(newNode1);
	// �� ���� ��� ����
	list->head = newNode3;
	free(newNode2);
	// �� ��° ��� ����
	list->head = NULL;
	free(newNode3);
	// �����带 ����
	free(list);


	return 0;
}