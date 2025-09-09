/* implement stack using linked list */

#include <iostream>

using namespace std;

class Stack {
      private:
	struct node {
		int data;
		struct node *next;
	};

// private data for a stack
      private:
	 node * sp;

      public:
	 Stack() {		// the constructor
		sp = NULL;
	};

	void push(int x) {	// push an element x into a stack
		node *t;

		t = (node *) malloc(sizeof(node));
		t->data = x;
		t->next = sp;
		sp = t;
	}

	int pop() {		// pop an element out off a stack
		node *t;
		int d;

		t = sp;
		d = t->data;
		sp = t->next;
		free(t);
		return d;
	}

	bool isEmpty() {	// test if the stack is empty or not
		return sp == NULL;
	}
};

/* main program */

int main()
{
	Stack A, B;
	const int M = 6;

	for (int i = 0; i < M; i++) {
		A.push(100 + i);
		B.push(200 + i);
	}

	cout << "Stack 1:" << endl;
	while (!A.isEmpty()) {
		cout << A.pop() << endl;
	}

	cout << endl << "Stack 2:" << endl;
	while (!B.isEmpty()) {
		cout << B.pop() << endl;
	}

	return 0;
}