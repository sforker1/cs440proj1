//
// Created by Samuel Forker on 9/8/21.
//
#include "DequeConvert.hpp"

bool
int_less(const int &o1, const int &o2) {
	return o1 < o2;
}

int main() {
	Deque_int deq;
	Deque_int_ctor(&deq, int_less);

	assert(deq.size(&deq) == 0);
	assert(deq.empty(&deq));

	// Should print "---- Deque_int, 10".
	printf("---- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
	// std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
	assert(sizeof deq.type_name == 10);

	deq.push_back(&deq, 1);
	deq.push_back(&deq, 2);
	deq.push_back(&deq, 3);
	deq.push_front(&deq, 0);
	deq.push_front(&deq, -1);

	printf("%d\n", deq.front(&deq));
	printf("%d\n", deq.back(&deq));
	assert(deq.front(&deq) == -1);
	assert(deq.back(&deq) == 3);

	deq.pop_front(&deq);
	deq.pop_back(&deq);
	assert(deq.front(&deq) == 0);
	assert(deq.back(&deq) == 2);

	assert(deq.size(&deq) == 3);

	for (Deque_int_Iterator it = deq.begin(&deq);
	     !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
		printf("%d\n", it.deref(&it));
	}
}