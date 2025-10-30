#include <stdio.h>

// 재귀 호출(Recursive Call)
// 재귀 호출은 함수 내부에서 자기 자신의 함수를 다시 호출하는 것
// 함수 안에서 중단하는 코드를 반드시 작성
// 특별한 문제에서 재귀 함수를 호출하면 복잡한 문제를 간단하게 표현할 수 있는 방법 제공
// 자칫 잘못 사용하면 오버헤드 발생가능

int recursive_add(int number)
{
	int total;
	if (number == 1)
		return 1;
	else {
		total = number + recursive_add(number - 1);
		printf("%d\n", total);
		return total;
	}
}

int recursive_factorial(int number)
{
	// 5*4*3*2*1 -> 5!
	if (number == 1)
		return 1;
	else {
		return number * recursive_factorial(number - 1);
	}
}

void recursive_binary(int number)
{
	// 10진수를 2진수로 변환
	// 2로 나눈 몫 계속 재귀 호출
	if (number == 0)
		return;
	else {
		recursive_binary(number / 2); // 몫을 인수로 전달
		printf("%d", number % 2);
	}
}

int main(void)
{
	int answer;
	recursive_add(5);
	answer = recursive_factorial(5);
	printf("%d\n", answer);

	recursive_binary(127);

	return 0;
}