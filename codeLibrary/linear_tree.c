#include <stdio.h>
#include <malloc.h>
#define MAX_NODE 32 // 5���� Ʈ��
// ������ ���� �ִ� ��� �� ���ϱ�
// 4���� : 2^4 - 1 = 15
// 

//

// ���� �ڽ�(LC), ������ �ڽ�(RC)
// Ʈ���� �ε��� �ο�
// ������ ���ʿ��� ����������, ������ �Ʒ��� �ο��� : ���� ��ȸ
// 0���� ������� ����

// �θ� �ε����� �ڽ��� ���ϴ� ���
// �θ�(P) : index
// ���� �ڽ�(LC) : index * 2
// ������ �ڽ�(RC) : ( index * 2 ) + 1

// �ڽ� index�� �̿��Ͽ� �θ�(P)�� ���ϴ� ���
// 
// �θ�(P) : index / 2

typedef struct treeType {
	char data[MAX_NODE];
	int parent; // ����Ʈ���� �θ��� �ε���
} treeType;

void linear_tree_display(treeType* tree)
{
	// Ʈ�� ��� : �迭�� ���
	// ��Ʈ���� ���� ������ ������ ���ʷ� ���
	// [A, B, C, D, -, -, E]

	printf("Linear Tree = [");
	for (int index = 0; index <= tree->parent * 2 + 1; index++) {
		printf("%c", tree->data[index]);
		if (index != tree->parent * 2 + 1) {
			printf(", ");
		}
	}
	printf("]\n");

	// ����Ʈ���� ���ڿ��� ǥ��
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
	// �޸� ���� �Ҵ� �� �ʱ�ȭ
	treeType* tree = (treeType*)malloc(sizeof(treeType));
	// Ʈ���� �ʱ�ȭ : '-'
	for (int index = 0; index < MAX_NODE; index++) {
		tree->data[index] = '-';
	}
	tree->parent = 0;
	return tree;
}

void linear_tree_add(treeType* tree, char pitem, char litem, char ritem)
{
	// ���� �θ����� ����Ʈ���� �θ�, ����, ������ �ڽ��� �߰�
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

			// ù ����� ��� ��Ʈ�� �Է�
			if (tree->parent == 1) {
				printf("Input Root ? ");
				scanf_s("\n%c", &tree->data[tree->parent], 1);
			}

			// ��Ʈ�� �ԷµǸ� �θ���� �ڵ����� ����
			pitem = tree->data[tree->parent];


			// ����Ʈ���� �θ��尡 ���� ��� (-)
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
	// �迭�� ����� ���� Ʈ���� ����
	treeType* tree = linear_tree_init();
	linear_tree_menu(tree);

	free(tree);

	return 0;
}