#include <stdio.h>
#include <malloc.h>

typedef struct student {
	char* name; // 이름
	int* score; // 배열(점수)
	int length; // 점수 개수
	double average;
	int maxscore;
} student;

student* student_init(void)
{
	int score[] = { 90, 80, 70, 60, 50 };
	student* std = (student*)malloc(sizeof(student));
	std->name = "Angela";
	std->score = score; // 배열의 이름 주소, 배열 이름은 포인터로 접근 가능
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
		total += std->score[index]; // 포인터는 배열처럼 사용 가능
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
	printf("이름 : %s\n", std->name);
	printf("평균 : %.1f\n", std->average);
	printf("최대 : %d\n", std->maxscore);

	free(std);
	return 0;
}