#ifndef DEQUE_H
#define DEQUE_H

#define Deque_DEFINE(t) \
	struct Deque_##t##_Iterator { \
		t *varPointer; \
		int iterCurr; \
		int iterSize; \
		t *startArray; \
		t& (*deref)(const struct Deque_##t##_Iterator *); \
		void (*inc)(Deque_##t##_Iterator *); \
		void (*dec)(Deque_##t##_Iterator *); \
	}; \
	struct Deque_##t { \
		char type_name[sizeof("Deque_" #t)] = "Deque_" #t; \
		t *array; \
		int arrSize = 0; \
		int frontVar = -1; \
		int backVar = -1; \
		size_t sizeVar; \
		Deque_##t##_Iterator (*begin)(const struct Deque_##t *); \
		Deque_##t##_Iterator (*end)(const struct Deque_##t *); \
		size_t (*size)(const struct Deque_##t *); \
		bool (*empty)(const struct Deque_##t *); \
		t& (*front)(const struct Deque_##t *); \
		t& (*back)(const struct Deque_##t *); \
		t& (*at)(const struct Deque_##t *, int); \
		void (*pop_front)(Deque_##t *); \
		void (*pop_back)(Deque_##t *); \
		void (*clear)(Deque_##t *); \
		void (*dtor)(Deque_##t *); \
		void (*push_back)(Deque_##t *, t); \
		void (*push_front)(Deque_##t *, t); \
		void (*sort)(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator); \
		bool (*compare)(const t&, const t&); \
	}; \
	void mergeSortMerger(Deque_##t *ap, int lower, int higher, int middle) { \
		int size = higher - lower + 1; \
		t *tmpArray = new t[size]; \
		int i = lower; \
		int j = middle + 1; \
		int k = 0; \
		while ((i <= middle) && (j <= higher)) { \
			if (ap->compare(ap->array[i],ap->array[j])) \
				tmpArray[k++] = ap->array[i++]; \
			else \
				tmpArray[k++] = ap->array[j++]; \
		} \
		while (i <= middle) { \
			tmpArray[k++] = ap->array[i++]; \
		} \
		while (j <= higher) { \
			tmpArray[k++] = ap->array[j++]; \
		} \
		for (k = 0; k < size; k++) { \
			ap->array[lower + k] = tmpArray[k]; \
		} \
		delete [] tmpArray; \
	} \
	void mergeSort(Deque_##t *ap, int lower, int higher) { \
		unsigned int middle; \
		if (lower < higher) { \
			middle = (lower + higher) / 2; \
			mergeSort(ap, lower, middle); \
			mergeSort(ap, middle + 1, higher); \
			mergeSortMerger(ap, lower, higher, middle); \
		} \
	} \
    void fix_for_sort(Deque_##t *ap) { \
		int tempArrSize = (ap->arrSize - ap->frontVar); \
		t *tempArr = new t[tempArrSize]; \
		int index = 0; \
		for(int i = ap->frontVar; i < ap->arrSize; i++) { \
			tempArr[index] = ap->array[i]; \
			index++; \
		} \
		int endOfArr = 0; \
		int newBackVar = ap->backVar + (ap->arrSize - ap->frontVar); \
		while (ap->backVar != newBackVar) { \
			for(int i = ap->backVar; i >= endOfArr; i--) { \
				ap->array[i + 1] = ap->array[i]; \
			} \
			ap->backVar++; \
			endOfArr++; \
		} \
		ap->frontVar = 0; \
		for(int i = 0; i < tempArrSize; i++) { \
			ap->array[i] = tempArr[i]; \
		} \
		delete [] tempArr; \
	} \
	void sort_func(Deque_##t *ap, Deque_##t##_Iterator low, Deque_##t##_Iterator high) { \
		if(high.iterCurr < low.iterCurr) { \
            int shiftAmt = (ap->arrSize - ap->frontVar); \
			low.iterCurr = (low.iterCurr - ap->frontVar); \
			high.iterCurr = (shiftAmt + high.iterCurr); \
			fix_for_sort(ap); \
		} else if (low.iterCurr == high.iterCurr) { \
			return; \
		} \
		mergeSort(ap, low.iterCurr, high.iterCurr); \
	} \
	bool Deque_##t##_equal(const struct Deque_##t ap, const struct Deque_##t ap2) { \
		if(ap.sizeVar == ap2.sizeVar) { \
			for(long unsigned int i = 0; i < ap.sizeVar; i++) { \
				if(ap.compare(ap.at(&ap, i), ap2.at(&ap2, i)) || ap.compare(ap2.at(&ap2, i), ap.at(&ap, i))) { \
					return false; \
				} \
			} \
		} else { \
			return false; \
		} \
		return true; \
	} \
	void clear_func(Deque_##t *ap) { \
		ap->frontVar = -1; \
		ap->backVar = -1; \
	} \
	void dtor_func(Deque_##t *ap) { \
		free(ap->array); \
	} \
	t& at_func(const struct Deque_##t *ap, int num) { \
		int index = ap->frontVar + num; \
		if(index > (ap->arrSize - 1)) { \
			index = index - ap->arrSize; \
		} \
		return ap->array[index]; \
	} \
	void dec_func(Deque_##t##_Iterator *ap) { \
		if (ap->iterCurr == 0) { \
			ap->iterCurr = (ap->iterSize - 1); \
			ap->varPointer = (ap->startArray + (ap->iterSize - 1)); \
		} else { \
			ap->iterCurr--; \
			ap->varPointer--; \
		} \
	} \
	void inc_func(Deque_##t##_Iterator *ap) { \
		if (ap->iterCurr == (ap->iterSize - 1)) { \
			ap->iterCurr = 0; \
			ap->varPointer = ap->startArray; \
		} else { \
			ap->varPointer++; \
			ap->iterCurr++; \
		} \
	} \
	t& deref_func(const struct Deque_##t##_Iterator* ap) { \
		return *(ap->varPointer); \
	} \
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator ap, Deque_##t##_Iterator ap2) { \
		if(ap.varPointer == ap2.varPointer) { \
			return true; \
		} else { \
			return false; \
		} \
	} \
	Deque_##t##_Iterator begin_func(const struct Deque_##t *ap) { \
		Deque_##t##_Iterator retVal; \
		retVal.varPointer = &ap->array[ap->frontVar]; \
		retVal.iterCurr = ap->frontVar; \
		retVal.inc = &inc_func; \
		retVal.deref = &deref_func; \
		retVal.dec = &dec_func; \
		retVal.iterSize = ap->arrSize; \
		retVal.startArray = ap->array; \
		return retVal; \
	} \
	Deque_##t##_Iterator end_func(const struct Deque_##t *ap) { \
		Deque_##t##_Iterator retVal; \
		t *tempPointer = &ap->array[ap->backVar]; \
		retVal.iterCurr = ap->backVar; \
		tempPointer++; \
		retVal.varPointer = tempPointer; \
		retVal.inc = &inc_func; \
		retVal.deref = &deref_func; \
		retVal.dec = &dec_func; \
		retVal.iterSize = ap->arrSize; \
		retVal.startArray = ap->array; \
		return retVal; \
	} \
	void pop_front_func(Deque_##t *ap) { \
		if(ap->frontVar == (ap->arrSize - 1)) { \
			ap->frontVar = 0; \
			ap->sizeVar--; \
		} else if (ap->frontVar == 0 && ap->backVar == 0){ \
			ap->frontVar = -1; \
			ap->backVar = -1; \
			ap->sizeVar--; \
		} else if (ap->frontVar == ap->backVar) { \
			ap->sizeVar--; \
		} else if (ap->frontVar < ap->backVar){ \
			if(ap->frontVar == 0) { \
				ap->sizeVar--; \
				ap->frontVar = (ap->arrSize - 1); \
			} else { \
				ap->sizeVar--; \
				ap->frontVar--; \
			} \
		} else { \
			if(ap->frontVar == (ap->arrSize - 1)){ \
				ap->sizeVar--; \
				ap->frontVar = 0; \
			} else { \
				ap->sizeVar--; \
				ap->frontVar++; \
			} \
		} \
	} \
	void pop_back_func(Deque_##t *ap) { \
		if(ap->backVar == 0 && ap->frontVar == 0){ \
			ap->backVar = -1; \
			ap->frontVar = -1; \
			ap->sizeVar--; \
		} else if (ap->backVar == ap->frontVar) { \
			ap->sizeVar--; \
		} else if (ap->backVar < ap->frontVar) { \
			if(ap->backVar == 0) { \
				ap->sizeVar--; \
				ap->backVar = (ap->arrSize - 1); \
			} else { \
				ap->sizeVar--; \
				ap->backVar--; \
			} \
		} else { \
			ap->sizeVar--; \
			ap->backVar--; \
		} \
	} \
	t& front_func(const struct Deque_##t *ap) { \
		return ap->array[ap->frontVar]; \
	} \
	t& back_func(const struct Deque_##t *ap) { \
		return ap->array[ap->backVar]; \
	} \
	size_t size_func(const struct Deque_##t *ap) { \
		return ap->sizeVar; \
	} \
	bool empty_func(const struct Deque_##t *ap) { \
		if(ap->sizeVar == 0) { \
			return true; \
		} \
		else { \
			return false; \
		} \
	} \
	void resize_array(Deque_##t *ap, bool ifShift) { \
		int tempArrSize = ap->arrSize; \
		ap->arrSize *= 2; \
		ap->array = (t *)realloc(ap->array, ap->arrSize * sizeof(t)); \
		if(ifShift) { \
			int newFrontVal = (ap->arrSize - (tempArrSize - ap->frontVar)); \
			while (ap->frontVar != newFrontVal) { \
				for(int i = tempArrSize; i > ap->frontVar; i--) { \
					ap->array[i] = ap->array[i - 1]; \
				} \
				ap->frontVar++; \
				tempArrSize++; \
			} \
		} \
	} \
	int check_array_space(Deque_##t *ap) { \
		if(ap->frontVar == 0 && ap->backVar == (ap->arrSize - 1)) { \
			return 2; \
		} else if (ap->frontVar == (ap->backVar + 1)) { \
			return 1; \
		} else { \
			return 0; \
		} \
	} \
	void push_front_func(Deque_##t *ap, t newInt){ \
		if(ap->frontVar == -1) { \
			ap->frontVar = 0; \
			ap->backVar = 0; \
			ap->sizeVar++; \
			ap->array[ap->frontVar] = newInt; \
			return; \
		} \
		int ifSpace = check_array_space(ap); \
		if(ifSpace == 0) { \
			if(ap->frontVar == 0) { \
				ap->frontVar = ap->arrSize - 1; \
			} else { \
				ap->frontVar--; \
			} \
			ap->sizeVar++; \
			ap->array[ap->frontVar] = newInt; \
		} else if (ifSpace == 1) { \
			resize_array(ap, true); \
			if(ap->frontVar == 0) { \
				ap->frontVar = ap->arrSize - 1; \
			} else { \
				ap->frontVar--; \
			} \
			ap->sizeVar++; \
			ap->array[ap->frontVar] = newInt; \
		} else { \
			resize_array(ap, false); \
			if(ap->frontVar == 0) { \
				ap->frontVar = ap->arrSize - 1; \
			} else { \
				ap->frontVar--; \
			} \
			ap->sizeVar++; \
			ap->array[ap->frontVar] = newInt; \
		} \
	} \
	void push_back_func(Deque_##t *ap, t newInt){ \
		if(ap->backVar == -1) { \
			ap->frontVar = 0; \
			ap->backVar = 0; \
			ap->sizeVar++; \
			ap->array[ap->backVar] = newInt; \
			return; \
		} \
		int ifSpace = check_array_space(ap); \
		if(ifSpace == 0) { \
			ap->backVar++; \
			ap->sizeVar++; \
			ap->array[ap->backVar] = newInt; \
		} else if (ifSpace == 1) { \
			resize_array(ap, true); \
			ap->backVar++; \
			ap->sizeVar++; \
			ap->array[ap->backVar] = newInt; \
		} else { \
			resize_array(ap, false); \
			ap->backVar++; \
			ap->sizeVar++; \
			ap->array[ap->backVar] = newInt; \
		} \
	} \
	void Deque_##t##_ctor(Deque_##t *ap, bool (*compare_func)(const t&, const t&)) { \
		ap->array = (t *) malloc(1 * sizeof(t)); \
		ap->compare = compare_func; \
		ap->arrSize++; \
		ap->sizeVar = 0; \
		ap->size = &size_func; \
		ap->empty = &empty_func; \
		ap->push_back = &push_back_func; \
		ap->push_front = &push_front_func; \
		ap->front = &front_func; \
		ap->back = &back_func; \
		ap->pop_front = &pop_front_func; \
		ap->pop_back = &pop_back_func; \
		ap->begin = &begin_func; \
		ap->end = &end_func; \
		ap->at = &at_func; \
		ap->dtor = dtor_func; \
		ap->clear = &clear_func; \
		ap->sort = &sort_func; \
	}
#endif