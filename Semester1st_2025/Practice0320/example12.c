#include <stdio.h>

// 구조체(structure)
// 서로 다른 종류의 데이터를 묶어서 관리하는 방법
// 사용자 자료형을 정의

// 설계도(추상화)
typedef struct sample {
	// 기본 자료형으로 멤버를 구성
	int a;
	double b;
	char c;
} sample;

// typedef struct sample sample;

void test1(void)
{
	struct sample my; // = { 10, 3.14, 'K' };
	// 구조체 변수의 멤버에 접근하는 방법
	// 구조체변수.멤버
	my.a = 10;
	my.b = 3.14;
	my.c = 'K';

	printf("size : %d\n", sizeof(struct sample)); // 24byte

	printf("%d\n", my.a);
	printf("%.1f\n", my.b);

}

void test2(void)
{
	// 자료형의 재정의
	typedef int suji;
	suji a = 10;
	printf("%d\n", a);

}

void test3(void)
{
	sample my = { 100, 12.3, 'C' };
	printf("%d\n", my.a);

}

int main(void)
{
	test3();
	return 0;
}