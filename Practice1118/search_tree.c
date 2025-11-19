#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left;
	struct tnode* right;
} tnode;

typedef struct treeType {
	tnode* root;
	tnode* parent;
} treeType;

void search_tree_insert(treeType* tree, char item)
{
	// 이진 탐색 트리의 삽입 연산
	// 부모는 왼쪽 자식보다 크다
	// 부모는 오른쪽 자식보다 작다
	// 루트에서부터 차례로 탐색하면서 작으면 왼쪽으로 이동, 크면 오른쪽으로 이동
	// 결국 새로 삽입된 노드는 단말 노드로 생성
	// 동일한 아이템이 없다고 가정

	tnode* newNode = NULL;
	tnode* nptr = NULL;  // 노드 탐색 포인터

	// 루트 노드가 없는 경우
	if (tree->root == NULL) {
		newNode = (tnode*)malloc(sizeof(tnode));
		newNode->data = item;
		newNode->left = NULL;
		newNode->right = NULL;
		tree->root = newNode;
		return;
	}

	// 루트 노드가 있는 경우
	// 루트부터 노드를 탐색 -> 삽입할 위치로 이동
	nptr = tree->root;

	while (nptr) {  // 노드가 존재하지 않을때까지
		// 아이템이 이미 존재하는 경우
		if (item == nptr->data) {
			printf("%c node is Exist\n", item);
			return;
		}

		// nptr이 이동하기 전에 부모노드를 지정
		tree->parent = nptr;

		// 아래로 이동
		if (item < nptr->data)
			nptr = nptr->left;  // 왼쪽 자식으로 이동
		else
			nptr = nptr->right;  // 오른쪽 자식으로 이동
	}

	// 삽입할 위치가 결정되면  새로운 노드를 생성
	newNode = (tnode*)malloc(sizeof(tnode));
	newNode->data = item;
	newNode->left = NULL;
	newNode->right = NULL;

	// 부모노드와 연결
	// 삽입노드가 부모의 왼쪽인지 오른쪽인지 판단
	if (item < tree->parent->data)
		tree->parent->left = newNode;  // 왼쪽 자식으로 연결
	else
		tree->parent->right = newNode;
}

void search_tree_display(tnode* parent)
{
	// 현재 서브트리의 부모와 왼쪽 오른쪽 자식의 정보를 출력
	char pitem, litem, ritem;
	pitem = parent->data;
	if (parent->left)
		litem = parent->left->data;
	else
		litem = '-';
	if (parent->right)
		ritem = parent->right->data;
	else
		ritem = '-';
	printf("P:%c -> LC:%c, RC:%c\n", pitem, litem, ritem);
}

void search_tree_inorder(tnode* parent)
{
	// 재귀 호출 방식으로 순회하는 inorder
	if (parent) {
		search_tree_inorder(parent->left);
		search_tree_display(parent);  // 방문
		search_tree_inorder(parent->right);
	}
}

void search_tree_menu(treeType* tree)
{
	int menu;
	char item;

	while (1) {
		printf("Search Tree 1.Insert, 2.Delete, 3.Search, 4.Display, 5.Exit\n");
		printf("Input the menu : ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			printf("Insert Item ? ");
			scanf_s("\n%c", &item, 1);
			search_tree_insert(tree, item);
		}

		else if (menu == 2) {

		}

		else if (menu == 3) {

		}

		else if (menu == 4) {
			// inorder로 순회 : 오름차순 정렬 효과
			printf("Binary Search Tree In-Order\n");
			if (tree->root) {
				printf("Root is %c\n", tree->root->data);
				search_tree_inorder(tree->root);
			}
			else
				printf("Root is not exits\n");
		}

		else if (menu == 5) {
			break;
		}

		else
			printf("Menu Error\n");

		printf("\n");
	}
}

treeType* search_tree_init(void)
{
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	tree->root = NULL;
	tree->parent = NULL;
	return tree;
}

int main(void)
{
	treeType* tree = search_tree_init();
	search_tree_menu(tree);
	free(tree);
	return 0;
}