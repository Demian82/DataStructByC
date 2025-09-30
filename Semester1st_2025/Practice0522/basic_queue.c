#include <stdio.h>
#define MAX_SIZE 5

// 배열을 사용한 큐(Queue)
// FIFO (First In First Out)
int main(void)
{
	int data[MAX_SIZE];
	int front; // 삭제 위치(인덱스)
	int rear; // 삽입 위치(인덱스)
	int index;
	int delitem;

	// 큐의 초기화 (큐가 비어있음)
	front = -1;
	rear = -1;

	// 큐에 10, 20, 30 삽입
	rear++;
	data[rear] = 10;
	rear++;
	data[rear] = 20;
	rear++;
	data[rear] = 30;

	// 큐에서 항목을 삭제
	front++;
	delitem = data[front];
	printf("Delete Itme : %d\n", delitem);


	// 큐 출력
	// rear는 항상 마지막 항목의 위치
	// front는 첫번째 항목의 앞에 위치
	printf("Linear Queue = [");
	for (index = front+1; index <= rear; index++)
	{
		printf("%d", data[index]);
		if (index != rear) // 마지막이 아니라면
			printf(", "); // 콤마를 삽입
	}
	printf("]\n");


	return 0;
}