#include <stdio.h>
#include <malloc.h>
#include "shape.h"


int main(void)
{
	// 도형의 면적 구하기 : 삼각형, 사각형, 원
	// 프로그램의 설계 : 입력과 출력을 명확
	// 입력 메뉴화 -> 기능별 함수를 구현 -> 관련 자료의 구조화(자료구조)
	//shape my;
	shape* pmy = shape_init_area();
	shape_menu_area(pmy);
	free(pmy);

	return 0;
}