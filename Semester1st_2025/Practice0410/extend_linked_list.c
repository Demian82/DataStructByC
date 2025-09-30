#include <stdio.h>
#include <malloc.h>

// ����� ����
typedef struct node {
	int data; // ������
	struct node* link; // �ڽŰ� �Ȱ��� �ڷᱸ���� ����Ŵ
} node;

// ��� ���
typedef struct listType {
	int length;  // ����� ����
	struct node* head;  // ù ��° ��带 ����Ű�� ������
} listType;

void linked_list_display(listType* list)
{
	// ����� Ž��
	// ��� : Linked List = [10->20->30]
	node* nptr;  // ��带 ����Ű�� Ž�� ������
	nptr = list->head;
	printf("Linked List = [");
	// Ž�� �����Ͱ� NULL�ƴϸ� Ž��
	while (nptr != NULL) {  // if(nptr)
		printf("%d", nptr->data);
		nptr = nptr->link;  // Ž�������� �̵�
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");
}

void linked_list_free(listType* list)
{
	// ��� ��带 ���ʷ� ���� ( ����� �޸� ��ȯ )
	// �տ������� �ϳ��� ���� �� ������ ����
	 
	// ������ ��带 ����Ű�� ������ ����
	node* nptr = list->head;
	// �ݺ��Ͽ� ������ ������ �����Ѵ�(NULL ���� Ȯ�ε� �� ����)
	while (nptr != NULL)
	{
		// ���� �� ����
		list->head = list->head->link; // nptr->link;
		free(nptr);
		// nptr�� ���� ���� �̵�
		nptr = list->head;
	}
	list->length = 0;
}

void linked_list_insert(listType* list)
{
	node* newNode = NULL;
	node* nptr = NULL;
	int index, pos;

	// �� �տ� ����
	newNode = (node*)malloc(sizeof(node)); // �� ��� ����
	newNode->data = 40;
	// �ڿ������� ����
	newNode->link = list->head;
	list->head = newNode;
	list->length++;

	// �������� ����
	newNode = (node*)malloc(sizeof(node)); // �� ��� ����
	newNode->data = 50;
	newNode->link = NULL;

	// ���� ������ ��带 ����Ű�� ������
	// nptr�� ������ ���� �̵�
	nptr = list->head;
	/*while (nptr->link != NULL)
	{
		nptr = nptr->link;
	} */
	
	for(index = 1; index < list->length; index++)
	{
	    nptr = nptr->link;
	}

	newNode->link = nptr->link; // NULL;
	nptr->link = newNode;
	list->length++;

	// �߰�(position)�� ����
	pos = 3;
	newNode = (node*)malloc(sizeof(node)); // �� ��� ����
	newNode->data = 60;

	nptr = list->head;
	// ������ ��ġ�� ���� ���� nptr �̵�
	for (index = 1; index < pos-1; index++)
	{
		nptr = nptr->link;
	}
	newNode->link = nptr->link;
	nptr->link = newNode;
	list->length++;
}

int main(void)
{
	listType* list;
	node* newNode1;
	node* newNode2;
	node* newNode3;
	int index;
	

	// ��� ����� ����
	list = (listType*)malloc(sizeof(listType));
	// ��� ����� �ʱ�ȭ
	list->length = 0;  // 0��
	list->head = NULL;  // ����Ű�� ��尡 ����

	// ù ��° ��� ����
	newNode1 = (node*)malloc(sizeof(node));
	newNode1->data = 10;
	newNode1->link = NULL;
	list->head = newNode1;  // ����� ù ��° ��带 ����Ŵ
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

	linked_list_display(list);

	linked_list_insert(list);
	linked_list_display(list);

	linked_list_free(list);
	linked_list_display(list);
	
	// �����带 ����
	free(list);
	return 0;
}