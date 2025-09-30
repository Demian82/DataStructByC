#include <stdio.h>

typedef struct grade {
	int* score;
	int length;
	int total;
} grade;

void get_total(grade* pmy)
{
	int index;
	pmy->total = 0;
	for (index = 0; index < pmy->length; index++) {
		pmy->total += pmy->score[index];
	}
}
int main(void)
{
	grade my;
	int s[] = { 10, 20, 30 };
	my.score = s;
	my.length = sizeof(s) / sizeof(s[0]);

	get_total(&my);
	printf("%d\n", my.total);


	return 0;
}