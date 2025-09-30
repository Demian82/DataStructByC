#include <stdio.h>
#include <malloc.h>

// �ּ� ���� ����ü
typedef struct juso {
    int id;
    char* name;
    int age;
    char* address;
} juso;

// ��� ����ü
typedef struct node {
    juso data;
    struct node* link;
} node;

// ����Ʈ ����ü
typedef struct listType {
    int length;
    node* head;
} listType;

// ���� ����ü
typedef struct stackType {
    int length;
    node* top;
} stackType;

void address_stack_free(stackType* stack)
{
	node* nptr = stack->top; // ������ top ������ ����
    while (nptr != NULL)
    {
		node* temp = nptr; // nptr�� �ӽ÷� ����
		nptr = nptr->link; // nptr�� ���� ���� �̵�
		free(temp->data.name); // name �޸� ����
		free(temp->data.address); // address �޸� ����
		free(temp); // ��� �޸� ����
    }
    stack->top = NULL;
    stack->length = 0;
}

void address_list_free(listType* list)
{
	node* nptr = list->head; // ����Ʈ�� head ������ ����
    while (nptr != NULL)
    {
		node* temp = nptr; // nptr�� �ӽ÷� ����
		nptr = nptr->link; // nptr�� ���� ���� �̵�
		free(temp->data.name); // name �޸� ����
		free(temp->data.address); // address �޸� ����
		free(temp); // ��� �޸� ����
    }
	list->head = NULL;
	list->length = 0;
}

juso* address_stack_pop(stackType* stack)
{
    if (stack->top == NULL)
        return NULL;

    node* temp = stack->top;
    stack->top = temp->link;
    stack->length--;

    juso* data = (juso*)malloc(sizeof(juso));
    data->id = temp->data.id;
    data->age = temp->data.age;
    data->name = (char*)malloc(strlen(temp->data.name) + 1);
    strcpy(data->name, temp->data.name);
    data->address = (char*)malloc(strlen(temp->data.address) + 1);
    strcpy(data->address, temp->data.address);

    free(temp->data.name);
    free(temp->data.address);
    free(temp);

    return data;
}

void address_list_undo(listType* list, stackType* stack)
{
    if (stack->length == 0)
	{ // ������ ����ִ� ���
        printf("Stack is Empty!!\n");
        return;
    }

    juso* item = address_stack_pop(stack);
	// juso����ü ������ item���� �� stack���� pop�� ���� item�� ����
    
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data.id = item->id;
	newNode->data.age = item->age;
	newNode->data.name = (char*)malloc(strlen(item->name) + 1);
	strcpy(newNode->data.name, item->name);
	newNode->data.address = (char*)malloc(strlen(item->address) + 1);
	strcpy(newNode->data.address, item->address);

	newNode->link = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        node* nptr = list->head;
        while (nptr->link != NULL)
        {
            nptr = nptr->link;
        }
        nptr->link = newNode;
    }

    list->length++;

    free(item->name);
    free(item->address);
    free(item);
}

void address_stack_push(stackType* stack, juso* item)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data.id = item->id;
    newNode->data.age = item->age;
    newNode->data.name = (char*)malloc(strlen(item->name) + 1);
    strcpy(newNode->data.name, item->name);
    newNode->data.address = (char*)malloc(strlen(item->address) + 1);
    strcpy(newNode->data.address, item->address);
    newNode->link = stack->top;
    stack->top = newNode;
    stack->length++;
}

void address_list_display(listType* list)
{
    printf("Linked Juso List\n");
	node* nptr = list->head; // ����Ʈ�� head ������ ����
    while (nptr != NULL)
    {
        printf("ID : %d    �̸� : %s    ���� : %d    �ּ� : %s\n",
            nptr->data.id, nptr->data.name, nptr->data.age, nptr->data.address);
		nptr = nptr->link; // ���� ���� �̵�
    }
}

juso* juso_list_input(void)
{
    juso* item = (juso*)malloc(sizeof(juso));
    item->name = (char*)malloc(100 * sizeof(char));
    item->address = (char*)malloc(100 * sizeof(char));
    
    printf("Input ID: ");
    scanf_s("%d", &item->id);
    getchar();

    printf("Input Name: ");
	scanf_s("%s", item->name, 100); // name������ �ִ� 100��
    getchar();

    printf("Input Age: ");
    scanf_s("%d", &item->age);
    getchar();

    printf("Input Address: ");
	scanf_s("%s", item->address, 100); // address������ �ִ� 100��
    getchar();

	return item;
}

void address_list_insert(listType* list, int pos, juso* item)
{
    node* newNode = NULL;
	node* nptr = NULL;
    
	// pos ���� ���� �������� Ȯ��
    if (pos < 1 || pos > list->length+1)
    {
        printf("Position out of range\n");
        return;
    }

    newNode = (node*)malloc(sizeof(node)); 
    newNode->data.id = item->id;
    newNode->data.age = item->age;
    newNode->data.name = (char*)malloc(strlen(item->name) + 1);
    strcpy(newNode->data.name, item->name);
    newNode->data.address = (char*)malloc(strlen(item->address) + 1);
    strcpy(newNode->data.address, item->address);
    newNode->link = NULL;

    if (pos == 1)
    {
        newNode->link = list->head;
        list->head = newNode;
    }
    else
    {
        nptr = list->head;
        for (int index = 1; index < pos - 1; index++)
        {
            nptr = nptr->link;
        }
        newNode->link = nptr->link;
        nptr->link = newNode;
    }

    list->length++;
    free(item);
}

int address_list_delete(listType* list, int pos, stackType* stack)
{
    node* nptr = NULL;
	node* pptr = NULL;
	int index;
	int delitem;

	// ����Ʈ�� ����ִ� ���
	if (list->head == NULL) // list->length == 0;
	{
		printf("List is Empty\n");
		return -1;
	}

	// position�� ��� ���
	if (pos < 1 || pos > list->length)
	{
		printf("Position out of range\n");
			return -1;
	}

	// ���� ���������
	nptr = list->head;

	// ù ��° ��带 ���� (pos = 1)
	if (pos == 1)
	{
		list->head = list->head->link; // nptr->link
	}
	// pos�� 2 �̻��� ���
	else
	{
		// ���� ��ġ(pos)�� �̵�
		for (index = 1; index < pos; index++)
		{
			pptr = nptr; // ���� ���� ������
			nptr = nptr->link;
		}
        pptr->link = nptr->link; // ���� ��带 �����ϰ� ����
	}

	address_stack_push(stack, &nptr->data);

	delitem = nptr->data.id;
	free(nptr->data.name);
    free(nptr->data.address);
	free(nptr);
	list->length--;
	return delitem;
}

void address_list_menu(listType* list, stackType* stack)
{
    int menu, pos, id;
    juso* item;

    while (1)
    {
        printf("Linked Juso List 1.Insert, 2.Delete, 3.Undo, 4.Display, 5.Exit\n");
        printf("Input the Menu : ");
        scanf_s("%d", &menu);
        getchar();

        if (menu == 1)
        { // ����
            printf("Insert Position ? ");
            scanf_s("%d", &pos);
            getchar();
            item = juso_list_input();
            address_list_insert(list, pos, item);
            printf("\n");
        }
        else if (menu == 2)
        { // ����
            printf("Delete Position ? ");
            scanf_s("%d", &pos);
            getchar();
            id = address_list_delete(list, pos, stack);
			printf("Deleted ID: %d\n", id);
            printf("\n");
        }
        else if (menu == 3)
        { // ����
            address_list_undo(list, stack);
            printf("\n");
        }
        else if (menu == 4)
        { // ���
            address_list_display(list);
            printf("\n");
        }
        else if (menu == 5)
        { // ����
            address_list_free(list);
            address_stack_free(stack);
            address_list_display(list);
            break;
        }
		else
        { // �߸��� �޴� �Է�
            printf("MENU ERROR\n");
            printf("\n");
            break;
        }
    }
}

listType* address_list_init(void)
{ // ����Ʈ �ʱ�ȭ
    listType* list = (listType*)malloc(sizeof(listType));
    list->length = 0;
    list->head = NULL;
    return list;
}

stackType* address_stack_init(void)
{ // ���� �ʱ�ȭ
    stackType* stack = (stackType*)malloc(sizeof(stackType));
    stack->length = 0;
    stack->top = NULL;
    return stack;
}

int main(void)
{
    listType* list = address_list_init();
    stackType* stack = address_stack_init();
    address_list_menu(list, stack);
	
    free(list);
    free(stack);
    return 0;
}