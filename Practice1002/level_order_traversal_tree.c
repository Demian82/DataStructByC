#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left; // ���� �ڽ�
	struct tnode* right; // ������ �ڽ�
} tnode;

typedef struct treeType {
	tnode* root;  // ���� Ʈ���� ��Ʈ ���
	tnode* parent;  // ���� ����Ʈ���� �θ���
} treeType;

// level order�� �ʿ��� ť�� �ڷᱸ��
typedef struct qnode {
	tnode* data;
	struct qnode* link;
} qnode;

// ť�� ������
typedef struct queueType {
	int length;
	qnode* front;  // ť�� ������� ������ (ù��° ���)
	qnode* rear;  // ť�� ���Գ�� ������ (������ ���)
} queueType;

// level order�� �ʿ��� ť�� ����
tnode* linked_queue_delete(queueType* queue)
{
	tnode* delitem;
	qnode* nptr = NULL;

	// ť�� ������� ���
	if (queue->front == NULL) {
		printf("Queue is Empty\n");
		return NULL;
	}

	// ť���� ��� ���� (ù ��° ���)
	nptr = queue->front;  // ���� ��� ������
	queue->front = nptr->link;  // queue->front->link

	// ���� �� ��尡 �������� ����
	// rear �����͸� ���� (NULL)
	if (queue->front == NULL) {
		queue->rear = NULL;
	}

	delitem = nptr->data;
	free(nptr);  // ��带 �޸� �ݳ�
	queue->length--;
	return delitem;
}

void linked_queue_insert(queueType* queue, tnode* item)
{
	qnode* newNode = NULL;

	newNode = (qnode*)malloc(sizeof(qnode));
	newNode->data = item;
	newNode->link = NULL;

	// ��尡 ���� ���
	if (queue->rear == NULL) {
		queue->rear = newNode;
		queue->front = newNode; // ù ��° ��带 �����Ѿ� ��
	}

	// ��尡 �ּ� 1�� �̻� �ִ� ���
	// rear�� ����
	else {
		queue->rear->link = newNode;  // ������ ���� ����
		queue->rear = newNode;
	}
	queue->length++;
}

queueType* linked_queue_init(void)
{
	// ť�� ���� (�������� �޸� �Ҵ�)
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	queue->length = 0;
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

void tree_level_order(treeType* tree)
{
	// ť�� ����
	queueType* queue = linked_queue_init();
	// ��Ʈ ��带 ť�� ����
	linked_queue_insert(queue, tree->root);

	// ť�� ��尡 ������ �ݺ�, ������ �ߴ�
	printf("Binary Tree Level Order = [");
	while (queue->front) {
		// ť���� Ʈ�� ��带 ������ �ͼ� (ť ����)
		// ���� �ڽ��� ������ �ٽ� ť�� ����
		// ������ �ڽ��� ������ �ٽ� ť�� ����

		// ���� Ʈ���� �θ���� ����
		tree->parent = linked_queue_delete(queue);

		// ��� (�湮)
		printf("%c", tree->parent->data);

		// �θ����� ���� �ڽ��� �ֳ� �˻�
		if (tree->parent->left) {
			// ������ �ٽ� ť�� ����
			linked_queue_insert(queue, tree->parent->left);
		}
		// �θ����� ������ �ڽ��� �ֳ� �˻�
		if (tree->parent->right) {
			// ������ �ٽ� ť�� ����
			linked_queue_insert(queue, tree->parent->right);
		}

		if (queue->front) {
			printf("->");
		}
	}
	printf("]\n");
}

// linked tree�� ����
void linked_tree_add(treeType* tree, char pitem, char litem, char ritem)
{
	// Top-down ��� : ��Ʈ ��� ����
	// �ϳ��� ����Ʈ���� �����ϴ� ����
	// �Ʒ��� �ٸ� ����Ʈ���� ����
	tnode* newNode = NULL;

	// ��Ʈ�� ���� ��� ��Ʈ ��带 ����
	if (tree->root == NULL) {
		newNode = (tnode*)malloc(sizeof(tnode));
		newNode->data = pitem;
		tree->root = newNode;
		tree->parent = newNode;
	}

	// ���޵Ǵ� �θ��� �����۰� ���� ���� Ʋ���� �θ�� ��ġ���� �ʴٸ�
	if (pitem != tree->parent->data) {
		printf("Parent node Error\n");
		return;
	}

	// ���� �ڽ��� �ִٸ�
	if (litem != '-') {
		tree->parent->left = (tnode*)malloc(sizeof(tnode));
		tree->parent->left->data = litem;
		tree->parent->left->left = NULL;
		tree->parent->left->right = NULL;
	}
	// �ڽ��� ���ٸ�
	else {
		tree->parent->left = NULL;
	}

	// ������ �ڽ��� �ִٸ�
	if (ritem != '-') {
		tree->parent->right = (tnode*)malloc(sizeof(tnode));
		tree->parent->right->data = ritem;
		tree->parent->right->left = NULL;
		tree->parent->right->right = NULL;
	}
	// �ڽ��� ���ٸ�
	else {
		tree->parent->right = NULL;
	}
}

void linked_tree_display(treeType* tree)
{
	// �ϳ��� ���� Ʈ���� ������ ���
	// ���޵Ǵ� ������ ����Ʈ���� �θ���
	char pitem, litem, ritem;

	// ť�� ����
	queueType* queue = linked_queue_init();
	// ��Ʈ ��带 ť�� ���� ����
	linked_queue_insert(queue, tree->root);

	// ť�� ��尡 ������ �ݺ�, ������ �ߴ�
	while (queue->front) {
		// ť���� Ʈ�� ��带 ������ �ͼ� (ť ����)
		// ���� �ڽ��� ������ �ٽ� ť�� ����
		// ������ �ڽ��� ������ �ٽ� ť�� ����

		// ���� Ʈ���� �θ���� ����
		tree->parent = linked_queue_delete(queue);


		// Ʈ���� �������� �ʴ� ���
		if (tree->parent == NULL) {
			printf("Tree is None\n");
			return;
		}

		//---------------------------------
		// ���� Ʈ���� ������ ���
		pitem = tree->parent->data;
		if (tree->parent->left)  // �ڽ��� �����ϸ� nptr->left != NULL
			litem = tree->parent->left->data;
		else
			litem = '-';  // �ڽ��� ����

		if (tree->parent->right)
			ritem = tree->parent->right->data;
		else
			ritem = '-';
		// �ϳ��� ����Ʈ���� ����
		printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);
		//-------------------------

		// �θ����� ���� �ڽ��� �ֳ� �˻�
		if (tree->parent->left) {
			// ������ �ٽ� ť�� ����
			linked_queue_insert(queue, tree->parent->left);
		}
		// �θ����� ������ �ڽ��� �ֳ� �˻�
		if (tree->parent->right) {
			// ������ �ٽ� ť�� ����
			linked_queue_insert(queue, tree->parent->right);
		}
	}
}

treeType* linked_tree_init(void)
{
	// ������ �ʱ�ȭ
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;
	return tree;
}

int main(void)
{
	treeType* tree = linked_tree_init();

	// Ʈ�� ����
	// ��Ʈ���� �ϳ��� ����Ʈ���� ����
	// �θ��� �����ʹ� �������� �̵��Ͽ� ����Ʈ���� ����

	tree->parent = tree->root;
	linked_tree_add(tree, 'A', 'B', 'C');
	// Ʈ��������, �θ������, �����ڽ� ������, ������ �ڽ� ������
	// �ڽ��� ���� ��� : '-'

	tree->parent = tree->root->left;
	linked_tree_add(tree, 'B', 'D', '-');

	tree->parent = tree->root->right;
	linked_tree_add(tree, 'C', '-', 'E');

	// Ʈ�� ���
	// ����� ���� Ʈ���� �θ��带 �������� ����

	// level order ���
	tree_level_order(tree);

	// tree�� ���� ���
	linked_tree_display(tree);
	return 0;
}