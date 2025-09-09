// compute (q, r) = a / b for two integers a, b; b > 0
// author D. J. Guan
// date: 2018/09/10

#include <stdio.h>

typedef struct {
	int q;
	int r;
} Q_and_R;

Q_and_R Div(const int x, const int y)
{
	Q_and_R v;

	v.q = x / y;
	v.r = x % y;

	return v;
}

int main()
{
	int a, b;
	Q_and_R w;

	while (scanf("%d %d", &a, &b) != EOF) {
		if (b <= 0)
			continue;
		w = Div(a, b);
		printf("%d/%d = %d .. %d\n", a, b, w.q, w.r);
	}
	return 0;
}