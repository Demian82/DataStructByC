// ���� ����Ʈ�� ����� ���׽�(Polynomial)�� ǥ��
// ���(coefficient)�� ����(exponent)�� ����Ͽ� ��带 ����
// f(x) = 4x^3 + 3x^2 + 5x^1

#include <stdio.h>
#include <malloc.h>
#include <math.h>

// ���׽� ���� ��Ÿ���� ���
typedef struct node {
	int coef;  // ���(coefficient)
	int expo;  // ����(exponent)
	struct node* link;  // ���� ���� ����Ű�� ��ũ
} node;

// ���׽� ��� ���
typedef struct polyType {
	int length;  // ���׽� ���� ����
	node* head;  // ���׽��� ù ��° ���� ����Ű�� ���
} polyType;

// ���׽��� ����
int poly_list_compute(polyType* poly, int x)
{
	int result = 0;
	node* nptr = poly->head;

	// ù ��° �׺��� ���ʷ� ���� �� ������
	while (nptr != NULL) {
		// pow() : C����� �ŵ����� ���ϴ� �Լ�
		result += nptr->coef * (int)pow(x, nptr->expo);
		nptr = nptr->link;
	}
	return result;
}

// ���� ���׽� ����Ʈ�� ���׽� ǥ�� ������ ���
// f(x) = 4x^3 + 3x^2 + 5x^1
void poly_list_display(polyType* poly)
{
	node* nptr = poly->head;
	printf("Polynomial Expression : f(x) = ");
	
	// ���� �������� ���� ���
	if (nptr == NULL) {
		printf("None");
	}

	// ���� ������ ��� ������ �ױ��� ���ʷ� �̵��Ͽ� ���
	while (nptr != NULL) {
		printf("%dx^", nptr->coef);
		printf("%d", nptr->expo);
		nptr = nptr->link;
		if (nptr != NULL) {
			printf(" + ");
		}
	}
	printf("\n");
}

// ���� ���׽��� �������� ���ο� ���� �߰�
void poly_list_insert(polyType* poly, int coef, int expo)
{
	node* newNode = NULL;
	node* nptr = NULL;

	// ���ο� ��带 ���� �� �ʱ�ȭ
	newNode = (node*)malloc(sizeof(node));
	newNode->coef = coef;
	newNode->expo = expo;
	newNode->link = NULL;

	// ��尡 �������� ���� ���
	if (poly->head == NULL) {
		poly->head = newNode;
	}
	// 1�� �̻��� ��尡 ������ ���
	else {
		nptr = poly->head;
		// ������ ���� �̵�
		while (nptr->link != NULL) { // ���� ��尡 ���� ���
			nptr = nptr->link;
		}
		// ������ ���� ����
		nptr->link = newNode;
	}
	poly->length++;
}

// ���׽Ŀ��� �� ���� ���� ����
void poly_list_make(polyType* poly)
{
	int coef, expo;
	int answer = 1;

	while (answer == 1) {
		// ����� ������ �Է� ����
		printf("Coefficient ? ");
		scanf_s("%d", &coef);
		printf("Exponent ? ");
		scanf_s("%d", &expo);
		// ���׽Ŀ� ���� �߰�
		poly_list_insert(poly, coef, expo);
		// ���� ��� ������ �Ǵ�
		printf("Continue making the term (1/0) ? ");
		scanf_s("%d", &answer);
		if (answer == 0) break;
	}
}

// ���׽� ����Ʈ �ʱ�ȭ
void poly_list_free(polyType* poly)
{
	// ù ��° ��忡�� ���� ������ ������ Ž��
	// ���� �ϳ��� ����
	node* nptr = poly->head;
	while (nptr != NULL) {
		poly->head = poly->head->link; // ���� ���� �̵�
		free(nptr);
		nptr = poly->head;
	}
	poly->length = 0;
}

polyType* poly_list_init(void)
{
	// ���׽� ����Ʈ �ʱ�ȭ
	polyType* poly = (polyType*)malloc(sizeof(polyType));
	poly->length = 0;
	poly->head = NULL;
	return poly;
}

// �� ���� ���׽��� ���޹޾� ��ģ ���׽� �����
polyType* poly_list_add(polyType* poly1, polyType* poly2)
{
	polyType* totPoly = poly_list_init();  // ������ ���׽� �ʱ�ȭ
	node* nptr1 = poly1->head;
	node* nptr2 = poly2->head;

	// �� ���� ���׽� �� �ϳ��� Ž���� ���� ������
	while (nptr1 && nptr2) {
		// ������ ���� ���� ����� ���ؼ� ���� ����
		if (nptr1->expo == nptr2->expo) {
			poly_list_insert(totPoly, nptr1->coef + nptr2->coef, nptr1->expo);
			// �Ѵ� ���� ������ �̵�
			nptr1 = nptr1->link;
			nptr2 = nptr2->link;
		}
		// ������ ū ���� �״�� ����
		else if (nptr1->expo > nptr2->expo) {
			poly_list_insert(totPoly, nptr1->coef, nptr1->expo);
			nptr1 = nptr1->link;
		}
		else if (nptr1->expo < nptr2->expo) {
			poly_list_insert(totPoly, nptr2->coef, nptr2->expo);
			nptr2 = nptr2->link;
		}
	}

	// poly1 ���׽��� �����ִ� ��� ������ ���� add�� ��� ����
	while (nptr1 != NULL) {
		poly_list_insert(totPoly, nptr1->coef, nptr1->expo);
		nptr1 = nptr1->link;
	}

	// poly2 ���׽��� �����ִ� ��� ������ ���� add�� ��� ����
	while (nptr2 != NULL) {
		poly_list_insert(totPoly, nptr2->coef, nptr2->expo);
		nptr2 = nptr2->link;
	}

	return totPoly;  // ��ģ ���׽��� ��ȯ
}

void poly_list_total(void)
{
	polyType* totPoly = NULL;  // �� ��ģ ���׽�
	polyType* addPoly = NULL;  // ������� ��ģ ���׽�
	polyType* newPoly = poly_list_init();  // ���� ���׽�
	int answer;

	while (1) {
		poly_list_free(newPoly);  // ���׽� �ʱ�ȭ
		poly_list_make(newPoly);  // ���׽� ����

		// ó�� ���׽��� ��ģ ���
		if (totPoly == NULL) {
			addPoly = poly_list_init();
		}
		// ������ ��ģ ���׽��� ���� ���
		else {
			poly_list_free(addPoly);
			free(addPoly);
			addPoly = totPoly;
		}

		// �� ���׽��� ��ġ�� ���
		totPoly = poly_list_add(newPoly, addPoly);
		poly_list_display(newPoly);  // ���� ���׽�
		poly_list_display(addPoly);  // ������� ��ģ ���׽�
		poly_list_display(totPoly);  // ���Ӱ� ��ģ �� ���׽�

		// ���ο� ���׽��� �����Ͽ� ��ĥ�� �Ǵ�
		printf("Continue adding the Polynomial (1/0) ? ");
		scanf_s("%d", &answer);
		if (answer == 0)
			break;
	}

	poly_list_free(totPoly);
	poly_list_free(addPoly);
	poly_list_free(newPoly);
	free(totPoly);
	free(addPoly);
	free(newPoly);
}

void poly_list_menu(polyType* poly)
{
	int menu, x, result;
	polyType* totPoly = NULL;   // �� ��ģ ���׽�
	polyType* addPoly = NULL;   // ������� ��ģ ���׽�

	while (1) {
		printf("\nPolynomial 1.Make, 2.Display, 3.Compute, 4.Polynomial Add, 5.Exit\n");
		printf("Input the Menu : ");
		scanf_s("%d", &menu);

		// ���׽� �����
		if (menu == 1) {
			// ���� ���׽��� �ʱ�ȭ�ϰ� ���ο� ���׽��� ����
			poly_list_free(poly);
			poly_list_make(poly);
		}

		// ���׽��� ǥ�������� ���
		else if (menu == 2) {
			poly_list_display(poly);
		}

		// ���׽��� ������ ���� �����Ͽ� ���׽��� ��� ���
		else if (menu == 3) {
			// ���׽��� ������ ���
			if (poly->head != NULL) {
				printf("Value of X ? ");
				scanf_s("%d", &x);
				result = poly_list_compute(poly, x);
				printf("Result : %d\n", result);
			}
			else {
				printf("Polynomial not Exist\n");
			}
		}

		// �� ���� ���׽��� ��ġ��
		else if (menu == 4) {
			// poly_list_total();
			
			// 1�� �޴��� ����Ͽ� �߰��� ���
			// ó�� ���׽��� ��ģ ���
			if (totPoly == NULL) {
				addPoly = poly_list_init();
			}
			// ������ ��ģ ���׽��� ���� ���
			else {
				poly_list_free(addPoly);
				free(addPoly);
				addPoly = totPoly;
			}

			// �� ���׽��� ��ġ�� ���
			totPoly = poly_list_add(poly, addPoly);
			poly_list_display(poly);     // ���� ���׽�
			poly_list_display(addPoly);  // ������� ��ģ ���׽�
			poly_list_display(totPoly);  // ���Ӱ� ��ģ �� ���׽�
		}

		// ���׽� ����Ʈ�� �ʱ�ȭ�ϰ� ����
		else if (menu == 5) {
			poly_list_free(poly);
			poly_list_display(poly);
			// ��ģ ���׽��� ���� ��� �޸𸮸� ������ �ʿ䰡 ����
			if (totPoly != NULL)
				poly_list_free(totPoly);
			if (addPoly != NULL)
				poly_list_free(addPoly);
			printf("Exit\n");
			break;
		}
		else {
			printf("Menu Error\n");
		}
	}
}

int main(void)
{
	polyType* poly = poly_list_init();
	poly_list_menu(poly);
	free(poly);
	return 0;
}