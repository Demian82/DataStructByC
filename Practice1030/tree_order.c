#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left;  // �����ڽ�
	struct tnode* right; // �������ڽ�
} tnode;

typedef struct treeType {
	tnode* root;    // ���� Ʈ���� ��Ʈ���
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
	qnode* rear;   // ť�� ���Գ�� ������ (������ ���)
} queueType;

// ������ �ڷᱸ��
typedef struct snode {
	tnode* data;
	struct snode* link;
} snode;

typedef struct stackType {
	int length;
	snode* top;
} stackType;

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
		queue->front = newNode;  // ù ��° ��带 �����Ѿ� ��
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

stackType* linked_stack_init(void)
{
	stackType* stack = (stackType*)malloc(sizeof(stackType));
	stack->length = 0;
	stack->top = NULL;
	return stack;
}

tnode* linked_stack_pop(stackType* stack)
{
	// pop�� ù ���� ��常 ����
	tnode* popitem = NULL;
	snode* nptr = NULL;  // ������带 ����Ŵ

	// ������ ������� ���
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
	// ���Ḯ��Ʈ���� ù ��° ���� ����
	// ���������� ���Ե� ��尡 ù ���� ��尡 ��
	snode* newNode = NULL;
	newNode = (snode*)malloc(sizeof(snode));
	newNode->data = item;
	newNode->link = stack->top;
	stack->top = newNode;
	stack->length++;
}

// level order ��ȸ
void tree_level_order(treeType* tree)
{
	// ť�� ����
	queueType* queue = linked_queue_init();
	// ��Ʈ ��带 ť�� ���� ����
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

// ��� ȣ���� ����� Ʈ���� ��ȸ
// �Լ��� �μ��� �����ϴ� �����ʹ� ����Ʈ���� �θ� ���
// ���� ��ȸ (pre order)
void tree_pre_order(tnode* parent)
{
	// P -> LC -> RC
	if (parent) {
		printf("%c", parent->data);
		tree_pre_order(parent->left);
		tree_pre_order(parent->right);
	}
}

// ���� ��ȸ
void tree_in_order(tnode* parent)
{
	// LC -> P -> RC
	if (parent) {
		
		tree_in_order(parent->left);
		printf("%c", parent->data);
		tree_in_order(parent->right);
	}
	
}

// ���� ��ȸ (post order)
void tree_post_order(tnode* parent)
{
	// LC -> RC -> P
	if (parent) {
		
		tree_post_order(parent->left);
		tree_post_order(parent->right);
		printf("%c", parent->data);
	}
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

	// ���޵Ǵ� �θ��� �����۰� ���� ���� Ʈ���� �θ�� ��ġ���� �ʴٸ�
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

void linked_tree_menu(treeType* tree)
{
	int menu;
	char pitem, litem, ritem;
	// level order�� ���� ť ����
	queueType* queue = linked_queue_init();

	while (1) {
		printf("Linked Binary Tree 1.Add, 2.Level Order, 3.Tree Oreder, "
			"4.Display, 5.Exit\n");
		printf("Input the menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			tree->parent = linked_queue_delete(queue);

			// ��Ʈ ��带 ������ ���� (��Ʈ�� �ִ��� ������)
			if (tree->root == NULL) {
				// ��Ʈ�� ����
				printf("root ? ");
				scanf_s("\n%c", &pitem, 1);
			}
			// ��Ʈ ���� ���������� ť�� ������� ���
			else if (tree->parent == NULL) {
				printf("sub tree is None\n");
				continue;
			}

			else {
				// ������ ���� Ʈ���� �θ� ����
				pitem = tree->parent->data;
			}

			// ���ʰ� ������ �ڽ��� ����
			// �ڽ��� ���� ��� '-' �� �Է�
			printf("Input Parent %c Left Child : ", pitem);
			scanf_s("\n%c", &litem, 1);
			printf("Input Parent %c Right Child : ", pitem);
			scanf_s("\n%c", &ritem, 1);

			// ���� Ʈ���� ����
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
	// ������ �ʱ�ȭ
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