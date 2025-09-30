#include <stdio.h>
#include <malloc.h>

void test1(void)
{
	// 배열(array)
	// 여러 개의 데이터를 담기 위한 구조
	// 메모리 공간을 연속으로 할당
	// 할당받은 공간의 위치(index)가 필요
	// 인덱스는 0부터 시작
	// 데이터는 같은 종류여야 함
	int a[5] = { 10, 20, 30, 40, 50 }; // 20byte
	int length;

	printf("%d\n", a[2]); // 30
	// 메모리 크기
	printf("size = %d\n", sizeof(a));

	// 배열의 개수
	length = sizeof(a) / sizeof(a[0]); // 20 / 4 -> 5
	printf("%d\n", length);

	// 마지막 요소
	printf("%d\n", a[length - 1]); //50

}

void test2(void)
{
	int a[] = { 10, 20, 30, 40, 50 };
	// 배열 이름의 정체 : 배열의 시작 주소
	printf("%p, %p\n", &a[0], a);
	printf("%p, %p\n", &a[1], a+1);
	// 주소에 1을 더하면 -> 할당받능 크기만큼 증가함

	// 배열 이름은 포인터로 사용할 수 있다.
	printf("%d, %d\n", a[0], *(a+0)); // 10
	printf("%d, %d\n", a[1], *(a+1)); // 20
	// 결론 : a[i] -> *(a+i)

}

void test3(void)
{
	int a[] = { 10, 20, 30, 40, 50 };
	int* pa = a; // 배열의 이름을 포인터의 초기값

	// 포인터를 배열처럼 사용 가능
	printf("%d, %d\n", *pa, *(pa+0)); // 10
	printf("%d, %d\n", *pa, *(pa + 1)); // 10, 20
}

void test4(void)
{
	// 동적 배열 : 동적 메모리 공간 할당 : malloc()
	int* p = (int*)malloc(20);
	p[0] = 10; // *(p + 0) = 10;
	p[1] = 20; // *(p + 1) = 10;
}

void test5(void)
{
	// 문자열 : "hello"
	// c언어는 문자열을 담기위한 데이터 타입이 없음
	char message[] = "hello"; // { 'h', 'e', 'l', 'l', 'o', '\0' };
	char* pm = "korea";
	// char* 로 문자열 정의가 가능

	printf("%s\n", message);
	// %s : 문자열 출력 포맷
	// 시작주소에서 1vyte씩 읽어서 문자로 출력하라
	// 단, null문자('\0')를 만날 때까지
	// 문자열에는 반드시 끝에 null이 포함
	printf("%d\n", sizeof(message));
	printf("%d\n", strlen(message)); // 문자열 길이
	printf("%s\n", pm);
}

int main(void)
{
	test5();
	return 0;
}