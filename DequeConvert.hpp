#ifndef DEQUECONVERT_H
#define DEQUECONVERT_H

#include <iostream>
#include <cstddef>
#include <cstdlib>



struct Deque_int {
	char type_name[sizeof("Deque_int")] = "Deque_int";
	int *array;
	int arrSize = 0;
	int frontVar = -1;
	int backVar = -1;
	size_t sizeVar;
//	int (*begin)(const struct Deque_int*);
//	int (*end)(const struct Deque_int*);
	size_t (*size)(const struct Deque_int*);
	bool (*empty)(const struct Deque_int*);
	void (*print)(const struct Deque_int*);
//	int (*front)(const struct Deque_int*);
//	int (*back)(const struct Deque_int*);
//	int (*pop_front)(const struct Deque_int*);
//	int (*pop_back)(const struct Deque_int*);
	void (*push_back)(Deque_int*, int);
//	void (*push_front)(const struct Deque_int*, int);
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

void resize_array(Deque_int *ap, bool ifShift) {
	int tempArrSize = ap->arrSize;
	ap->arrSize *= 2;
	ap->array = (int *)realloc(ap->array, ap->arrSize * sizeof(int));
	if(ifShift) {
		int newFrontVal = (ap->arrSize - (tempArrSize - ap->frontVar));

		while (ap->frontVar != newFrontVal) {
			for(int i = tempArrSize; i > ap->frontVar; i--) {
				ap->array[i] = ap->array[i - 1];
				//free?
			}
			ap->frontVar++;
			tempArrSize++;
		}
	}
}

int check_array_space(Deque_int *ap) {
	if(ap->frontVar == 0 && ap->backVar == (ap->arrSize - 1)) {
		return 2;
	} else if (ap->frontVar == (ap->backVar + 1)) {
		return 1;
	} else {
		return 0;
	}
}



void push_back_func(Deque_int *ap, int newInt){ //add param for front or back
	if(ap->backVar == -1) {
		ap->frontVar = 0;
		ap->backVar = 0;
		ap->array[ap->backVar] = newInt;
	}
	int ifSpace = check_array_space(ap);
	if(ifSpace == 0) {
		ap->backVar++; //check
		ap->array[ap->backVar] = newInt;
	} else if (ifSpace == 1) { //Needs shift
		resize_array(ap, true);
		ap->backVar++;
		ap->array[ap->backVar] = newInt;
	} else { //No shift
		resize_array(ap, false);
		ap->backVar++;
		ap->array[ap->backVar] = newInt;
	}
}

void print_func(const struct Deque_int* ap) {
	//should be remade to print only from front to back
	std::cout << "Slots in array: " << ap->arrSize << std::endl;
	std::cout << "{";
	for(int i = 0; i <= ap->backVar; i++) {
		std::cout << ap->array[i] << ", ";
	}
	std::cout << "}" << std::endl;
}

void Deque_int_ctor(Deque_int *ap, bool notSure) {
	if(notSure){
		notSure = false; // supress warning
	}
	ap->array = (int *) malloc(1 * sizeof(int));
	ap->array[0] = NULL;
	ap->arrSize++;
	ap->sizeVar = 0;
	ap->size = &size_func;
	ap->empty = &empty_func;
	ap->push_back = &push_back_func;
	ap->print = &print_func;
}





#endif