#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left; // ���� �ڽ�
	struct tnode* right; // ������ �ڽ�
} tnode;

typedef struct treeType {
	tnode* root;
	tnode* parent;
} treeType;

int main()
{
	treeType* tree = NULL;
	tnode* node1, * node2, * node3, * node4, *node5;
	tnode* nptr = NULL;
	char pitem, litem, ritem;

	tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;

	/* TOP->DOWN ���
	// ��Ʈ ��� ����
	// TOP-down ���
	// ��Ʈ�� ����� �θ� ����� �ڽ��� ����� ����
	node1 = (tnode*)malloc(sizeof(tnode));
	node1->data = 'A';
	node1->left = NULL;
	node1->right = NULL;
	// ���� ��带 ��Ʈ ���� ����
	tree->root = node1;

	// ���� �ڽ�
	// ����Ʈ���� �θ��带 ����
	tree->parent = tree->root;
	node2 = (tnode*)malloc(sizeof(tnode));
	node2->data = 'B';
	node2->left = NULL;
	node2->right = NULL;
	// ���� ��带 �θ��� ���� �ڽ����� ����
	tree->parent->left = node2;

	// ������ �ڽ�
	// ����Ʈ���� �θ��带 ����
	node3 = (tnode*)malloc(sizeof(tnode));
	node3->data = 'C';
	node3->left = NULL;
	node3->right = NULL;
	// ���� ��带 �θ��� ������ �ڽ����� ����
	tree->parent->right = node3;

	// �θ��� B�� �̵�
	tree->parent = tree->root->left;

	// B�� ���� �ڽ�
	node4 = (tnode*)malloc(sizeof(tnode));
	node4->data = 'D';
	node4->left = NULL;
	node4->right = NULL;
	// ���� ��带 �θ��� ������ �ڽ����� ����
	tree->parent->left = node4;
	// B�� �������� ����

	// �θ��� C�� �̵�
	tree->parent = tree->root->right;

	// C�� ������ �ڽ�
	node5 = (tnode*)malloc(sizeof(tnode));
	node5->data = 'E';
	node5->left = NULL;
	node5->right = NULL;
	// ���� ��带 �θ��� ������ �ڽ����� ����
	tree->parent->right = node5;
	// C�� ������ ����
	*/


	// Bottom-Up ��� : �ڽ��� ���� ����� �������� ��Ʈ
	node5 = (tnode*)malloc(sizeof(tnode));
	node5->data = 'E';
	node5->left = NULL;
	node5->right = NULL;

	node4 = (tnode*)malloc(sizeof(tnode));
	node4->data = 'D';
	node4->left = NULL;
	node4->right = NULL;

	node3 = (tnode*)malloc(sizeof(tnode));
	node3->data = 'C';
	node3->left = NULL;
	node3->right = node5;

	node2 = (tnode*)malloc(sizeof(tnode));
	node2->data = 'B';
	node2->left = node4;
	node2->right = NULL;

	// ��Ʈ ���
	node1 = (tnode*)malloc(sizeof(tnode));
	node1->data = 'A';
	node1->left = node2;
	node1->right = node3;

	// ��Ʈ ��� ����
	tree->root = node1;

	// Ʈ�� ����
	// ���� Ʈ�� ������ ���
	// P:A -> LC:B, RC:C
	// P:B -> LC:D, RC:-
	// P:C -> LC:-, RC:E

	// �θ��带 ��Ʈ�� �̵�
	tree->parent = tree->root;
	nptr = tree->parent;

	pitem = '-', litem = '-', ritem = '-';
	pitem = nptr->data;
	if (nptr->left) {// nptr->left != NULL
		litem = nptr->left->data;
	}
	if (nptr->right) {// nptr->right != NULL
		ritem = nptr->right->data;
	}
	printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);

	nptr = tree->parent->left;
	pitem = '-', litem = '-', ritem = '-';
	pitem = nptr->data;
	if (nptr->left) {// nptr->left != NULL
		litem = nptr->left->data;
	}
	if (nptr->right) {// nptr->right != NULL
		ritem = nptr->right->data;
	}
	printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);

	nptr = tree->parent->right;
	pitem = '-', litem = '-', ritem = '-';
	pitem = nptr->data;
	if (nptr->left) {// nptr->left != NULL
		litem = nptr->left->data;
	}
	if (nptr->right) {// nptr->right != NULL
		ritem = nptr->right->data;
	}
	printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);

	return 0;
}