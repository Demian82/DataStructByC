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

void linked_tree_add(treeType* tree, char pitem, char litem, char ritem)
{
	// TOP->DOWN ��� : ��Ʈ ��� ����
	// �ϳ��� ����Ʈ���� �����ϴ� ����
	// �Ʒ��� �ٸ� ����Ʈ���� ���δ�
	tnode* newNode = NULL;

	// ��Ʈ�� ���� ��� ��Ʈ ��带 ����
	if (tree->root == NULL) {
		newNode = (tnode*)malloc(sizeof(tnode));
		newNode->data = pitem;
		tree->root = newNode;
		tree->parent = newNode;
	}

	// ���޵Ǵ� �θ��� �����۰� ���� ���� Ʈ���� �θ�� ��ġ���� �ʴٸ�
	if (pitem != tree->parent->data)
	{
		printf("Parent node Error\n");
		return;
	}

	// ���� �ڽ��� �ִٸ�
	if (litem != '-')
	{
		tree->parent->left = (tnode*)malloc(sizeof(tnode));
		tree->parent->left->data = litem;
		tree->parent->left->left = NULL;
		tree->parent->left->right = NULL;
	}
	// �ڽ��� ���ٸ�
	else
	{
		tree->parent->left = NULL;
	}

	// ������ �ڽ��� �ִٸ�
	if (ritem != '-')
	{
		tree->parent->right = (tnode*)malloc(sizeof(tnode));
		tree->parent->right->data = ritem;
		tree->parent->right->left = NULL;
		tree->parent->right->right = NULL;
	}
	// �ڽ��� ���ٸ�
	else
	{
		tree->parent->right = NULL;
	}
	
}

void linked_tree_display(tnode* parent)
{
	// �ϳ��� ����Ʈ���� ������ ���
	// ���޵Ǵ� ������ ����Ʈ���� �θ���

	char pitem, litem, ritem;

	// Ʈ���� �������� �ʴ� ���
	if (parent == NULL)
	{
		printf("Tree is empty.");
		return;
	}

	pitem = parent->data;
	if (parent->left) {// nptr->left != NULL
		litem = parent->left->data;
	}
	else
	{
		litem = '-';
	}

	if (parent->right) {// nptr->right != NULL
		ritem = parent->right->data;
	}
	else
	{
		ritem = '-';
	}

	printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);
}

treeType* linked_tree_init(void)
{
	// ������ �ʱ�ȭ
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;
	return tree;
}

int main()
{
	treeType* tree = linked_tree_init();
	
	// Ʈ�� ����
	// ��Ʈ���� �ϳ��� ����Ʈ���� ����
	// �θ��� �����ʹ� �������� �̵��Ͽ� ����Ʈ���� ����

	tree->parent = tree->root;
	linked_tree_add(tree, 'A', 'B', 'C');
	// Ʈ��������, �θ������, ���� �ڽ� ������, ������ �ڽ� ������
	// �ڽ��� ���� ��� '-'�� ����

	tree->parent = tree->root->left;
	linked_tree_add(tree, 'B', 'D', '-');

	tree->parent = tree->root->right;
	linked_tree_add(tree, 'C', '-', 'E');

	// Ʈ�� ���
	// ����� ���� Ʈ���� �θ��带 �������� ����

	printf("Linked Binary Tree\n");
	// �θ��带 ��Ʈ�� �̵�
	tree->parent = tree->root;
	linked_tree_display(tree->parent);
	// ���� �ڽ��� ���� Ʈ��
	linked_tree_display(tree->parent->left);
	// ������ �ڽ��� ���� Ʈ��
	linked_tree_display(tree->parent->right);
	
	return 0;
}