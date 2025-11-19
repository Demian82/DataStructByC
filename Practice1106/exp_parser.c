#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX_SIZE 30 // 연산식의 길이

// 스택의 자료구조
typedef struct snode {
	char data;  // 연산식 항목(문자)이 아이템
	struct snode* link;
} snode;

typedef struct stackType {
	int length;
	snode* top;
} stackType;

// 연산 수식에 사용되는 자료구조
typedef struct expType {
	char infix[MAX_SIZE]; // infix 수식 -> a+b
	int length; // infix 수식 길이
	char postfix[MAX_SIZE]; // postfix 수식 -> ab+
} expType;

// 스택의 연산
stackType* linked_stack_init(void)
{
	stackType* stack = (stackType*)malloc(sizeof(stackType));
	stack->length = 0;
	stack->top = NULL;
	return stack;
}

char linked_stack_pop(stackType* stack)
{
	// pop은 첫 번재 노드만 삭제
	char popitem = NULL;
	snode* nptr = NULL;  // 삭제노드를 가리킴

	// 스택이 비어있을 경우
	if (stack->top == NULL) {
		printf("stack is Empty\n");
		return NULL;
	}

	nptr = stack->top;
	stack->top = nptr->link;
	popitem = nptr->data;
	free(nptr);
	stack->length--;
	return popitem;
}

void linked_stack_push(stackType* stack, char item)
{
	// 연결리스트에서 첫 번째 노드로 삽입
	// 마지막으로 삽입된 노드가 첫 번재 노드가 됨
	snode* newNode = NULL;
	newNode = (snode*)malloc(sizeof(snode));
	newNode->data = item;
	newNode->link = stack->top;
	stack->top = newNode;
	stack->length++;
}

void infix_to_postfix1(expType* exp)
{
	// infix를 postfix로 변환
	// 연산자의 연산방향(left->right)을 고려, 우선순위 고려하지 않음
	// a+b-c -> abc-+ (X) ab+c- (O)

	stackType* stack = linked_stack_init();
	int index, pindex = 0; // pindex: postfix 문자열 처리에 필요한 index
	char item, popitem;

	// postfix 표현 초기화
	for (index = 0; index < MAX_SIZE; index++)
	{
		exp->postfix[index] = 0; // '\0' null
	}

	// infix 연산식에서 아이템을 하나씩 가져옴
	for (index = 0; index < exp->length; index++)
	{
		item = exp->infix[index];

		// 연산자 피연산자 비교
		// 연산자일 경우
		if (item == '+' || item == '-' || item == '*' || item == '/')
		{
			// 스택에 연산자가 있으면 pop하여 출력 후 다시 push
			if (stack->top) {
				popitem = linked_stack_pop(stack);
				exp->postfix[pindex] = popitem;
				pindex++;
			}
			// 새로운 연산자는 무조건 push
			linked_stack_push(stack, item);
		}

		// 연산자일 경우
		else {
			exp->postfix[pindex] = item;
			pindex++;
		}
	}

	// 스택에 남은 연산자를 출력
	while (stack->top) {
		popitem = linked_stack_pop(stack);
		printf("%c", popitem);
	}
}

void exp_parser_menu(expType* exp)
{
	// Infix 수식을 입력 받아 postfix 연산식 변환
	int menu;

	while (1) {
		printf("Expression Tree 1.Input Infix, 2.Display Postfix, 3.Exit\n");
		printf("Input the menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			// infix 문자열 입력
			// 가정: 공백없이 표현식, 연산자 사칙연산만 허용
			printf("Input the infix Expression ? ");
			scanf_s("%s", exp->infix, MAX_SIZE);
			exp->length = strlen(exp->infix); // 문자열 길이 계산
		}

		else if (menu == 2) {
			infix_to_postfix1(exp);
			printf("Infix : %s\n", exp->infix);
			printf("Postfix : %s\n", exp->postfix);
		}

		else if (menu == 3) {
			break;
		}

		else {
			printf("menu error\n");
		}
		printf("\n");
	}
}

expType* exp_parser_init()
{
	// 수식 연산 표현의 초기화
	expType* exp = (expType*)malloc(sizeof(expType));
	int index;
	for (index = 0; index < MAX_SIZE; index++) {
		exp->infix[index] = 0; // '\0'로 초기화
	}
	exp->length = 0;
	return exp;
}

int main(void)
{
	expType* exp = exp_parser_init();
	exp_parser_menu(exp);
	free(exp);
	return 0;
}