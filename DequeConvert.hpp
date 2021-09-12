#ifndef DEQUECONVERT_H
#define DEQUECONVERT_H

#include <iostream>
#include <cstddef>
#include <cstdlib>


struct Deque_int_Iterator {
	int *varPointer;
	int iterCurr;
	int iterSize;
	int *startArray;
	int (*deref)(const struct Deque_int_Iterator*);
	void (*inc)(Deque_int_Iterator*);
	void (*dec)(Deque_int_Iterator*);
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
	int (*at)(const struct Deque_int*, int);
	void (*pop_front)(Deque_int*);
	void (*pop_back)(Deque_int*);
	void (*clear)(Deque_int*);
	void (*dtor)(Deque_int*);
	void (*push_back)(Deque_int*, int);
	void (*push_front)(Deque_int*, int);
	void (*sort)(Deque_int*, Deque_int_Iterator, Deque_int_Iterator);
	bool (*compare)(const int&, const int&);
};

void mergeSortMerger(Deque_int* ap, int lower, int higher, int middle) {
	int size = higher - lower + 1;
	int *tmpArray = new int[size];
	int i = lower;
	int j = middle + 1;
	int k = 0;
	while ((i <= middle) && (j <= higher)) {
		if (ap->compare(ap->array[i],ap->array[j]))
			tmpArray[k++] = ap->array[i++];
		else
			tmpArray[k++] = ap->array[j++];
	}
	while (i <= middle) {
		tmpArray[k++] = ap->array[i++];
	}
	while (j <= higher) {
		tmpArray[k++] = ap->array[j++];
	}
	for (k = 0; k < size; k++) {
		ap->array[lower + k] = tmpArray[k];
	}
	delete [] tmpArray;
}

void mergeSort(Deque_int* ap, int lower, int higher) {
	unsigned int middle;
	if (lower < higher) {
		middle = (lower + higher) / 2;
		mergeSort(ap, lower, middle);
		mergeSort(ap, middle + 1, higher);
		mergeSortMerger(ap, lower, higher, middle);
	}
}

void sort_func(Deque_int* ap, Deque_int_Iterator low, Deque_int_Iterator high) {
	if(high.iterCurr < low.iterCurr) {
		std::cout << "YIKES ALERT!" << std::endl;
		//fix array fix_array(Deque_int* ap);
	} else if (low.iterCurr == high.iterCurr) {
		return; // do nothing!
	}
	mergeSort(ap, low.iterCurr, high.iterCurr);
}


bool Deque_int_equal(const struct Deque_int ap, const struct Deque_int ap2) {
	if(ap.sizeVar == ap2.sizeVar) {
		for(long unsigned int i = 0; i < ap.sizeVar; i++) {
			//std::cout << "COMPARE: " << ap.at(&ap, i) << " vs " << ap2.at(&ap2, i) << std::endl;
			if(ap.compare(ap.at(&ap, i), ap2.at(&ap2, i)) || ap.compare(ap2.at(&ap2, i), ap.at(&ap, i))) {
				return false;
			}
		}
	} else {
		return false;
	}
	return true;
}

void clear_func(Deque_int* ap) {
	ap->frontVar = -1;
	ap->backVar = -1;
}

void dtor_func(Deque_int* ap) {
	// save for later
}

int at_func(const struct Deque_int* ap, int num) {
	int index = ap->frontVar + num;
	if(index > (ap->arrSize - 1)) { //exceeds array size
		index = index - ap->arrSize;
	}
	return ap->array[index];
}

void dec_func(Deque_int_Iterator* ap) {
	if (ap->iterCurr == 0) {
		ap->iterCurr = (ap->iterSize - 1);
		ap->varPointer = (ap->startArray + (ap->iterSize - 1));
	} else {
		ap->iterCurr--;
		ap->varPointer--;
	}
}

void inc_func(Deque_int_Iterator* ap) {
	if (ap->iterCurr == (ap->iterSize - 1)) {
		ap->iterCurr = 0;
		ap->varPointer = ap->startArray;
	} else {
		ap->varPointer++;
		ap->iterCurr++;
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

Deque_int_Iterator begin_func(const struct Deque_int* ap) {
	Deque_int_Iterator retVal;
	retVal.varPointer = &ap->array[ap->frontVar];
	retVal.iterCurr = ap->frontVar;
	retVal.inc = &inc_func;
	retVal.deref = &deref_func;
	retVal.dec = &dec_func;
	retVal.iterSize = ap->arrSize;
	retVal.startArray = ap->array;
	return retVal;
}

Deque_int_Iterator end_func(const struct Deque_int* ap) {
	Deque_int_Iterator retVal;
	int *tempPointer = &ap->array[ap->backVar];
	retVal.iterCurr = ap->backVar;
	tempPointer++;
	retVal.varPointer = tempPointer;
	retVal.inc = &inc_func;
	retVal.deref = &deref_func;
	retVal.dec = &dec_func;
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
		//std::cout << "Case Front 0: " << newInt << " inserted at " << ap->frontVar << std::endl;
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
		//std::cout << "Case Front 1: " << newInt << " inserted at " << ap->frontVar << std::endl;
	} else if (ifSpace == 1) {
		resize_array(ap, true);
		if(ap->frontVar == 0) {
			ap->frontVar = ap->arrSize - 1;
		} else {
			ap->frontVar--;
		}
		ap->sizeVar++;
		ap->array[ap->frontVar] = newInt;
		//std::cout << "Case Front 2: " << newInt << " inserted at " << ap->frontVar << std::endl;
	} else {
		resize_array(ap, false);
		if(ap->frontVar == 0) {
			ap->frontVar = ap->arrSize - 1;
		} else {
			ap->frontVar--;
		}
		ap->sizeVar++;
		ap->array[ap->frontVar] = newInt;
		//std::cout << "Case Front 3: " << newInt << " inserted at " << ap->frontVar << std::endl;
	}
}

void push_back_func(Deque_int *ap, int newInt){ //add param for front or back
	if(ap->backVar == -1) {
		ap->frontVar = 0;
		ap->backVar = 0;
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		//std::cout << "Case Back 0: " << newInt << " inserted at " << ap->backVar << std::endl;
		return;
	}
	int ifSpace = check_array_space(ap);
	if(ifSpace == 0) {
		ap->backVar++; //check
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		//std::cout << "Case Back 1: " << newInt << " inserted at " << ap->backVar << std::endl;
	} else if (ifSpace == 1) { //Needs shift
		resize_array(ap, true);
		ap->backVar++;
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		//std::cout << "Case Back 2: " << newInt << " inserted at " << ap->backVar << std::endl;
	} else { //No shift
		resize_array(ap, false);
		ap->backVar++;
		ap->sizeVar++;
		ap->array[ap->backVar] = newInt;
		//std::cout << "Case Back 3: " << newInt << " inserted at " << ap->backVar << std::endl;
	}
}

void print_func(const struct Deque_int* ap) {
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
	std::cout << "}" << std::endl;
	std::cout << "Front: " << ap->frontVar << std::endl;
	std::cout << "Back: " << ap->backVar << std::endl;
	std::cout << "True Size: " << ap->sizeVar << std::endl;
}

void Deque_int_ctor(Deque_int *ap, bool (*compare_func)(const int&, const int&)) {
	ap->array = (int *) malloc(1 * sizeof(int));
	ap->compare = compare_func;
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
	ap->at = &at_func;
	ap->dtor = dtor_func;
	ap->clear = &clear_func;
	ap->sort = &sort_func;
}

#endif