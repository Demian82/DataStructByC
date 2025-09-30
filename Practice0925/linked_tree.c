#include <stdio.h>
#include <malloc.h>

typedef struct tnode {
	char data;
	struct tnode* left; // ¿ÞÂÊ ÀÚ½Ä
	struct tnode* right; // ¿À¸¥ÂÊ ÀÚ½Ä
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

	/* TOP->DOWN ¹æ½Ä
	// ·çÆ® ³ëµå »ý¼º
	// TOP-down ¹æ½Ä
	// ·çÆ®¸¦ ¸¸µé°í ºÎ¸ð¸¦ ¸¸µé°í ÀÚ½ÄÀ» ¸¸µå´Â °úÁ¤
	node1 = (tnode*)malloc(sizeof(tnode));
	node1->data = 'A';
	node1->left = NULL;
	node1->right = NULL;
	// ÇöÀç ³ëµå¸¦ ·çÆ® ³ëµå·Î ÁöÁ¤
	tree->root = node1;

	// ¿ÞÂÊ ÀÚ½Ä
	// ¼­ºêÆ®¸®ÀÇ ºÎ¸ð³ëµå¸¦ ÁöÁ¤
	tree->parent = tree->root;
	node2 = (tnode*)malloc(sizeof(tnode));
	node2->data = 'B';
	node2->left = NULL;
	node2->right = NULL;
	// ÇöÀç ³ëµå¸¦ ºÎ¸ðÀÇ ¿ÞÂÊ ÀÚ½ÄÀ¸·Î ¿¬°á
	tree->parent->left = node2;

	// ¿À¸¥ÂÊ ÀÚ½Ä
	// ¼­ºêÆ®¸®ÀÇ ºÎ¸ð³ëµå¸¦ ÁöÁ¤
	node3 = (tnode*)malloc(sizeof(tnode));
	node3->data = 'C';
	node3->left = NULL;
	node3->right = NULL;
	// ÇöÀç ³ëµå¸¦ ºÎ¸ðÀÇ ¿À¸¥ÂÊ ÀÚ½ÄÀ¸·Î ¿¬°á
	tree->parent->right = node3;

	// ºÎ¸ð³ëµå B·Î ÀÌµ¿
	tree->parent = tree->root->left;

	// BÀÇ ¿ÞÂÊ ÀÚ½Ä
	node4 = (tnode*)malloc(sizeof(tnode));
	node4->data = 'D';
	node4->left = NULL;
	node4->right = NULL;
	// ÇöÀç ³ëµå¸¦ ºÎ¸ðÀÇ ¿À¸¥ÂÊ ÀÚ½ÄÀ¸·Î ¿¬°á
	tree->parent->left = node4;
	// BÀÇ ¿À¸¥ÂÊÀº ¾øÀ½

	// ºÎ¸ð³ëµå C·Î ÀÌµ¿
	tree->parent = tree->root->right;

	// CÀÇ ¿À¸¥ÂÊ ÀÚ½Ä
	node5 = (tnode*)malloc(sizeof(tnode));
	node5->data = 'E';
	node5->left = NULL;
	node5->right = NULL;
	// ÇöÀç ³ëµå¸¦ ºÎ¸ðÀÇ ¿À¸¥ÂÊ ÀÚ½ÄÀ¸·Î ¿¬°á
	tree->parent->right = node5;
	// CÀÇ ¿ÞÂÊÀº ¾øÀ½
	*/


	// Bottom-Up ¹æ½Ä : ÀÚ½ÄÀ» ¸ÕÀú ¸¸µé°í ¸¶Áö¸·¿¡ ·çÆ®
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

	// ·çÆ® ³ëµå
	node1 = (tnode*)malloc(sizeof(tnode));
	node1->data = 'A';
	node1->left = node2;
	node1->right = node3;

	// ·çÆ® ³ëµå ÁöÁ¤
	tree->root = node1;

	// Æ®¸® ­ˆ·Â
	// ¼­ºê Æ®¸® ´ÜÀ§·Î Ãâ·Â
	// P:A -> LC:B, RC:C
	// P:B -> LC:D, RC:-
	// P:C -> LC:-, RC:E

	// ºÎ¸ð³ëµå¸¦ ·çÆ®·Î ÀÌµ¿
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