#include <stdio.h>
#include <malloc.h>

typedef struct student {
	char* name; // �̸�
	int* score; // �迭(����)
	int length; // ���� ����
	double average;
	int maxscore;
} student;

student* student_init(void)
{
	int score[] = { 90, 80, 70, 60, 50 };
	student* std = (student*)malloc(sizeof(student));
	std->name = "Angela";
	std->score = score; // �迭�� �̸� �ּ�, �迭 �̸��� �����ͷ� ���� ����
	std->length = sizeof(score) / sizeof(score[0]); // 5
	
	return std;
}

void student_compute(student* std)
{
	int total = 0;
	int index;
	std->maxscore = std->score[0];
	for (index = 0; index < std->length; index++)
	{
		total += std->score[index]; // �����ʹ� �迭ó�� ��� ����
	}
	std->average = (double)total / std->length;

	for (index = 1; index < std->length; index++)
	{
		if (std->maxscore < std->score[index])
		{
			std->maxscore = std->score[index];
		}
	}
}

int main(void)
{
	student* std = student_init();
	student_compute(std);
	printf("�̸� : %s\n", std->name);
	printf("��� : %.1f\n", std->average);
	printf("�ִ� : %d\n", std->maxscore);

	free(std);
	return 0;
}