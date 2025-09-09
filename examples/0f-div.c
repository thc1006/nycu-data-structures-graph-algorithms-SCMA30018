// simplify fraction a / b, a, b > 0
//      block structure of C
//
// author: D. J. Guan
// date: 2018/9/10

#include <stdio.h>
#include <stdlib.h>

int main()
{
// a new data type
	typedef struct {
		int q;
		int r;
	} Q_and_R;

	int a, b, d;
	Q_and_R w;

// compute (q, r) = x / y
	Q_and_R Div(const int x, const int y) {
		Q_and_R v;

		v.q = x / y;
		v.r = x % y;

		return v;
	}

// compute GCD of x and y
	int gcd(const int x, const int y) {
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

// main program
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