// get next token
// author: D. J. Guan
// date: 2022/10/25

#include <stdio.h>
#include <ctype.h>

typedef struct {
	int type;		// type
	double value;	// value
} token;

#define EOL 0
#define CONSTANT 1
#define OPERATOR 2
#define VARIABLE 3

token get_next_token()
{
	token t;
	int c;
	double v;

	while ((c = getchar()) == ' ');		// skip spaces

	if (c == EOF) {
		t.type = EOF;
		t.value = 0;
	} else if (c == '\n') {
		t.type = EOL;
		t.value = 0;
	} else if (isdigit(c)) {
		ungetc(c, stdin);
		scanf("%lg", &v);
		t.type = CONSTANT;
		t.value = v;
	} else if (isalpha(c)) {
		t.type = VARIABLE;
		t.value = c;
	} else {
		t.type = OPERATOR;
		t.value = c;
	}
	return t;
}

int main()
{
	token t;

	t = get_next_token();
	while (t.type != EOF) {
		if (t.type == EOL)
			printf("end of line\n");
		else if (t.type == CONSTANT)
			printf("constant: %lg\n", t.value);
		else if (t.type == VARIABLE)
			printf("variable: %c\n", (int) t.value);
		else if (t.type == OPERATOR)
			printf("operator: %c\n", (int) t.value);
		t = get_next_token();
	}
	return 0;
}
