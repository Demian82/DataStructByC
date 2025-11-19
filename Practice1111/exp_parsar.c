#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX_SIZE 30  // 연산식의 길이

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
	char infix[MAX_SIZE];  // infix 수식 -> a+b
	int length;  // infix 수식 길이
	char postfix[MAX_SIZE];  // postfix 수식 -> ab+
	int check;  // 올바른 수식(1), 잘못된 수식(0)
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

int exp_parser_compute(expType* exp)
{
	// 생성된 postfix 표현식을 연산
	// 스택을 사용
	// 스택은 char data이므로 정수문자('5') 실제정수로 변환 (5)
	// 정수문자 - 48 -> 진짜 정수

	stackType* stack = linked_stack_init();
	int index;
	char item, number1, number2, result;

	// postfix 항목을 가져옴
	for (index = 0; index < strlen(exp->postfix); index++) {
		item = exp->postfix[index];

		if (item == '+' || item == '-' || item == '*' || item == '/') {
			number2 = linked_stack_pop(stack); // 오른쪽 피연산자
			number1 = linked_stack_pop(stack);

			if (item == '+')
				linked_stack_push(stack, number1 + number2);
			else if (item == '-')
				linked_stack_push(stack, number1 - number2);
			else if (item == '*')
				linked_stack_push(stack, number1 * number2);
			else if (item == '/')
				linked_stack_push(stack, number1 / number2);
		}

		else {
			item = item - 48;
			linked_stack_push(stack, item);
		}
	}

	// 최종결과
	result = linked_stack_pop(stack);
	return result;
}

void exp_parser_check(expType* exp)
{
	// 괄호의 쌍을 검사
	// 스택을 사용
	// left braket '(', '[' 이 나오면 스택에 push
	// right braket ')', ']'이 나오면 스택에서 pop
	// 스택에는 괄호만 들어있음
	// 스택이 비면 정상 수식
	// 올바른 경우 check = 1, 잘못된 경우 check = 0

	stackType* stack = linked_stack_init();
	int index;
	char item, popitem;

	for (index = 0; index < exp->length; index++) {
		item = exp->infix[index];

		// 왼쪽 괄호가 나오면 무조건 스택에 push
		if (item == '(' || item == '[') {
			linked_stack_push(stack, item);
		}

		// 오른쪽 괄호가 나오면 pop
		else if (item == ')' || item == ']') {
			if (stack->top == NULL) {
				// 왼쪽 괄호가 없음
				printf("Left Bracket is None\n");
				exp->check = 0;
				return;
			}
			// 스택이 비어 있지 않을 경우
			popitem = linked_stack_pop(stack);
			// 괄호의 쌍이 맞는지 검사
			if ((item == ')' && popitem != '(') || (item == ']' && popitem != '[')) {
				printf("Bracket is Mismatch\n");
				exp->check = 0;
				return;
			}
		}
	}

	// 최종적으로 스택이 비면 정상 수식
	if (stack->top == NULL) {
		printf("Correct Bracket\n");
		exp->check = 1;
	}
	else {
		printf("Right Bracket is None\n");
		exp->check = 0;
	}
}

int exp_parser_prior(char oper)
{
	// 연산자의 우선 순위 값을 반환함
	// 일반적으로 우선순위가 높을 수록 숫자는 작음 0 > 1 > 2
	// 여기서는 우선순위가 높은 것은 수가 크다고 가정
	// 괄호의 우선순위 가장 낮다

	int prior;  // 우선순위 값
	if (oper == '*' || oper == '/')
		prior = 2;
	else if (oper == '+' || oper == '-')
		prior = 1;
	else if (oper == '(' || oper == ')')  // 괄호의 우선순위
		prior = 0;
	else
		prior = -1; // 잘못된 연산자
	return prior;
}

void infix_to_postfix(expType* exp)
{
	// infix를 postfix로 변환
	// 연산자의 연산방향(left->right)을 고려
	// 우선순위를 고려함 (*,/ 가 +,- 보다 높다)
	// 괄호를 고려한 우선순위를 적용 -> 괄호로 묶여진 연산이 먼저 처리됨
	// a+b-c -> ab+c-
	// a+b*c -> abc*-
	// (a+b)*c -> ab+c*

	stackType* stack = linked_stack_init();
	int index, pindex = 0;  // pindex : postfix 문자열 처리에 필요한 index
	char item, popitem;

	// postfix 표현 초기화
	for (index = 0; index < MAX_SIZE; index++) {
		exp->postfix[index] = 0;  // '\0' 널문자
	}

	// infix 연산식에서 아이템을 하나씩 가져옴
	for (index = 0; index < exp->length; index++) {
		item = exp->infix[index];

		// 왼쪽 괄호(left bracket)가 나오면 스택에 push
		if (item == '(') {
			linked_stack_push(stack, item);
		}

		// 오른쪽 괄호(right bracket)가 나오면
		// 왼쪽 괄호가 나올때 까지 계속 pop 후 출력
		else if (item == ')') {
			popitem = linked_stack_pop(stack);
			while (popitem != '(') {
				exp->postfix[pindex] = popitem;
				pindex++;
				popitem = linked_stack_pop(stack);
			}
		}

		// 연산자일 경우
		else if (item == '+' || item == '-' || item == '*' || item == '/') {
			// 스택에 연산자가 있으면 우선순위를 검사해야 함
			// 우선 순위 검사 함수를 사용	

			// 스택에 연산자가 계속 있으면 우선순위를 계속 따져야 함
			while (stack->top) {
				// 새로운 연산자와 스택의 연산자 우선순위를 비교
				if (exp_parser_prior(item) <= exp_parser_prior(stack->top->data)) {
					// 새로운 연산자 <= 스택의 연산자
					// pop후 출력 push
					popitem = linked_stack_pop(stack);
					exp->postfix[pindex] = popitem;
					pindex++;
				}
				else  // 스택의 연산자가 클 경우
					break;
			}

			// 새로운 연산자는 무조건 push
			linked_stack_push(stack, item);
		}

		// 피연산자일 경우
		else {
			exp->postfix[pindex] = item;
			pindex++;
		}
	}

	// 스택에 남은 연산자를 출력
	while (stack->top) {
		popitem = linked_stack_pop(stack);
		exp->postfix[pindex] = popitem;
		pindex++;
	}
}

void exp_parser_menu(expType* exp)
{
	// infix 수식을 입력 받아 postfix 연산식 변환
	int menu, result;  // 연산결과

	while (1) {
		printf("Expression 1.Input Infix, 2.Postfix & Compute, 3.Exit\n");
		printf("Input the menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			// infix 문자열 입력
			// 가정 : 공백없이 표현식, 연산자 +,-,*,/ 만 허용
			printf("Input the infix Expression ? ");
			scanf_s("%s", exp->infix, MAX_SIZE);
			exp->length = strlen(exp->infix);  // 문자열 길이 계산
			// 괄호의 쌍을 검사
			exp_parser_check(exp);
		}

		else if (menu == 2) {
			if (exp->check == 1) {
				infix_to_postfix(exp);
				printf("Infix : %s\n", exp->infix);
				printf("Postfix : %s\n", exp->postfix);
				// postfix 연산식을 연산
				result = exp_parser_compute(exp);
				printf("result : %d\n", result);
			}
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

expType* exp_parser_init(void)
{
	// 수식 연산 표현 자료구조 초기화
	expType* exp = (expType*)malloc(sizeof(expType));
	int index;
	for (index = 0; index < MAX_SIZE; index++) {
		exp->infix[index] = 0;  // '\0'로 초기화
	}
	exp->length = 0;
	exp->check = 0;
	return exp;
}

int main(void)
{
	expType* exp = exp_parser_init();
	exp_parser_menu(exp);
	free(exp);
	return 0;
}