// simplify fraction a / b; a, b > 0
// author D. J. Guan
// date: 2018/09/10

#include <stdio.h>
#include <stdlib.h>

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

int gcd(const int x, const int y)
{
	int a, b, r;

	a = abs(x);
	b = abs(y);
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	int a, b, d;
	Q_and_R w;

	while (scanf("%d %d", &a, &b) != EOF) {
		if (b <= 0)
			continue;
		w = Div(a, b);
		printf("%d/%d = %d", a, b, w.q);
		if (w.r) {
			d = gcd(w.r, b);
			printf(" %d/%d", w.r / d, b / d);
		}
		putchar('\n');
	}
	return 0;
}