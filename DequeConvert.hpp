#ifndef DEQUECONVERT_H
#define DEQUECONVERT_H

#include <iostream>
#include <cstddef>
#include <cstdlib>


struct Deque_int_Iterator {
	int *varPointer;
	int iterFront;
	int iterBack;
	int iterSize;
	int *startArray;
	int (*deref)(const struct Deque_int_Iterator*);
	void (*inc)(Deque_int_Iterator*);
};

struct Deque_int {
	char type_name[sizeof("Deque_int")] = "Deque_int";
	int *array;
	int arrSize = 0; //true array size
	int frontVar = -1;
	int backVar = -1;
	size_t sizeVar; //amount of elements in the array
	Deque_int_Iterator (*begin)(const struct Deque_int*);
	Deque_int_Iterator (*end)(const struct Deque_int*);
	size_t (*size)(const struct Deque_int*);
	bool (*empty)(const struct Deque_int*);
	void (*print)(const struct Deque_int*);
	int (*front)(const struct Deque_int*);
	int (*back)(const struct Deque_int*);
	void (*pop_front)(Deque_int*);
	void (*pop_back)(Deque_int*);
	void (*push_back)(Deque_int*, int);
	void (*push_front)(Deque_int*, int);
};


void inc_func(Deque_int_Iterator* ap) {
	if(ap->iterFront == ap->iterBack) {
		//std::cout << "Inc Case 1" << std::endl;
		ap->iterFront++;
		ap->varPointer++;
		// do nothing? undefined behavior because we're hoping the iterator catches the next dereference from the pointer
	} else if (ap->iterFront < ap->iterBack){
		//std::cout << "Inc Case 2" << std::endl;
		ap->iterFront++;
		ap->varPointer++;
	} else {
		if(ap->varPointer == (ap->startArray + (ap->iterSize - 1))) {
			//std::cout << "Inc Case 3" << std::endl;
			ap->iterFront = 0;
			ap->varPointer = ap->startArray;
		} else {
			//std::cout << "Inc Case 4" << std::endl;
			ap->iterFront++;
			ap->varPointer++;
		}
	}
}

int deref_func(const struct Deque_int_Iterator* ap) {
	return *(ap->varPointer);
}


bool Deque_int_Iterator_equal(Deque_int_Iterator ap, Deque_int_Iterator ap2) {
	//std::cout << "COMPARE: " << ap.varPointer << " and " << ap2.varPointer << std::endl;
	if(ap.varPointer == ap2.varPointer) {
		return true;
	} else {
		return false;
	}
}

//void Deque_delete(int *ap) {
//	free(ap);
//}

Deque_int_Iterator begin_func(const struct Deque_int* ap) {
	Deque_int_Iterator retVal;
	retVal.varPointer = &ap->array[ap->frontVar];
	retVal.inc = &inc_func;
	retVal.deref = &deref_func;
	retVal.iterFront = ap->frontVar;
	retVal.iterBack = ap->backVar;
	retVal.iterSize = ap->arrSize;
	retVal.startArray = ap->array;
	return retVal;
}

Deque_int_Iterator end_func(const struct Deque_int* ap) {
	Deque_int_Iterator retVal;
	int *tempPointer = &ap->array[ap->backVar];
	tempPointer++;
	retVal.varPointer = tempPointer;
	retVal.inc = &inc_func;
	retVal.deref = &deref_func;
	retVal.iterFront = ap->frontVar;
	retVal.iterBack = ap->backVar;
	retVal.iterSize = ap->arrSize;
	retVal.startArray = ap->array;
	return retVal;
}

void pop_front_func(Deque_int* ap) {
	if(ap->frontVar == (ap->arrSize - 1)) {
		ap->frontVar = 0;
		ap->sizeVar--;
	} else if (ap->frontVar == 0 && ap->backVar == 0){
		ap->frontVar = -1;
		ap->backVar = -1;
		ap->sizeVar--;
	} else if (ap->frontVar == ap->backVar) {
		ap->sizeVar--;
		//remove item by placing fake place holder?
		//reduce size
		//increase height on if tree (top)
	} else if (ap->frontVar < ap->backVar){
		if(ap->frontVar == 0) {
			ap->sizeVar--;
			ap->frontVar = (ap->arrSize - 1);
		} else {
			ap->sizeVar--;
			ap->frontVar--;
		}
	} else {
		if(ap->frontVar == (ap->arrSize - 1)){
			ap->sizeVar--;
			ap->frontVar = 0;
		} else {
			ap->sizeVar--;
			ap->frontVar++;
		}
	}
}

void pop_back_func(Deque_int* ap) {
	if(ap->backVar == 0 && ap->frontVar == 0){
		ap->backVar = -1;
		ap->frontVar = -1;
		ap->sizeVar--;
	} else if (ap->backVar == ap->frontVar) {
		ap->sizeVar--;
		//nothing happens
		//fake variable
	} else if (ap->backVar < ap->frontVar) {
		if(ap->backVar == 0) {
			ap->sizeVar--;
			ap->backVar = (ap->arrSize - 1);
		} else {
			ap->sizeVar--;
			ap->backVar--;
		}
	} else {
		ap->sizeVar--;
		ap->backVar--;
	}
}

int front_func(const struct Deque_int* ap) {
	return ap->array[ap->frontVar];
}

int back_func(const struct Deque_int* ap) {
	return ap->array[ap->backVar];
}


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

void push_front_func(Deque_int *ap, int newInt){
	if(ap->frontVar == -1) {
		ap->frontVar = 0;
		ap->backVar = 0;
		ap->sizeVar++;
		ap->array[ap->frontVar] = newInt;
		std::cout << "Case Front 0: " << newInt << " inserted at " << ap->frontVar << std::endl;
		return;
	}
	int ifSpace = check_array_space(ap);
	if(ifSpace == 0) {
		if(ap->frontVar == 0) {
			ap->frontVar = ap->arrSize - 1;
		} else {
			ap->frontVar--;
		}
		ap->sizeVar++;
		ap->array[ap->frontVar] = newInt;
		std::cout << "Case Front 1: " << newInt << " inserted at " << ap->frontVar << std::endl;
	} else if (ifSpace == 1) {
		resize_array(ap, true);
		if(ap->frontVar == 0) {
			ap->frontVar = ap->arrSize - 1;
		} else {
			ap->frontVar--;
		}
		ap->sizeVar++;
		ap->array[ap->frontVar] = newInt;
		std::cout << "Case Front 2: " << newInt << " inserted at " << ap->frontVar << std::endl;
	} else {
		resize_array(ap, false);
		if(ap->frontVar == 0) {
			ap->frontVar = ap->arrSize - 1;
		} else {
			ap->frontVar--;
		}
		ap->sizeVar++;
		ap->array[ap->frontVar] = newInt;
		std::cout << "Case Front 3: " << newInt << " inserted at " << ap->frontVar << std::endl;
	}
}

void push_back_func(Deque_int *ap, int newInt){ //add param for front or back
	if(ap->backVar == -1) {
		ap->frontVar = 0;
		ap->backVar = 0;
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		std::cout << "Case Back 0: " << newInt << " inserted at " << ap->backVar << std::endl;
		return;
	}
	int ifSpace = check_array_space(ap);
	if(ifSpace == 0) {
		ap->backVar++; //check
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		std::cout << "Case Back 1: " << newInt << " inserted at " << ap->backVar << std::endl;
	} else if (ifSpace == 1) { //Needs shift
		resize_array(ap, true);
		ap->backVar++;
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		std::cout << "Case Back 2: " << newInt << " inserted at " << ap->backVar << std::endl;
	} else { //No shift
		resize_array(ap, false);
		ap->backVar++;
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		std::cout << "Case Back 3: " << newInt << " inserted at " << ap->backVar << std::endl;
	}
}

void print_func(const struct Deque_int* ap) {
	//should be remade to print only from front to back
	std::cout << "Slots in array: " << ap->arrSize << std::endl;
	std::cout << "{";
	int tempI = ap->frontVar;
	bool ifPassed = true;
	while (ifPassed) {
		if(tempI == ap->backVar) {
			ifPassed = false;
		}
		std::cout << ap->array[tempI] << ", ";
		if(tempI != (ap->arrSize - 1)) {
			tempI++;
		} else {
			tempI = 0;
		}
	}

//	for(int i = 0; i <= ap->backVar; i++) {
//		std::cout << ap->array[i] << ", ";
//	}
	std::cout << "}" << std::endl;
	std::cout << "Front: " << ap->frontVar << std::endl;
	std::cout << "Back: " << ap->backVar << std::endl;
	std::cout << "True Size: " << ap->sizeVar << std::endl;
}

void Deque_int_ctor(Deque_int *ap, bool notSure) {
	if(notSure){
		notSure = false; // supress warning
	}
	ap->array = (int *) malloc(1 * sizeof(int));
	//ap->array[0] = NULL;
	ap->arrSize++;
	ap->sizeVar = 0;
	ap->size = &size_func;
	ap->empty = &empty_func;
	ap->push_back = &push_back_func;
	ap->push_front = &push_front_func;
	ap->print = &print_func;
	ap->front = &front_func;
	ap->back = &back_func;
	ap->pop_front = &pop_front_func;
	ap->pop_back = &pop_back_func;
	ap->begin = &begin_func;
	ap->end = &end_func;
}





#endif