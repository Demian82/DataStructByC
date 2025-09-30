#include  <stdio.h>

int main(void)
{
	// 1. 배열을 사용한 리스트의 초기화
	int data[5] = { 10, 20 };
	int length = 2;
	int pos; //위치
	int delItem; // 삭제 값을 지정하기 위한 변수
	int index;

	// 3. 리스트의 마지막에 아이템를 삽입
	data[length] = 30;
	length++; //길이를 1 증가
	// 10, 20, 30

	// 4. 리스트의 맨 앞에 아이템 삽입
	// 현재 항목들을 하나씩 뒤로 이동
	// 뒤에서부터 이동
	for (index = length-1; index >= 0; index--) {
		data[index+1] = data[index];
	}
	data[0] = 40; // 맨 앞에 삽입
	length++;

	// 5. 리스트의 중간에 아이템을 삽입
	// 3번째 자리에 삽입
	pos = 3;
	for (index = length - 1; index >= pos-1; index--) {
		data[index + 1] = data[index];
	}
	data[pos - 1] = 50;
	length++;
	// [40, 10, 50, 20, 30]

	// 6. 리스트의 맨 뒤의 아이템을 삭제
	delItem = data[length - 1]; // 삭제 아이템
	length--; // 개수 감소
	printf("Delete Item : %d\n", delItem);

	// 7. 리스트의 맨 앞의 아이템을 삭제
	delItem = data[0];
	for (index = 0; index < length - 1; index++) {
		data[index] = data[index + 1];
	}
	length--; // 개수 감소
	printf("Delete Item : %d\n", delItem);

	// 8. 리스트의 중간의 아이템을 삭제
	// 2번째(index = 1) 아이템을 삭제
	pos = 2;
	delItem = data[pos - 1];
	for (index = pos-1; index < length - 1; index++) {
		data[index] = data[index + 1];
	}
	length--; // 개수 감소
	printf("Delete Item : %d\n", delItem);


	// 2. 리스트의 탐색 및 출력
	printf("Linear List = [");
	for (index = 0; index < length; index++) {
		printf("%d", data[index]);
		// index가 마지막이 아니라면 ,를 붙여라
		if (index != length - 1)
			printf(", ");
	}
	printf("]\n");


	return 0;
}