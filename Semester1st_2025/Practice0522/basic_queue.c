#include <stdio.h>
#define MAX_SIZE 5

// �迭�� ����� ť(Queue)
// FIFO (First In First Out)
int main(void)
{
	int data[MAX_SIZE];
	int front; // ���� ��ġ(�ε���)
	int rear; // ���� ��ġ(�ε���)
	int index;
	int delitem;

	// ť�� �ʱ�ȭ (ť�� �������)
	front = -1;
	rear = -1;

	// ť�� 10, 20, 30 ����
	rear++;
	data[rear] = 10;
	rear++;
	data[rear] = 20;
	rear++;
	data[rear] = 30;

	// ť���� �׸��� ����
	front++;
	delitem = data[front];
	printf("Delete Itme : %d\n", delitem);


	// ť ���
	// rear�� �׻� ������ �׸��� ��ġ
	// front�� ù��° �׸��� �տ� ��ġ
	printf("Linear Queue = [");
	for (index = front+1; index <= rear; index++)
	{
		printf("%d", data[index]);
		if (index != rear) // �������� �ƴ϶��
			printf(", "); // �޸��� ����
	}
	printf("]\n");


	return 0;
}