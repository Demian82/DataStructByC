#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	struct node* llink; // ������ ��ũ�� ���
	int data;
	struct node* rlink; // ������ ��ũ�� ���
} node;

typedef struct listType // ��� ���
{
	int length;
	struct node* head;
} listType;

int double_list_delete(listType* list, int pos)
{
	int delitem, index;
	node* nptr = NULL;

	// ��尡 ���� ���
	if (list->head == NULL)
	{
		printf("List is Empty\n");
		return -1;
	}

	// position check
	if (pos < 1 || pos > list->length)
	{
		printf("position out of range\n");
		return -1;
	}

	// ù��° ��带 ����
	if (pos == 1)
	{
		nptr = list->head;
		// ��尡 1���� ���
		if (nptr->rlink == NULL)
		{
			list->head = NULL;
		}
		// ��尡 2�� �̻��� ���
		else
		{
			list->head = nptr->rlink; // ���� ��带 ����Ŵ
			nptr->rlink->llink = NULL;
		}
	}
	else // pos�� 2 �̻��� ���
	{
		nptr = list->head;
		// ������ ��ġ�� �̵�
		for (index = 1; index < pos; index++)
		{
			nptr = nptr->rlink;
		}
		// ������ ��尡 �ƴ� ���
		if (nptr->rlink != NULL)
		{
			nptr->llink->rlink = nptr->rlink;
			nptr->rlink->llink = nptr->llink;
		}
		else
		{
			nptr->llink->rlink = nptr->rlink;
		}
	}
	
	delitem = nptr->data;
	free(nptr);
	list->length--;

	return delitem;
}

void double_list_insert(listType* list, int pos, int item)
{
	node* newNode = (node*)malloc(sizeof(node));
	node* nptr = NULL;
	int index;
	
	// position �˻�
	if (pos < 1 || pos > list->length + 1)
	{
		printf("position out of range\n");
		return;
	}

	newNode->data = item;

	// ù��° ���� �����ϴ� ���
	if (pos == 1)
	{
		// ��尡 ���� ���
		if (list->head == NULL)
		{
			list->head = newNode;
			newNode->llink = NULL;
			newNode->rlink = NULL;
		}
		else
		{
			// ��尡 1�� �̻��� ���
			newNode->rlink = list->head;
			list->head = newNode;
			newNode->llink = NULL;
			newNode->rlink->llink = newNode;
		}
	}
	else  // 2��° ���ķ� ����
	{
		nptr = list->head;
		// ������ġ�� ���� ���� nptr�̵�
		for (index = 1; index < pos - 1; index++)
		{
			nptr = nptr->rlink;
		}

		// �߰��� �����ϴ� ���
		if (nptr->rlink != NULL)
		{
			newNode->rlink = nptr->rlink;
			nptr->rlink = newNode;
			newNode->llink = nptr;
			nptr->rlink->llink = newNode;
		}
		else // ������ ���� �����ϴ� ���
		{
			newNode->rlink = nptr->rlink;
			nptr->rlink = newNode;
			newNode->llink = nptr;
			// nptr->rlink->llink = newNode; (�ʿ����)
		}
	}
	list->length++;
}

void double_list_display(listType* list)
{
	node* nptr = list->head;
	printf("Double Linked List = [");
	while (nptr != NULL)
	{
		printf("%d", nptr->data);
		nptr = nptr->rlink;
		if (nptr != NULL)
		{
			printf("<->");
		}
	}
	printf("]\n");
}

void double_list_menu(listType* list)
{
	int menu, pos, item, delitem=-1;

	while (1)
	{
		printf("Double Linked List : 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Position ? ");
			scanf_s("%d", &pos);
			printf("Insert Item ? ");
			scanf_s("%d", &item);
			double_list_insert(list, pos, item);
		}
		else if (menu == 2)
		{
			printf("Delete Position ? ");
			scanf_s("%d", &pos);
			delitem = double_list_delete(list, pos);
			if (delitem > 0)
				printf("Delete Item : %d\n", delitem);
		}
		else if (menu == 3)
		{
			double_list_display(list);
		}
		else if (menu == 4)
		{
			printf("Exit\n");
			break;
		}
		else
		{
			printf("Menu Error\n");
		}
	}
}

listType* double_list_init()
{
	listType* list = (listType*)malloc(sizeof(listType));
	list->length = 0;
	list->head = NULL;
	return list;
}

int main(void)
{
	listType* list = double_list_init();
	double_list_menu(list);
	free(list);

	
	return 0;
}