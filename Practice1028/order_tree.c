#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left;  // 왼쪽자식
	struct tnode* right; // 오른쪽자식
} tnode;

typedef struct treeType {
	tnode* root;    // 현재 트리의 루트노드
	tnode* parent;  // 현재 서브트리의 부모노드
} treeType;

// level order에 필요한 큐의 자료구조
typedef struct qnode {
	tnode* data;
	struct qnode* link;
} qnode;

// 큐의 헤더노드
typedef struct queueType {
	int length;
	qnode* front;  // 큐의 삭제노드 포인터 (첫번째 노드)
	qnode* rear;   // 큐의 삽입노드 포인터 (마지막 노드)
} queueType;

// 스택의 자료구조
typedef struct snode {
	tnode* data;
	struct snode* link;
} snode;

typedef struct stackType {
	int length;
	snode* top;
} stackType;

// level order에 필요한 큐의 연산
tnode* linked_queue_delete(queueType* queue)
{
	tnode* delitem;
	qnode* nptr = NULL;

	// 큐가 비어있을 경우
	if (queue->front == NULL) {
		printf("Queue is Empty\n");
		return NULL;
	}

	// 큐에서 노드 삭제 (첫 번째 노드)
	nptr = queue->front;  // 삭제 노드 포인터
	queue->front = nptr->link;  // queue->front->link

	// 삭제 후 노드가 존재하지 않음
	// rear 포인터를 정리 (NULL)
	if (queue->front == NULL) {
		queue->rear = NULL;
	}

	delitem = nptr->data;
	free(nptr);  // 노드를 메모리 반납
	queue->length--;
	return delitem;
}

void linked_queue_insert(queueType* queue, tnode* item)
{
	qnode* newNode = NULL;

	newNode = (qnode*)malloc(sizeof(qnode));
	newNode->data = item;
	newNode->link = NULL;

	// 노드가 없는 경우
	if (queue->rear == NULL) {
		queue->rear = newNode;
		queue->front = newNode;  // 첫 번째 노드를 가리켜야 함
	}

	// 노드가 최소 1개 이상 있는 경우
	// rear만 연결
	else {
		queue->rear->link = newNode;  // 마지막 노드로 삽입
		queue->rear = newNode;
	}
	queue->length++;
}

queueType* linked_queue_init(void)
{
	// 큐를 생성 (헤더노드의 메모리 할당)
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	queue->length = 0;
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

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

// level order 순회
void tree_level_order(treeType* tree)
{
	// 큐를 생성
	queueType* queue = linked_queue_init();
	// 루트 노드를 큐에 먼저 삽입
	linked_queue_insert(queue, tree->root);

	// 큐에 노드가 있으면 반복, 없으면 중단
	printf("Binary Tree Level Order = [");
	while (queue->front) {
		// 큐에서 트리 노드를 가지고 와서 (큐 삭제)
		// 왼쪽 자식이 있으면 다시 큐에 삽입
		// 오른쪽 자식이 있으면 다시 큐에 삽입

		// 서브 트리의 부모노드로 지정
		tree->parent = linked_queue_delete(queue);

		// 출력 (방문)
		printf("%c", tree->parent->data);

		// 부모노드의 왼쪽 자식이 있나 검사
		if (tree->parent->left) {
			// 있으면 다시 큐에 삽입
			linked_queue_insert(queue, tree->parent->left);
		}
		// 부모노드의 오른쪽 자식이 있나 검사
		if (tree->parent->right) {
			// 있으면 다시 큐에 삽입
			linked_queue_insert(queue, tree->parent->right);
		}

		if (queue->front) {
			printf("->");
		}
	}
	printf("]\n");
}

// 전위 순회 (pre order)
void tree_pre_order(treeType* tree)
{
	// P -> LC -> RC
	// 스택을 사용하여 구현

	// pre order 순회를 위한 스택의 생성
	stackType* stack = linked_stack_init();

	// 루트 노드를 스택에 넣고 시작
	linked_stack_push(stack, tree->root);

	printf("Binary Tree Pre Order = [");
	while (stack->top) { // 스택에 아이템이 있으면 반복
		// 방문(visit)은 스택에서 꺼낸(pop) 노드로 부터 출발
		// 꺼낸 트리 노드를 부모 노드로 지정
		tree->parent = linked_stack_pop(stack);

		printf("%c", tree->parent->data);  // 방문

		// 자식이 있는지 검사 (오른쪽->왼쪽)
		// 자식이 있으면 자식을 스택에 push
		if (tree->parent->right)
			linked_stack_push(stack, tree->parent->right);
		if (tree->parent->left)
			linked_stack_push(stack, tree->parent->left);

		// -> 표시
		if (stack->top) {
			printf("->");
		}
	}
	printf("]\n");
}

// 중위 순회
void tree_in_order(treeType* tree)
{
	// 중위: LC -> P -> RC
	// 가장 왼쪽의 자식을 먼저 찾음(왼쪽 자식을 먼저 방문)
	// 부모노드로 다시 방문 -> 스택을 활용
	// 이후 오른쪽을 방문 -> 다시 가장 왼쪽 자식을 먼저 찾음

	// 스택의 생성
	stackType* stack = linked_stack_init();
	tree->parent = tree->root;
	// 스택이 빌 때까지(스택에 노드가 있으면)
	// 스택이 비어있더라도 자식노드가 있다면
	printf("Binary Tree In Order = [");
	while (stack->top || tree->parent) {
		// 왼쪽으로 이동
		if (tree->parent) {
			// 부모가 있으면 스택에 push
			// 다시 되돌아 와야 하므로
			linked_stack_push(stack, tree->parent);
			tree->parent = tree->parent->left;
		}
		// 현재 부모가 NULL이라면
		else {
			// 스택에서 pop 방문
			tree->parent = linked_stack_pop(stack);
			printf("%c", tree->parent->data); // 부모 방문
			// 오른쪽 자식으로 이동
			tree->parent = tree->parent->right;
			// 구분문자
			if (stack->top || tree->parent)
				printf("->");
		}
	}
	printf("]\n");
}

// 후위 순회 (post order)
void tree_post_order(treeType* tree)
{
	// pre order : P -> RC -> LC
	// 스택을 사용하여 역순으로 출력
	// LC -> RC -> P

	// post order 순회를 위한 스택의 생성
	// pre order 결과를 저장할 스택 생성
	stackType* stack = linked_stack_init();

	// pre order 결과를 역순으로 저장할 스택 생성
	stackType* outStack = linked_stack_init();

	// 루트 노드를 스택에 넣고 시작
	linked_stack_push(stack, tree->root);

	while (stack->top) { // 스택에 아이템이 있으면 반복
		// 방문(visit)은 스택에서 꺼낸(pop) 노드로 부터 출발
		// 꺼낸 트리 노드를 부모 노드로 지정
		tree->parent = linked_stack_pop(stack);

		// 부모 노드를 다시 스택에 저장
		linked_stack_push(outStack, tree->parent);

		// 자식이 있는지 검사( LC -> RC)
		// 자식이 있으면 자식을 스택에 push
		if (tree->parent->left)
			linked_stack_push(stack, tree->parent->left);
		if (tree->parent->right)
			linked_stack_push(stack, tree->parent->right);
		}

	printf("Binary Tree Post Order = [");
	while (outStack->top) { // outStack에 아이템이 있으면 반복
		tree->parent = linked_stack_pop(outStack);
		printf("%c", tree->parent->data);  // 방문

		// -> 표시
		if (outStack->top) {
			printf("->");
		}
	}
	printf("]\n");
}

// linked tree의 연산
void linked_tree_add(treeType* tree, char pitem, char litem, char ritem)
{
	// Top-down 방식 : 루트 노드 생성
	// 하나의 서브트리를 구성하는 과정
	// 아래로 다른 서브트리를 붙임
	tnode* newNode = NULL;

	// 루트가 없을 경우 루트 노드를 생성
	if (tree->root == NULL) {
		newNode = (tnode*)malloc(sizeof(tnode));
		newNode->data = pitem;
		tree->root = newNode;
		tree->parent = newNode;
	}

	// 전달되는 부모노드 아이템과 현재 서브 트리의 부모와 일치하지 않다면
	if (pitem != tree->parent->data) {
		printf("Parent node Error\n");
		return;
	}

	// 왼쪽 자식이 있다면
	if (litem != '-') {
		tree->parent->left = (tnode*)malloc(sizeof(tnode));
		tree->parent->left->data = litem;
		tree->parent->left->left = NULL;
		tree->parent->left->right = NULL;
	}
	// 자식이 없다면
	else {
		tree->parent->left = NULL;
	}

	// 오른쪽 자식이 있다면
	if (ritem != '-') {
		tree->parent->right = (tnode*)malloc(sizeof(tnode));
		tree->parent->right->data = ritem;
		tree->parent->right->left = NULL;
		tree->parent->right->right = NULL;
	}
	// 자식이 없다면
	else {
		tree->parent->right = NULL;
	}
}

void linked_tree_display(treeType* tree)
{
	// 하나의 서브 트리의 정보를 출력
	// 전달되는 정보는 서브트리의 부모노드
	char pitem, litem, ritem;

	// 큐를 생성
	queueType* queue = linked_queue_init();
	// 루트 노드를 큐에 먼저 삽입
	linked_queue_insert(queue, tree->root);

	// 큐에 노드가 있으면 반복, 없으면 중단
	while (queue->front) {
		// 큐에서 트리 노드를 가지고 와서 (큐 삭제)
		// 왼쪽 자식이 있으면 다시 큐에 삽입
		// 오른쪽 자식이 있으면 다시 큐에 삽입

		// 서브 트리의 부모노드로 지정
		tree->parent = linked_queue_delete(queue);


		// 트리가 존재하지 않는 경우
		if (tree->parent == NULL) {
			printf("Tree is None\n");
			return;
		}

		//---------------------------------
		// 서브 트리의 정보를 출력
		pitem = tree->parent->data;
		if (tree->parent->left)  // 자식이 존재하면 nptr->left != NULL
			litem = tree->parent->left->data;
		else
			litem = '-';  // 자식이 없다

		if (tree->parent->right)
			ritem = tree->parent->right->data;
		else
			ritem = '-';
		// 하나의 서브트리의 정보
		printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);
		//-------------------------

		// 부모노드의 왼쪽 자식이 있나 검사
		if (tree->parent->left) {
			// 있으면 다시 큐에 삽입
			linked_queue_insert(queue, tree->parent->left);
		}
		// 부모노드의 오른쪽 자식이 있나 검사
		if (tree->parent->right) {
			// 있으면 다시 큐에 삽입
			linked_queue_insert(queue, tree->parent->right);
		}
	}
}

void linked_tree_menu(treeType* tree)
{
	int menu;
	char pitem, litem, ritem;
	// level order를 위한 큐 생성
	queueType* queue = linked_queue_init();

	while (1) {
		printf("Linked Binary Tree 1.Add, 2.Level Order, 3.Pre Oreder, "
			"4.In Order, 5.Post Order, 6.Display, 7.Exit\n");
		printf("Input the menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			tree->parent = linked_queue_delete(queue);

			// 루트 노드를 만들지 결정 (루트가 있느냐 없느냐)
			if (tree->root == NULL) {
				// 루트를 생성
				printf("root ? ");
				scanf_s("\n%c", &pitem, 1);
			}
			// 루트 노드는 존재하지만 큐가 비어있을 경우
			else if (tree->parent == NULL) {
				printf("sub tree is None\n");
				continue;
			}

			else {
				// 생성할 서브 트리의 부모를 결정
				pitem = tree->parent->data;
			}

			// 왼쪽과 오른쪽 자식을 지정
			// 자식이 없을 경우 '-' 를 입력
			printf("Input Parent %c Left Child : ", pitem);
			scanf_s("\n%c", &litem, 1);
			printf("Input Parent %c Right Child : ", pitem);
			scanf_s("\n%c", &ritem, 1);

			// 서브 트리를 생성
			linked_tree_add(tree, pitem, litem, ritem);

			if (tree->parent->left)
				linked_queue_insert(queue, tree->parent->left);
			if (tree->parent->right)
				linked_queue_insert(queue, tree->parent->right);
		}

		else if (menu == 2) {
			tree_level_order(tree);
		}

		else if (menu == 3) {
			tree_pre_order(tree);
		}

		else if (menu == 4) {
			tree_in_order(tree);
		}

		else if (menu == 5) {
			tree_post_order(tree);
		}

		else if (menu == 6) {
			linked_tree_display(tree);
		}

		else if (menu == 7) {
			break;
		}

		else {
			printf("menu error\n");
		}
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

int main(void)
{
	treeType* tree = linked_tree_init();
	linked_tree_menu(tree);
	free(tree);
	return 0;
}