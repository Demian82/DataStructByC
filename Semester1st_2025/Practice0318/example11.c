#include <stdio.h>

// �Լ��� �迭�̸��� �����ͷ� ���޹���
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

	printf("�ִ밪 : %d\n", max);
}

int main(void)
{
	int score[] = { 92, 78, 83, 95, 63, 100 };
	int idx;
	int length = sizeof(score) / sizeof(score[0]);
	int total = get_total(score, length);

	// �迭 �̸��� �Լ��� ����, ����(����)�� ���� ����

	printf("���� : %d\n", total);

	get_max(score, length);

	return 0;
}