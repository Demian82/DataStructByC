// 연결 리스트를 사용한 다항식(Polynomial)의 표현
// 계수(coefficient)와 지수(exponent)를 사용하여 노드를 구성
// f(x) = 4x^3 + 3x^2 + 5x^1

#include <stdio.h>
#include <malloc.h>
#include <math.h>

// 다항식 항을 나타내는 노드
typedef struct node {
	int coef;  // 계수(coefficient)
	int expo;  // 지수(exponent)
	struct node* link;  // 다음 항을 가리키는 링크
} node;

// 다항식 헤더 노드
typedef struct polyType {
	int length;  // 다항식 항의 개수
	node* head;  // 다항식의 첫 번째 항을 가리키는 헤더
} polyType;

// 다항식을 연산
int poly_list_compute(polyType* poly, int x)
{
	int result = 0;
	node* nptr = poly->head;

	// 첫 번째 항부터 차례로 연산 후 누적합
	while (nptr != NULL) {
		// pow() : C언어의 거듭제곱 구하는 함수
		result += nptr->coef * (int)pow(x, nptr->expo);
		nptr = nptr->link;
	}
	return result;
}

// 현재 다항식 리스트를 다항식 표현 식으로 출력
// f(x) = 4x^3 + 3x^2 + 5x^1
void poly_list_display(polyType* poly)
{
	node* nptr = poly->head;
	printf("Polynomial Expression : f(x) = ");
	
	// 항이 존재하지 않을 경우
	if (nptr == NULL) {
		printf("None");
	}

	// 항이 존재할 경우 마지막 항까지 차례로 이동하여 출력
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

// 현재 다항식의 마지막에 새로운 항을 추가
void poly_list_insert(polyType* poly, int coef, int expo)
{
	node* newNode = NULL;
	node* nptr = NULL;

	// 새로운 노드를 생성 후 초기화
	newNode = (node*)malloc(sizeof(node));
	newNode->coef = coef;
	newNode->expo = expo;
	newNode->link = NULL;

	// 노드가 존재하지 않을 경우
	if (poly->head == NULL) {
		poly->head = newNode;
	}
	// 1개 이상의 노드가 존재할 경우
	else {
		nptr = poly->head;
		// 마지막 노드로 이동
		while (nptr->link != NULL) { // 다음 노드가 있을 경우
			nptr = nptr->link;
		}
		// 마지막 노드로 삽입
		nptr->link = newNode;
	}
	poly->length++;
}

// 다항식에서 한 개의 항을 생성
void poly_list_make(polyType* poly)
{
	int coef, expo;
	int answer = 1;

	while (answer == 1) {
		// 계수와 지수를 입력 받음
		printf("Coefficient ? ");
		scanf_s("%d", &coef);
		printf("Exponent ? ");
		scanf_s("%d", &expo);
		// 다항식에 항을 추가
		poly_list_insert(poly, coef, expo);
		// 항을 계속 만들지 판단
		printf("Continue making the term (1/0) ? ");
		scanf_s("%d", &answer);
		if (answer == 0) break;
	}
}

// 다항식 리스트 초기화
void poly_list_free(polyType* poly)
{
	// 첫 번째 노드에서 부터 마지막 노드까지 탐색
	// 항을 하나씩 삭제
	node* nptr = poly->head;
	while (nptr != NULL) {
		poly->head = poly->head->link; // 다음 노드로 이동
		free(nptr);
		nptr = poly->head;
	}
	poly->length = 0;
}

polyType* poly_list_init(void)
{
	// 다항식 리스트 초기화
	polyType* poly = (polyType*)malloc(sizeof(polyType));
	poly->length = 0;
	poly->head = NULL;
	return poly;
}

// 두 개의 다항식을 전달받아 합친 다항식 만들기
polyType* poly_list_add(polyType* poly1, polyType* poly2)
{
	polyType* totPoly = poly_list_init();  // 합쳐진 다항식 초기화
	node* nptr1 = poly1->head;
	node* nptr2 = poly2->head;

	// 두 개의 다항식 중 하나가 탐색을 끝날 때까지
	while (nptr1 && nptr2) {
		// 지수가 같은 항은 계수를 더해서 항을 생성
		if (nptr1->expo == nptr2->expo) {
			poly_list_insert(totPoly, nptr1->coef + nptr2->coef, nptr1->expo);
			// 둘다 다음 항으로 이동
			nptr1 = nptr1->link;
			nptr2 = nptr2->link;
		}
		// 지수가 큰 항은 그대로 연결
		else if (nptr1->expo > nptr2->expo) {
			poly_list_insert(totPoly, nptr1->coef, nptr1->expo);
			nptr1 = nptr1->link;
		}
		else if (nptr1->expo < nptr2->expo) {
			poly_list_insert(totPoly, nptr2->coef, nptr2->expo);
			nptr2 = nptr2->link;
		}
	}

	// poly1 다항식이 남아있는 경우 나머지 항을 add에 모두 연결
	while (nptr1 != NULL) {
		poly_list_insert(totPoly, nptr1->coef, nptr1->expo);
		nptr1 = nptr1->link;
	}

	// poly2 다항식이 남아있는 경우 나머지 항을 add에 모두 연결
	while (nptr2 != NULL) {
		poly_list_insert(totPoly, nptr2->coef, nptr2->expo);
		nptr2 = nptr2->link;
	}

	return totPoly;  // 합친 다항식을 반환
}

void poly_list_total(void)
{
	polyType* totPoly = NULL;  // 총 합친 다항식
	polyType* addPoly = NULL;  // 현재까지 합친 다항식
	polyType* newPoly = poly_list_init();  // 현재 다항식
	int answer;

	while (1) {
		poly_list_free(newPoly);  // 다항식 초기화
		poly_list_make(newPoly);  // 다항식 생성

		// 처음 다항식을 합친 경우
		if (totPoly == NULL) {
			addPoly = poly_list_init();
		}
		// 기존에 합친 다항식이 있을 경우
		else {
			poly_list_free(addPoly);
			free(addPoly);
			addPoly = totPoly;
		}

		// 두 다항식을 합치고 출력
		totPoly = poly_list_add(newPoly, addPoly);
		poly_list_display(newPoly);  // 현재 다항식
		poly_list_display(addPoly);  // 현재까지 합친 다항식
		poly_list_display(totPoly);  // 새롭게 합친 총 다항식

		// 새로운 다항식을 생성하여 합칠지 판단
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
	polyType* totPoly = NULL;   // 총 합친 다항식
	polyType* addPoly = NULL;   // 현재까지 합친 다항식

	while (1) {
		printf("\nPolynomial 1.Make, 2.Display, 3.Compute, 4.Polynomial Add, 5.Exit\n");
		printf("Input the Menu : ");
		scanf_s("%d", &menu);

		// 다항식 만들기
		if (menu == 1) {
			// 현재 다항식을 초기화하고 새로운 다항식을 생성
			poly_list_free(poly);
			poly_list_make(poly);
		}

		// 다항식을 표현식으로 출력
		else if (menu == 2) {
			poly_list_display(poly);
		}

		// 다항식의 지수에 값을 대입하여 다항식의 결과 출력
		else if (menu == 3) {
			// 다항식이 존재할 경우
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

		// 두 개의 다항식을 합치기
		else if (menu == 4) {
			// poly_list_total();
			
			// 1번 메뉴를 사용하여 추가할 경우
			// 처음 다항식을 합친 경우
			if (totPoly == NULL) {
				addPoly = poly_list_init();
			}
			// 기존에 합친 다항식이 있을 경우
			else {
				poly_list_free(addPoly);
				free(addPoly);
				addPoly = totPoly;
			}

			// 두 다항식을 합치고 출력
			totPoly = poly_list_add(poly, addPoly);
			poly_list_display(poly);     // 현재 다항식
			poly_list_display(addPoly);  // 현재까지 합친 다항식
			poly_list_display(totPoly);  // 새롭게 합친 총 다항식
		}

		// 다항식 리스트를 초기화하고 종료
		else if (menu == 5) {
			poly_list_free(poly);
			poly_list_display(poly);
			// 합친 다항식이 없을 경우 메모리를 해제할 필요가 없음
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