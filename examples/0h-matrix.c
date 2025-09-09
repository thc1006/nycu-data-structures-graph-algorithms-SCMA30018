// C -- dynamically allocate memory for 2-dimentional array
//      set m and n from command line
//      generate random data using random()
//
// author: D. J. Guan
// date: 2019/10/25

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int ac, char *av[])
{
	int **A;
	int m, n;

	if (ac > 1)
		sscanf(av[1], "%d", &m);
	else
		m = 10;

	if (ac > 2)
		sscanf(av[2], "%d", &n);
	else
		n = 10;

	// allocate memory for A;
	A = (int **) malloc(sizeof(int *) * m);
	for (int i = 0; i < m; i++)
		A[i] = (int *) malloc(sizeof(int) * n);;

#ifndef FIX
	srandom(time(NULL));
#endif
	// generate random data in [-10, 10] in A
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = random() % 20 - 10;
	// print out A
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf("%4d", A[i][j]);
		putchar('\n');
	}

	// free memory for A
	for (int i = 0; i < m; i++)
		free(A[i]);
	free(A);

	return 0;
}