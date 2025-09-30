#include <stdio.h>

// 함수는 자기 자신의 영역이 존재
// 데이터를 전달받기 위해 매개 변수(parameter)를 정의

int get_area(int w, int h)
{
	int area;
	area = w * h;
	printf("사각형 면적 : %d\n", area);
	// 결과를 main으로 되돌려줌
	return area;
}

void main(void)
{
	// 사각형 면적 구하기
	int width = 10;
	int height = 20;
	int area; // 면적

	// 데이터(인수)를 함수로 전달
	area = get_area(width, height);

	printf("사각형 면적 : %d\n", area);

}