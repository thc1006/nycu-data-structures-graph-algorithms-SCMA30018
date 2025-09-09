// compute (q, r) = a / b for two integers a, b; b > 0
// author D. J. Guan
// date: 2018/09/10

#include <stdio.h>

void Div(int q[], int r[], const int x, const int y)
{
	q[0] = x / y;
	r[0] = x % y;

	return;
}

int main()
{
	int a, b;
	int q, r;

	while (scanf("%d %d", &a, &b) != EOF) {
		if (b <= 0)
			continue;
		Div(&q, &r, a, b);
		printf("%d/%d = %d .. %d\n", a, b, q, r);
	}
	return 0;
}