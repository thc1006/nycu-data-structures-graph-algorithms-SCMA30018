/* implement stack using linked list */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 200

/* stack.h */

struct stack {
	int data;
	struct stack *next;
};

struct stack *new_stack()	// the constructor
{
	return NULL;
}

void push(struct stack **s, int x)	// to push an element x into a stack
{
	struct stack *t;

	t = (struct stack *) malloc(sizeof(int));
	t->data = x;
	t->next = *s;
	*s = t;
}

int pop(struct stack **s)	// to pop an element out off a stack
{
	struct stack *t;
	int d;

	t = *s;
	d = t->data;
	*s = t->next;
	free(t);
	return d;
}

void delete_stack(struct stack *s)
{
	struct stack *t, *u;

	t = s;
	while (t != NULL) {
		u = t;
		t = t->next;
		free(u);
	}
}

/* main program */

int main()
{
	struct stack *A, *B;
	int i;

	A = new_stack();
	B = new_stack();

	for (i = 0; i < M; i++) {
		push(&A, 100 + i);
		push(&B, 200 + i);
	}

	printf("Dump of stack 1:\n");
	for (i = 0; i < M; i++) {
		printf("%d\n", pop(&A));
	}

	printf("Dump of stack 2:\n");
	for (i = 0; i < M; i++) {
		printf("%d\n", pop(&B));
	}

	delete_stack(A);
	delete_stack(B);

	return 0;
}