// write a bit to stdout, similar to putchar
// author: D. J. Guan
// date: 2022/12/23

#include <stdio.h>

int c = 0;		// the buffer
int d = 0;		// number of bits in the buffer

void putbit(const int b)
{
	if (d == 8) {		// the buffer c is full
		putchar(c);
		c = 0; d = 0;
	}
	c = (c << 1) ^ b;
	d++;
}

// A demonstration of the usage of putbit()
// The input {0,1}-bit string is from stdin with ASCII code of '0' or '1'.
// Each line must contain a multiple of 8 bits, Otherwise, 0's will be padded.
// The output is stdout. (Some characters cannot be displayed properly.)
int main()
{
	int n = 0;		// total number of bits
	int x;

	while ((x = getchar()) != EOF) {
		if ((x == '0') || (x == '1')) {
			putbit(x - '0');	// x is the ASCII code of 0 or 1
			n++;
		}
		if (x == '\n')
			if (d) {		// the last few bits
				putchar(c << (8 - d));
				putchar('\n');
				c = 0; d = 0;
			}
	}
	fprintf(stderr, "%d bits\n", n);
	return 0;
}