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

// 재귀 호출을 사용한 트리의 순회
// 함수의 인수로 전달하는 데이터는 서브트리의 부모 노드
// 전위 순회 (pre order)
void tree_pre_order(tnode* parent)
{
	// P -> LC -> RC
	if (parent) {
		printf("%c", parent->data);
		tree_pre_order(parent->left);
		tree_pre_order(parent->right);
	}
}

// 중위 순회
void tree_in_order(tnode* parent)
{
	// LC -> P -> RC
	if (parent) {
		
		tree_in_order(parent->left);
		printf("%c", parent->data);
		tree_in_order(parent->right);
	}
	
}

// 후위 순회 (post order)
void tree_post_order(tnode* parent)
{
	// LC -> RC -> P
	if (parent) {
		
		tree_post_order(parent->left);
		tree_post_order(parent->right);
		printf("%c", parent->data);
	}
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
		printf("Linked Binary Tree 1.Add, 2.Level Order, 3.Tree Oreder, "
			"4.Display, 5.Exit\n");
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
			printf("Pre Order = [");
			tree_pre_order(tree->root);
			printf("]\n");

			printf("In Order = [");
			tree_in_order(tree->root);
			printf("]\n");

			printf("Post Order = [");
			tree_post_order(tree->root);
			printf("]\n");
			
		}

		else if (menu == 4) {
			linked_tree_display(tree);
		}

		else if (menu == 5) {
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