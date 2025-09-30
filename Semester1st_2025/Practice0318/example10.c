#include <stdio.h>
#include <malloc.h>

void test1(void)
{
	// �迭(array)
	// ���� ���� �����͸� ��� ���� ����
	// �޸� ������ �������� �Ҵ�
	// �Ҵ���� ������ ��ġ(index)�� �ʿ�
	// �ε����� 0���� ����
	// �����ʹ� ���� �������� ��
	int a[5] = { 10, 20, 30, 40, 50 }; // 20byte
	int length;

	printf("%d\n", a[2]); // 30
	// �޸� ũ��
	printf("size = %d\n", sizeof(a));

	// �迭�� ����
	length = sizeof(a) / sizeof(a[0]); // 20 / 4 -> 5
	printf("%d\n", length);

	// ������ ���
	printf("%d\n", a[length - 1]); //50

}

void test2(void)
{
	int a[] = { 10, 20, 30, 40, 50 };
	// �迭 �̸��� ��ü : �迭�� ���� �ּ�
	printf("%p, %p\n", &a[0], a);
	printf("%p, %p\n", &a[1], a+1);
	// �ּҿ� 1�� ���ϸ� -> �Ҵ�޴� ũ�⸸ŭ ������

	// �迭 �̸��� �����ͷ� ����� �� �ִ�.
	printf("%d, %d\n", a[0], *(a+0)); // 10
	printf("%d, %d\n", a[1], *(a+1)); // 20
	// ��� : a[i] -> *(a+i)

}

void test3(void)
{
	int a[] = { 10, 20, 30, 40, 50 };
	int* pa = a; // �迭�� �̸��� �������� �ʱⰪ

	// �����͸� �迭ó�� ��� ����
	printf("%d, %d\n", *pa, *(pa+0)); // 10
	printf("%d, %d\n", *pa, *(pa + 1)); // 10, 20
}

void test4(void)
{
	// ���� �迭 : ���� �޸� ���� �Ҵ� : malloc()
	int* p = (int*)malloc(20);
	p[0] = 10; // *(p + 0) = 10;
	p[1] = 20; // *(p + 1) = 10;
}

void test5(void)
{
	// ���ڿ� : "hello"
	// c���� ���ڿ��� ������� ������ Ÿ���� ����
	char message[] = "hello"; // { 'h', 'e', 'l', 'l', 'o', '\0' };
	char* pm = "korea";
	// char* �� ���ڿ� ���ǰ� ����

	printf("%s\n", message);
	// %s : ���ڿ� ��� ����
	// �����ּҿ��� 1vyte�� �о ���ڷ� ����϶�
	// ��, null����('\0')�� ���� ������
	// ���ڿ����� �ݵ�� ���� null�� ����
	printf("%d\n", sizeof(message));
	printf("%d\n", strlen(message)); // ���ڿ� ����
	printf("%s\n", pm);
}

int main(void)
{
	test5();
	return 0;
}