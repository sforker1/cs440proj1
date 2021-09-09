#ifndef DEQUECONVERT_H
#define DEQUECONVERT_H

#include <iostream>
#include <cstddef>
#include <cstdlib>



struct Deque_int {
	std::string type_name = "Deque_int";
	int *array;
	size_t sizeVar;
//	int (*begin)(const struct Deque_int*);
//	int (*end)(const struct Deque_int*);
	size_t (*size)(const struct Deque_int*);
	bool (*empty)(const struct Deque_int*);
	int (*front)(const struct Deque_int*);
	int (*back)(const struct Deque_int*);
	int (*pop_front)(const struct Deque_int*);
	int (*pop_back)(const struct Deque_int*);
	void (*push_back)(const struct Deque_int*, int);
	void (*push_front)(const struct Deque_int*, int);
};

struct Deque_int_Iterator {
	int (*deref)(const struct Deque_int_Iterator*);
	void (*inc)(const struct Deque_int_Iterator*);
};

//bool Deque_int_Iterator_equal(Deque_int_Iterator* ap, int end) {
//	return false;
//}

//void Deque_delete(int *ap) {
//	free(ap);
//}

size_t size_func(const struct Deque_int* ap) {
	return ap->sizeVar;
}

bool empty_func(const struct Deque_int* ap) {
	if(ap->sizeVar == 0) {
		return true;
	}
	else {
		return false;
	}
}

void push_back(Deque_int *ap, int b){

}

Deque_int *Deque_int_ctor(Deque_int *ap, bool notSure) {
	ap->type_name = "int";
	ap->array = (int *) malloc(0 * sizeof(int));
	ap->sizeVar = 0;
	ap->size = &size_func;
	ap->empty = &empty_func;
}





#endif