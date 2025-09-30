#include <stdio.h>
// c언어는 함수의 나열이다
// C프로그램의 진입점(시작)
void main(void)
{
	// 변수(variable)
	// 데이터는 메모리 공간에 존재해야 처리할 수 있다.
	int a = 66; // 정수(4byte)
	double b = 3.1415; // 실수(8byte)
	char c = 'A'; // 문자(1byte)

	//정수의 데이터를 출력하는 방법
	printf("a = %d\n", a);
	printf("b = %.1f\n", b);
	printf("c = %c\n", c); // A
	printf("c = %d\n", c); // 65
	printf("a = %c\n", a);

	// 함수의 종류
	// 사용자 정의 함수
	// 라이브러리 함수
	printf("hello\n");

}
