// C array and pointer
//
// author: D. J. Guan
// date: 2018/9/10

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a;

	a = (int *) malloc(sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
		a[i] = i;

	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	putchar('\n');

	*a = 9;
	a[1] = 8;
	*(a + 2) = 7;
	a[3] = 6;
	*(a + 4) = 5;
	a[5] = 4;
	*(a + 6) = 3;
	a[7] = 2;
	*(a + 8) = 1;
	a[9] = 0;

	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	putchar('\n');

	printf("%d ", *a + a[1] + *(a + 2));
	printf("%d\n", *(a + 9) + a[8] + *(a + 7));

	return 0;
}