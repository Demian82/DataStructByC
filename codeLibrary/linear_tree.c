#include <stdio.h>
#include <malloc.h>
#define MAX_NODE 32 // 5레벨 트리
// 레벨에 따른 최대 노드 수 구하기
// 4레벨 : 2^4 - 1 = 15
// 

//

// 왼쪽 자식(LC), 오른쪽 자식(RC)
// 트리의 인덱스 부여
// 순서는 왼쪽에서 오른쪽으로, 위에서 아래로 부여함 : 레벨 순회
// 0번은 사용하지 않음

// 부모 인덱스로 자식을 구하는 방법
// 부모(P) : index
// 왼쪽 자식(LC) : index * 2
// 오른쪽 자식(RC) : ( index * 2 ) + 1

// 자식 index를 이용하여 부모(P)를 구하는 방법
// 
// 부모(P) : index / 2

typedef struct treeType {
	char data[MAX_NODE];
	int parent; // 서브트리의 부모노드 인덱스
} treeType;

void linear_tree_display(treeType* tree)
{
	// 트리 출력 : 배열을 출력
	// 루트부터 현재 마지막 노드까지 차례로 출력
	// [A, B, C, D, -, -, E]

	printf("Linear Tree = [");
	for (int index = 0; index <= tree->parent * 2 + 1; index++) {
		printf("%c", tree->data[index]);
		if (index != tree->parent * 2 + 1) {
			printf(", ");
		}
	}
	printf("]\n");

	// 서브트리를 문자열로 표현
	// P:A -> LC:B, RC:C
	// P:B -> LC:D, RC:-
	// P:C -> LC:-, RC:E
	for (int index = 1; index < MAX_NODE; index++) {
		if (tree->data[index] != '-') {
			printf("P:%c -> LC:%c, RC:%c\n",
				tree->data[index], tree->data[index * 2], tree->data[index * 2 + 1]);
		}
	}
}

treeType* linear_tree_init(void)
{
	// 메모리 공간 할당 및 초기화
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	// 트리의 초기화 : '-'
	for (int index = 0; index < MAX_NODE; index++) {
		tree->data[index] = '-';
	}
	tree->parent = 0;
	return tree;
}

void linear_tree_add(treeType* tree, char pitem, char litem, char ritem)
{
	// 현재 부모노드의 서브트리에 부모, 왼쪽, 오른쪽 자식을 추가
	// P:index, LR:index*2; RC:index*2+1
	tree->data[tree->parent] = pitem;
	tree->data[tree->parent * 2] = litem;
	tree->data[tree->parent * 2 + 1] = ritem;
}

void linear_tree_menu(treeType* tree)
{
	int menu;
	char pitem, litem, ritem;
	while (1) {
		printf("Linear Tree 1.Add, 2.Display, 3.Exit\n");
		printf("Input the menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			tree->parent++;

			// 첫 노드일 경우 루트만 입력
			if (tree->parent == 1) {
				printf("Input Root ? ");
				scanf_s("\n%c", &tree->data[tree->parent], 1);
			}

			// 루트만 입력되면 부모노드는 자동으로 결정
			pitem = tree->data[tree->parent];


			// 서브트리의 부모노드가 없을 경우 (-)
			while (pitem == '-') {
				tree->parent++;
				pitem = tree->data[tree->parent];
			}

			printf("Input Parent : ");
			scanf_s("\n%c", &pitem, 1);
			
			printf("Input Left Child : ");
			scanf_s("\n%c", &litem, 1);
			
			printf("Input Right Child : ");
			scanf_s("\n%c", &ritem, 1);
			
			linear_tree_add(tree, pitem, litem, ritem);
		}
		else if (menu == 2)
		{
			linear_tree_display(tree);
		}
		else if (menu == 3)
		{
			break;
		}
		else
		{
			printf("MENU ERROR\n");
		}
		printf("\n");
	}
}

int main() {
	// 배열을 사용한 이진 트리의 구현
	treeType* tree = linear_tree_init();
	linear_tree_menu(tree);

	free(tree);

	return 0;
}