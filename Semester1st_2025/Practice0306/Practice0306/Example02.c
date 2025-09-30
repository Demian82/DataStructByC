#include <stdio.h>

void main(void)
{
	// 데이터
	// 문자 : 'A', "hello"
	// 숫자 : 정수, 실수
	// 어떤 데이터를 프로그램에서 사용
	// 데이터는 메모리 공간에 있어야 함
	// 데이터를 위해 메모리 공간을 할당
	// 정수 메모리 공간을 할당 : int (4byte)
	// 실수 메모리 공간을 할당 : double (8byte)
	// 변수 : 메모리 공간을 할당 받고 이름을 붙인 것
	int number1 = 10;
	int number2 = 20;
	int add = number1 + number2;
	printf("add = %d\n", add);
	// %d : 정수 포맷
}