// Get the next bit from stdin, similar to getchar
// author: D. J. Guan
// date: 2021/12/30

#include <stdio.h>

int c, d;

int getbit()
{
	if (d == 0) {
		c = getchar();
		if (c == EOF)
			return EOF;
		d = (1 << 7);	// the leftmost bit in a byte
	}
	int e = c & d;
	d >>= 1;
	if (e)
		return 1;
	else
		return 0;
}

int main()
{
	int n, x;

	d = 0;
	n = 0;
	while ((x = getbit()) != EOF) {
		if ((n % 40) == 0) putchar('\n');
		putchar(x + '0');
		n++;
		if ((n % 4) == 0) putchar(' ');
		if ((c == '\n') && ((n % 8) == 0)) putchar('\n');
	}
	printf("\n%d bits\n", n);
	return 0;
}