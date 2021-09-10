//
// Created by Samuel Forker on 9/8/21.
//

#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <typeinfo>
#include "DequeConvert.hpp"

bool
int_less(const int &o1, const int &o2) {
	return o1 < o2;
}

int main() {
	FILE *devnull = fopen("/dev/null", "w");
	assert(devnull != 0);

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

	//deq.print(&deq);
	assert(deq.size(&deq) == 3);

	for (Deque_int_Iterator it = deq.begin(&deq);
	     !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
		printf("%d\n", it.deref(&it));
	}

	// Test decrement.
	{
		auto it = deq.end(&deq);
		it.dec(&it);
		assert(it.deref(&it) == 2);
	}

	// printf("Using at.\n");

	for (size_t i = 0; i < 3; i++) {
		printf("%d: %d\n", int(i), deq.at(&deq, i));
	}

	deq.clear(&deq);

	deq.dtor(&deq);

	{
		Deque_int deq1, deq2;
		Deque_int_ctor(&deq1, int_less);
		Deque_int_ctor(&deq2, int_less);

		deq1.push_back(&deq1, 1);
		deq1.push_back(&deq1, 2);
		deq1.push_back(&deq1, 3);
		deq2.push_back(&deq2, 1);
		deq2.push_back(&deq2, 2);
		deq2.push_back(&deq2, 3);

		assert(Deque_int_equal(deq1, deq2));

		deq1.pop_back(&deq1);
		assert(!Deque_int_equal(deq1, deq2));
		deq1.push_back(&deq1, 4);
		assert(!Deque_int_equal(deq1, deq2));

		deq1.dtor(&deq1);
		deq2.dtor(&deq2);
	}

	// Test performance.
	{
		std::default_random_engine e;
		using rand = std::uniform_int_distribution<int>;
		std::uniform_real_distribution<float> action;
		Deque_int deq;
		Deque_int_ctor(&deq, int_less);

		for (int i = 0; i < 10000; i++) {
			deq.push_back(&deq, i);
		}

		// In one end, out the other.
		for (int i = 0; i < 20000000; i++) {
			// fprintf(stderr, "iter: %d\n", i);
			deq.push_back(&deq, i);
			deq.pop_front(&deq);
		}
		for (int i = 0; i < 20000000; i++) {
			deq.push_front(&deq, i);
			deq.pop_back(&deq);
		}

		// To do some computation, to prevent compiler from optimizing out.
		size_t sum = 0, max_size = 0;
		// Random.
		int pf = 0, pb = 0, pof = 0, pob = 0;
		for (int i = 0; i < 10000000; i++) {
			if (action(e) > .55) {
				if (rand(0, 1)(e) == 0) {
					deq.push_back(&deq, i);
					pf++;
				} else {
					deq.push_front(&deq, i);
					pb++;
				}
			} else {
				if (deq.size(&deq) > 0) {
					if (rand(0, 1)(e) == 0) {
						deq.pop_back(&deq);
						pob++;
					} else {
						deq.pop_front(&deq);
						pof++;
					}
				}
			}
			max_size = std::max(deq.size(&deq), max_size);
			// Randomly access one element.
			if (deq.size(&deq) > 0) {
				sum += deq.at(&deq, rand(0, deq.size(&deq) - 1)(e));
			}
		}
		// Print it out to prevent optimizer from optimizing out the at() calls.
		fprintf(devnull, "%lu", sum);
		printf("%zu max size\n", max_size);
		printf("%d push_backs, %d push_fronts, %d pop_backs, %d pop_fronts, %d size\n", pb, pf, pob, pof, (int) deq.size(&deq));
		deq.dtor(&deq);
	}

	// Test random access performance
	{
		size_t sum = 0;
		int lo = 0, hi = 10000000;
		Deque_int deq;
		Deque_int_ctor(&deq, int_less);

		for(int i = lo; i < hi; i++) {
			deq.push_back(&deq, i);
		}

		for(int i = lo; i < hi; i++) {
			sum += deq.at(&deq, i);
		}
		printf("Sum of all integers between %d and %d calculated using a deque is %lu.\n", lo, hi, sum);
		deq.dtor(&deq);
	}

	int rv = fclose(devnull);
	assert(rv == 0);
}