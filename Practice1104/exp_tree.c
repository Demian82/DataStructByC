#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAX_SIZE 30

// 수식 : 연산자와 피연산자로 구성 (a+b*c)
// 오른쪽에서 왼쪽으로 연산
// 우선순위 : *, /는 +, - 보다 높다 (먼저 연산)
// 수식에 괄호가 있다면 가장 먼저 연산을 수행

// 수식의 표현법
// infix(중위) : 일반적인 수식 : a+b
// prefix(전위) : 연산자가 피연산자보다 먼저 나옴 : +ab
// postfix(후위) : 피연산자가 연산자보다 먼저 나옴: ab+

// 컴파일러는 infix로 표현된 수식을 postfix로 변환 후 연산을 수행
// postfix로 표혆된 수식의 연산은 스택을 사용

// postfix로 표현된 연산식을 수식 트리로 만들기
// 1. postfix 수식을 배열로 저장
// 2. postfix 수식으로부터 하나씩 반복해서 가져옴
// 3. 피연산자와 연산자를 구분해서 철
// 4. 피연산자는 노드를 만들어 스택에 push
// 5. 연산자는 부모노드로 만든 후 스택에서 pop후 자식으로 연결
//    스택에서 먼저 pop한 노드는 오른쪽 자식으로 연결
// 6. 자식이 연결된 연산자 노드는 다시 스택에 push

// 트리의 자료구조
typedef struct tnode {
	char data;
	struct tnode* left;
	struct tnode* right;
} tnode;

typedef struct treeType {
	tnode* root;
	tnode* parent;
} treeType;

// 스택의 자료구조
typedef struct snode {
	tnode* data;  // 트리의 노드가 아이템
	struct snode* link;
} snode;

typedef struct stackType {
	int length;
	snode* top;
} stackType;

// 연산 수식에 사용되는 자료구조
typedef struct expType {
	char postfix[MAX_SIZE]; // postfix 수식
	int length; // postfix 길이
} expType;

// 스택의 연산
stackType* linked_stack_init(void)
{
	stackType* stack = (stackType*)malloc(sizeof(stackType));
	stack->length = 0;
	stack->top = NULL;
	return stack;
}

tnode* linked_stack_pop(stackType* stack)
{
	// pop은 첫 번재 노드만 삭제
	tnode* popitem = NULL;
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

void linked_stack_push(stackType* stack, tnode* item)
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

void exp_tree_add(treeType* tree, expType* exp)
{
	// 수식 트리 생성
	stackType* stack = linked_stack_init(); // 스택 생성
	int index;
	char item;

	// postfix에서 아이템 가져오기
	for (index = 0; index < exp->length; index++)
	{
		item = exp->postfix[index];

		// 트리 노드 생성
		tnode* newNode = (tnode*)malloc(sizeof(tnode));
		
		// 피연산자 연산자 구분
		// 피연산자이면
		if (item != '+' && item != '-' && item != '*' && item != '/')
		{
			newNode->data = item;
			newNode->left = NULL;
			newNode->right = NULL;
		}
		// 연산자이면
		else
		{
			newNode->data = item;
			newNode->right = linked_stack_pop(stack);
			newNode->left = linked_stack_pop(stack);
		}

		linked_stack_push(stack, newNode);
	}

	// 마지막으로 스택에서 pop-> 루트노드
	tree->root = linked_stack_pop(stack);
}

void tree_in_order(tnode* parent)
{
	// 재귀 호출을 통한 중위 순회
	// LC -> P -> RC
	if (parent) {

		tree_in_order(parent->left);
		printf("%c", parent->data);
		tree_in_order(parent->right);
	}
}

void exp_tree_menu(treeType* tree, expType* exp)
{
	// postfix 수식을 입력 받아 수식트리 구성
	int menu;

	while (1) {
		printf("Expression Tree 1.Input Postfix, 2.Display, 3.Exit\n");
		printf("Input the menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			printf("Input the postfix Expression ? ");
			scanf_s("%s", exp->postfix, MAX_SIZE);
			exp->length = strlen(exp->postfix); // 문자열 길이 계산
			// 수식 트리 생성
			exp_tree_add(tree, exp);
		}

		else if (menu == 2) {
			printf("Expression Tree In-Order = ");
			tree_in_order(tree->root);
			printf("\n");
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

treeType* linked_tree_init(void)
{
	// 헤더노드 초기화
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;
	return tree;
}

treeType* exp_tree_init(void)
{
	// 수식 트리의 초기화
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;
	return tree;
}

expType* exp_parser_init()
{
	// 수식 연산 표현의 초기화
	expType* exp = (expType*)malloc(sizeof(expType));
	int index;
	for (index = 0; index < MAX_SIZE; index++) {
		exp->postfix[index] = 0; // '\0'로 초기화
	}
	exp->length = 0;
	return exp;
}

int main(void)
{
	treeType* tree = exp_tree_init();
	expType* exp = exp_parser_init();
	exp_tree_menu(tree, exp);
	free(tree);
	free(exp);
	return 0;
}