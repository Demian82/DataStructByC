#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left; // 왼쪽 자식
	struct tnode* right; // 오른쪽 자식
} tnode;

typedef struct treeType {
	tnode* root;
	tnode* parent;
} treeType;

void linked_tree_add(treeType* tree, char pitem, char litem, char ritem)
{
	// TOP->DOWN 방식 : 루트 노드 생성
	// 하나의 서브트리를 구성하는 과정
	// 아래로 다른 서브트리를 붙인다
	tnode* newNode = NULL;

	// 루트가 없을 경우 루트 노드를 생성
	if (tree->root == NULL) {
		newNode = (tnode*)malloc(sizeof(tnode));
		newNode->data = pitem;
		tree->root = newNode;
		tree->parent = newNode;
	}

	// 전달되는 부모노드 아이템과 현재 서브 트리의 부모와 일치하지 않다면
	if (pitem != tree->parent->data)
	{
		printf("Parent node Error\n");
		return;
	}

	// 왼쪽 자식이 있다면
	if (litem != '-')
	{
		tree->parent->left = (tnode*)malloc(sizeof(tnode));
		tree->parent->left->data = litem;
		tree->parent->left->left = NULL;
		tree->parent->left->right = NULL;
	}
	// 자식이 없다면
	else
	{
		tree->parent->left = NULL;
	}

	// 오른쪽 자식이 있다면
	if (ritem != '-')
	{
		tree->parent->right = (tnode*)malloc(sizeof(tnode));
		tree->parent->right->data = ritem;
		tree->parent->right->left = NULL;
		tree->parent->right->right = NULL;
	}
	// 자식이 없다면
	else
	{
		tree->parent->right = NULL;
	}
	
}

void linked_tree_display(tnode* parent)
{
	// 하나의 서브트리의 정보를 출력
	// 전달되는 정보는 서브트리의 부모노드

	char pitem, litem, ritem;

	// 트리가 존재하지 않는 경우
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
	// 헤더노드 초기화
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;
	return tree;
}

int main()
{
	treeType* tree = linked_tree_init();
	
	// 트리 구성
	// 루트부터 하나씩 서브트리를 구성
	// 부모노드 포인터는 수동으로 이동하여 서브트리를 구성

	tree->parent = tree->root;
	linked_tree_add(tree, 'A', 'B', 'C');
	// 트리포인터, 부모아이템, 왼쪽 자식 아이템, 오른쪽 자식 아이템
	// 자식이 없을 경우 '-'로 전달

	tree->parent = tree->root->left;
	linked_tree_add(tree, 'B', 'D', '-');

	tree->parent = tree->root->right;
	linked_tree_add(tree, 'C', '-', 'E');

	// 트리 출력
	// 출력할 서브 트리의 부모노드를 수동으로 지정

	printf("Linked Binary Tree\n");
	// 부모노드를 루트로 이동
	tree->parent = tree->root;
	linked_tree_display(tree->parent);
	// 왼쪽 자식의 서브 트리
	linked_tree_display(tree->parent->left);
	// 오른쪽 자식의 서브 트리
	linked_tree_display(tree->parent->right);
	
	return 0;
}