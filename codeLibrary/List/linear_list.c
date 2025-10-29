#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5 // ġȯ

// �ڷᱸ���� ����ȭ
typedef struct listType
{
	int data[MAX_SIZE]; // �迭�� ����� ����Ʈ
	int length; // ����Ʈ�� ������ ����
} listType;

void linear_list_display(listType* list)
{
	int index;
	//����Ʈ�� Ž�� �� ���

	printf("Linear List = [");
	for (index = 0; index < list -> length; index++) {
		printf("%d", list -> data[index]);
		// index�� �������� �ƴ϶�� ,�� �ٿ���
		if (index != list->length - 1)
			printf(", ");
	}
	printf("]\n");
}

void linear_list_insert(listType* list, int pos, int item)
{
	int index;

	// ����Ʈ�� ������ ���
	if (list->length == MAX_SIZE)
	{
		printf("List is Full!!\n");
		return;
	}

	// ���� ��ü�� ���� ����ó��
	if (pos < 1 || pos > list->length + 1)
	{
		printf("Postion out of range!!\n");
		return;
	}
	
	for (index = list->length - 1; index >= pos - 1; index--) {
		list->data[index + 1] = list->data[index];
	}
	list->data[pos - 1] = item;
	(list->length)++;
}

int linear_list_delete(listType* list, int pos)
{
	int index;
	int delItem;

	// ����Ʈ�� ��� ���� ���
	if (list->length == 0)
	{
		printf("List is Empty!!\n");
		return -1; // ���� ����
	}

	// ���� ��ġ ����
	if (pos<1 || pos > list->length)
	{
		printf("Position out of range!!\n");
		return -1;
	}

	delItem = list->data[pos - 1];
	for (index = pos - 1; index < list->length - 1; index++) {
		list->data[index] = list->data[index + 1];
	}
	(list->length)--; // ���� ����
	return delItem;
}

void linear_list_menu(listType* list)
{
	int pos; //��ġ
	int delItem; // ���� ���� �����ϱ� ���� ����
	int item; // ������ ������
	int menu;

	// �޴�ȭ
	while (1)
	{
		printf("Linear List : 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Inuput menu : ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Position ? ");
			scanf_s("%d", &pos);
			printf("insert Item ? ");
			scanf_s("%d", &item);
			linear_list_insert(list, pos, item);
		}
		else if (menu == 2)
		{
			printf("Delete Position ? ");
			scanf_s("%d", &pos);
			delItem = linear_list_delete(list, pos);
			if (delItem >= 0)
			{
				printf("Delete Item : %d\n", delItem);
			}
		}
		else if (menu == 3)
		{
			linear_list_display(list);
		}
		else if (menu == 4)
		{
			printf("exit\n");
			break;
		}
		else
		{
			printf("menu error\n");
		}
	}

}

listType* linear_list_init(void)
{
	// �ڷᱸ���� �ʱ�ȭ
	// ���� �޸� �Ҵ�
	listType* list = (listType*)malloc(sizeof(listType));
	list->length = 0;
	
	return list;
}

int main(void)
{
	listType* list = linear_list_init();
	linear_list_menu(list);
	free(list);

	return 0;
}