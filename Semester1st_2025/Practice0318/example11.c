#include <stdio.h>

// 함수는 배열이름을 포인터로 전달받음
int get_total(int* ps, int length)
{
	int total = 0;
	int idx;
	for (idx = 0; idx < length; idx++) {
		total += *(ps + idx);
	}

	return total;
}

void get_max(int* ps, int length)
{
	int index;
	int max = ps[0];
	for (index = 1; index < length; index++) {
		if (max < ps[index])
			max = ps[index];
	}

	printf("최대값 : %d\n", max);
}

int main(void)
{
	int score[] = { 92, 78, 83, 95, 63, 100 };
	int idx;
	int length = sizeof(score) / sizeof(score[0]);
	int total = get_total(score, length);

	// 배열 이름을 함수로 전달, 개수(길이)도 같이 전달

	printf("총합 : %d\n", total);

	get_max(score, length);

	return 0;
}