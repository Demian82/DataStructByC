#include <stdio.h>

// 사각형 면적 구하기
// C언어는 함수의 나열이다

// main()는 c언어의 시작점(진입)
// 

// vodi : 전달하는 데이터가 없음, 반환하는 데이터가 없음
// 함수에서 매개변수로 주소를 전달받음 -> 포인터를 사용

struct square
{
	int width;
	int height;
	int area; // 면적
};

void get_area(struct square* pmy)
{
	pmy->area = pmy->width * pmy->height;
	// 결과를 main()으로 반환
}

int main(void)
{
	// 구조체를 사용하여 데이터를 묶음 : 새로운 자료형
	struct square my;
	my.width = 10;
	my.height = 3;


	get_area(&my); // 함수 호출, 데이터를 전달
	// 함수로부터 값을 반환 받음
	
	printf("사각형 면적 : %d\n", my.area); // 30
	return 0;
}
