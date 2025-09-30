#include <stdio.h>
#include <malloc.h>

// 주소 정보 구조체
typedef struct juso {
    int id;
    char* name;
    int age;
    char* address;
} juso;

// 노드 구조체
typedef struct node {
    juso data;
    struct node* link;
} node;

// 리스트 구조체
typedef struct listType {
    int length;
    node* head;
} listType;

// 스택 구조체
typedef struct stackType {
    int length;
    node* top;
} stackType;

void address_stack_free(stackType* stack)
{
	node* nptr = stack->top; // 스택의 top 노드부터 시작
    while (nptr != NULL)
    {
		node* temp = nptr; // nptr을 임시로 저장
		nptr = nptr->link; // nptr을 다음 노드로 이동
		free(temp->data.name); // name 메모리 해제
		free(temp->data.address); // address 메모리 해제
		free(temp); // 노드 메모리 해제
    }
    stack->top = NULL;
    stack->length = 0;
}

void address_list_free(listType* list)
{
	node* nptr = list->head; // 리스트의 head 노드부터 시작
    while (nptr != NULL)
    {
		node* temp = nptr; // nptr을 임시로 저장
		nptr = nptr->link; // nptr을 다음 노드로 이동
		free(temp->data.name); // name 메모리 해제
		free(temp->data.address); // address 메모리 해제
		free(temp); // 노드 메모리 해제
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
	{ // 스택이 비어있는 경우
        printf("Stack is Empty!!\n");
        return;
    }

    juso* item = address_stack_pop(stack);
	// juso구조체 형식의 item생성 후 stack에서 pop한 값을 item에 저장
    
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
	node* nptr = list->head; // 리스트의 head 노드부터 시작
    while (nptr != NULL)
    {
        printf("ID : %d    이름 : %s    나이 : %d    주소 : %s\n",
            nptr->data.id, nptr->data.name, nptr->data.age, nptr->data.address);
		nptr = nptr->link; // 다음 노드로 이동
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
	scanf_s("%s", item->name, 100); // name변수는 최대 100자
    getchar();

    printf("Input Age: ");
    scanf_s("%d", &item->age);
    getchar();

    printf("Input Address: ");
	scanf_s("%s", item->address, 100); // address변수는 최대 100자
    getchar();

	return item;
}

void address_list_insert(listType* list, int pos, juso* item)
{
    node* newNode = NULL;
	node* nptr = NULL;
    
	// pos 값이 정상 범위인지 확인
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

	// 리스트가 비어있는 경우
	if (list->head == NULL) // list->length == 0;
	{
		printf("List is Empty\n");
		return -1;
	}

	// position을 벗어날 경우
	if (pos < 1 || pos > list->length)
	{
		printf("Position out of range\n");
			return -1;
	}

	// 삭제 노드포인터
	nptr = list->head;

	// 첫 번째 노드를 삭제 (pos = 1)
	if (pos == 1)
	{
		list->head = list->head->link; // nptr->link
	}
	// pos이 2 이상인 경우
	else
	{
		// 삭제 위치(pos)로 이동
		for (index = 1; index < pos; index++)
		{
			pptr = nptr; // 삭제 이전 포인터
			nptr = nptr->link;
		}
        pptr->link = nptr->link; // 삭제 노드를 제외하고 연결
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
        { // 삽입
            printf("Insert Position ? ");
            scanf_s("%d", &pos);
            getchar();
            item = juso_list_input();
            address_list_insert(list, pos, item);
            printf("\n");
        }
        else if (menu == 2)
        { // 삭제
            printf("Delete Position ? ");
            scanf_s("%d", &pos);
            getchar();
            id = address_list_delete(list, pos, stack);
			printf("Deleted ID: %d\n", id);
            printf("\n");
        }
        else if (menu == 3)
        { // 복구
            address_list_undo(list, stack);
            printf("\n");
        }
        else if (menu == 4)
        { // 출력
            address_list_display(list);
            printf("\n");
        }
        else if (menu == 5)
        { // 종료
            address_list_free(list);
            address_stack_free(stack);
            address_list_display(list);
            break;
        }
		else
        { // 잘못된 메뉴 입력
            printf("MENU ERROR\n");
            printf("\n");
            break;
        }
    }
}

listType* address_list_init(void)
{ // 리스트 초기화
    listType* list = (listType*)malloc(sizeof(listType));
    list->length = 0;
    list->head = NULL;
    return list;
}

stackType* address_stack_init(void)
{ // 스택 초기화
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