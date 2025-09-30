#include <stdio.h>
#include <malloc.h>

void test1(void)
{
	// 포인터(pointer)
	// 메모리 공간을 가리킴 -> 주소를 이용해서 가리킴
	// 포인터 변수 : 주소를 데이터로 가짐
	// 포인터 변수의 초기값은 상수로 지정할 수 없다
	// int * p, int *p 다 가능
	// 포인터로 사용할 메모리 공간은 사용가능한 영역이어야 함
	// 변수를 정의하면 사용가능한 메모리 공간을 할당
	int a = 10;
	int* p = &a; // & : 주소연산자

	// 포인터로 메모리 공간의 데이터에 접근
	// * 연산자를 사용 : *p

	printf("%d\n", *p); // 직접 접근
	*p = 100;
	printf("%d\n", a);
}

void test2(void)
{
	// 포인터 타입 : 가리키는 공간의 크기
	// int* : 4byte 공간을 가리킴
	// double* : 8byte 공간을 가리킴
	// char* : 1byte 공간을 가리킴

	// 정적 메모리 공간 할당 : 미리 메모리 공간을 할당 (변수정수)
	// 동적 메모리 공간 할당
	// 코드 중간에 원하는 크기로 언제든지 메모리 공간을 할당
	// 함수 : malloc()
	// 반환값 : 주소가 반환

	int* p = (int*)malloc(16);
	*p = 100;
	printf("%d\n", *p);
}

int main(void)
{
	test2();

	return 0; // 관습적으로 정상종료
}