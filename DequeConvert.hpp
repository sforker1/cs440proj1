#ifndef DEQUECONVERT_H
#define DEQUECONVERT_H

struct Deque_int {
	int data;
	int type_name;
	int (*size)(const struct Deque_int*);
	int (*empty)(const struct Deque_int*);
	int (*front)(const struct Deque_int*);
	int (*back)(const struct Deque_int*);
	void (*push_back)(const struct Deque_int*, int);
	void (*push_front)(const struct Deque_int*, int);
};

struct Deque_iter {
	int iterator;
};

void Deque_delete(int *ap) {
	free(ap);
}

Deque_int *Deque_int_ctor(Deque_int *ap, bool notSure) {

}

void push_back(Deque_int *ap, int b){

}



#endif