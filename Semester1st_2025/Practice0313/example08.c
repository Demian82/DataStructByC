#include <stdio.h>

void compute(int a, int b, int* padd, int* psub)
{
	*padd = a + b;
	*psub = a - b; 
}


int main(void)
{
	int a = 10, b = 20;
	int add, sub;
	compute(a, b, &add, &sub);
	
	printf("add = %d, sub = %d\n", add, sub);

	return 0;
}