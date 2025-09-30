#include <stdio.h>
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

int main() {
	// 배열을 사용한 이진 트리의 구현
	char data[MAX_NODE];
	
	int parent = 0; // 서브트리의 부모노드 인덱스

	// 트리의 초기화 : '-'
	for (int index = 0; index < MAX_NODE; index++) {
		data[index] = '-';
	}

	// 트리의 구현 방법
	// 서브트리를 기준으로 부모노드 지정
	
	// 루트 노드 : 최상위 노드
	parent++;
	data[parent] = 'A';
	data[parent * 2] = 'B'; // LC
	data[parent * 2 + 1] = 'C'; // RC

	// 두 번째 서브트리로 이동 : 자식만 만듦
	parent++;
	data[parent * 2] = 'D'; // LC
	data[parent * 2 + 1] = '-'; // RC 자식이 없음

	// 세 번째 서브트리로 이동 : 자식만 만듦
	parent++;
	data[parent * 2] = '-'; // LC 자식이 없음
	data[parent * 2 + 1] = 'E'; // RC

	// 트리 출력 : 배열을 출력
	// 루트부터 현재 마지막 노드까지 차례로 출력
	// [A, B, C, D, -, -, E]

	printf("Linear Tree = [");
	for (int index = 0; index <= parent * 2 + 1; index++) {
		printf("%c", data[index]);
		if (index != parent * 2 + 1) {
			printf(", ");
		}
	}
	printf("]\n");

	// 서브트리를 문자열로 표현
	// P:A -> LC:B, RC:C
	// P:B -> LC:D, RC:-
	// P:C -> LC:-, RC:E
	for (int index = 1; index < MAX_NODE; index++) {
		if (data[index] != '-') {
			printf("P:%c -> LC:%c, RC:%c\n",
				data[index], data[index * 2], data[index * 2 + 1]);
		}
	}

	for (int index = 1; index < MAX_NODE; index++) {
		printf("%c", data[index]);
	}

	return 0;
}