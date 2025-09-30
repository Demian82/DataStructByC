#include <stdio.h>
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

int main() {
	// �迭�� ����� ���� Ʈ���� ����
	char data[MAX_NODE];
	
	int parent = 0; // ����Ʈ���� �θ��� �ε���

	// Ʈ���� �ʱ�ȭ : '-'
	for (int index = 0; index < MAX_NODE; index++) {
		data[index] = '-';
	}

	// Ʈ���� ���� ���
	// ����Ʈ���� �������� �θ��� ����
	
	// ��Ʈ ��� : �ֻ��� ���
	parent++;
	data[parent] = 'A';
	data[parent * 2] = 'B'; // LC
	data[parent * 2 + 1] = 'C'; // RC

	// �� ��° ����Ʈ���� �̵� : �ڽĸ� ����
	parent++;
	data[parent * 2] = 'D'; // LC
	data[parent * 2 + 1] = '-'; // RC �ڽ��� ����

	// �� ��° ����Ʈ���� �̵� : �ڽĸ� ����
	parent++;
	data[parent * 2] = '-'; // LC �ڽ��� ����
	data[parent * 2 + 1] = 'E'; // RC

	// Ʈ�� ��� : �迭�� ���
	// ��Ʈ���� ���� ������ ������ ���ʷ� ���
	// [A, B, C, D, -, -, E]

	printf("Linear Tree = [");
	for (int index = 0; index <= parent * 2 + 1; index++) {
		printf("%c", data[index]);
		if (index != parent * 2 + 1) {
			printf(", ");
		}
	}
	printf("]\n");

	// ����Ʈ���� ���ڿ��� ǥ��
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