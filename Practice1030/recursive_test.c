#include <stdio.h>

// ��� ȣ��(Recursive Call)
// ��� ȣ���� �Լ� ���ο��� �ڱ� �ڽ��� �Լ��� �ٽ� ȣ���ϴ� ��
// �Լ� �ȿ��� �ߴ��ϴ� �ڵ带 �ݵ�� �ۼ�
// Ư���� �������� ��� �Լ��� ȣ���ϸ� ������ ������ �����ϰ� ǥ���� �� �ִ� ��� ����
// ��ĩ �߸� ����ϸ� ������� �߻�����

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
	// 10������ 2������ ��ȯ
	// 2�� ���� �� ��� ��� ȣ��
	if (number == 0)
		return;
	else {
		recursive_binary(number / 2); // ���� �μ��� ����
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