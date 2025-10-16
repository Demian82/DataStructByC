#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left; // 왼쪽 자식
	struct tnode* right; // 오른쪽 자식
} tnode;

typedef struct treeType {
	tnode* root;  // 현재 트리의 루트 노드
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
	qnode* rear;  // 큐의 삽입노드 포인터 (마지막 노드)
} queueType;

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
		queue->front = newNode; // 첫 번째 노드를 가리켜야 함
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

void tree_level_order(treeType* tree)
{
	// 큐를 생성
	queueType* queue = linked_queue_init();
	// 루트 노드를 큐에 삽입
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

	// 전달되는 부모노드 아이템과 현재 서브 틀리의 부모와 일치하지 않다면
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

	// 트리 구성
	// 루트부터 하나씩 서브트리를 구성
	// 부모노드 포인터는 수동으로 이동하여 서브트리를 구성

	tree->parent = tree->root;
	linked_tree_add(tree, 'A', 'B', 'C');
	// 트리포인터, 부모아이템, 왼쪽자식 아이템, 오른쪽 자식 아이템
	// 자식이 없을 경우 : '-'

	tree->parent = tree->root->left;
	linked_tree_add(tree, 'B', 'D', '-');

	tree->parent = tree->root->right;
	linked_tree_add(tree, 'C', '-', 'E');

	// 트리 출력
	// 출력할 서브 트리의 부모노드를 수동으로 지정

	// level order 출력
	tree_level_order(tree);

	// tree의 정보 출력
	linked_tree_display(tree);
	return 0;
}