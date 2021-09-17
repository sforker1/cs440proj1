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

	{
		Deque_int deq;
		Deque_int_ctor(&deq, int_less);

		Deque_int deq1;
		Deque_int_ctor(&deq1, int_less);

		deq.push_back(&deq, 10);
		deq.push_back(&deq, 9);
		deq.push_back(&deq, 8);
		deq.push_back(&deq, 7);
		deq.push_back(&deq, 6);
		deq.push_front(&deq, 3);
		deq.push_front(&deq, 4);

		deq1.push_back(&deq1, 4);
		deq1.push_back(&deq1, 3);
		deq1.push_back(&deq1, 8);
		deq1.push_back(&deq1, 9);
		deq1.push_back(&deq1, 10);
		deq1.push_back(&deq1, 7);
		deq1.push_back(&deq1, 6);

		auto iter1 = deq.begin(&deq);
		auto iter2 = deq.end(&deq);

		for(int i=0;i<1;i++)
			iter1.inc(&iter1);

		for(int i=0;i<2;i++)
			iter2.dec(&iter2);

		deq.sort(&deq, iter1, iter2);


		for (Deque_int_Iterator it = deq.begin(&deq);
		     !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
			printf("%d\n", it.deref(&it));
		}

		printf("------------------------");

		for (Deque_int_Iterator it = deq1.begin(&deq1);
		     !Deque_int_Iterator_equal(it, deq.end(&deq1)); it.inc(&it)) {
			printf("%d\n", it.deref(&it));
		}

		assert(Deque_int_equal(deq, deq1));

//		deq.pop_front(&deq);
//		deq.pop_back(&deq);
//		assert(deq.front(&deq) == 0);
//		assert(deq.back(&deq) == 2);
//
//		assert(deq.size(&deq) == 3);

//		for (Deque_int_Iterator it = deq.begin(&deq);
//		     !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
//			printf("%d\n", it.deref(&it));
//		}

//		// Test decrement.
//		{
//			auto it = deq.end(&deq);
//			it.dec(&it);
//			assert(it.deref(&it) == 2);
//		}
//
//		// printf("Using at.\n");
//
//		for (size_t i = 0; i < 3; i++) {
//			printf("%d: %d\n", int(i), deq.at(&deq, i));
//		}

		deq.clear(&deq);

		deq.dtor(&deq);
	}

//	// Test equality.  It is undefined behavior if the two deques were constructed with different
//	// comparison functions.
//	{
//		Deque_int deq1, deq2;
//		Deque_int_ctor(&deq1, int_less);
//		Deque_int_ctor(&deq2, int_less);
//
//		deq1.push_back(&deq1, 1);
//		deq1.push_back(&deq1, 2);
//		deq1.push_back(&deq1, 3);
//		deq2.push_back(&deq2, 1);
//		deq2.push_back(&deq2, 2);
//		deq2.push_back(&deq2, 3);
//
//		assert(Deque_int_equal(deq1, deq2));
//
//		deq1.pop_back(&deq1);
//		assert(!Deque_int_equal(deq1, deq2));
//		deq1.push_back(&deq1, 4);
//		assert(!Deque_int_equal(deq1, deq2));
//
//		deq1.dtor(&deq1);
//		deq2.dtor(&deq2);
//	}
//
//	// Test performance.
//	{
//		std::default_random_engine e;
//		using rand = std::uniform_int_distribution<int>;
//		std::uniform_real_distribution<float> action;
//		Deque_int deq;
//		Deque_int_ctor(&deq, int_less);
//
//		for (int i = 0; i < 10000; i++) {
//			deq.push_back(&deq, i);
//		}
//
//		// In one end, out the other.
//		for (int i = 0; i < 20000000; i++) {
//			// fprintf(stderr, "iter: %d\n", i);
//			deq.push_back(&deq, i);
//			deq.pop_front(&deq);
//		}
//		for (int i = 0; i < 20000000; i++) {
//			deq.push_front(&deq, i);
//			deq.pop_back(&deq);
//		}
//
//		// To do some computation, to prevent compiler from optimizing out.
//		size_t sum = 0, max_size = 0;
//		// Random.
//		int pf = 0, pb = 0, pof = 0, pob = 0;
//		for (int i = 0; i < 10000000; i++) {
//			if (action(e) > .55) {
//				if (rand(0, 1)(e) == 0) {
//					deq.push_back(&deq, i);
//					pf++;
//				} else {
//					deq.push_front(&deq, i);
//					pb++;
//				}
//			} else {
//				if (deq.size(&deq) > 0) {
//					if (rand(0, 1)(e) == 0) {
//						deq.pop_back(&deq);
//						pob++;
//					} else {
//						deq.pop_front(&deq);
//						pof++;
//					}
//				}
//			}
//			max_size = std::max(deq.size(&deq), max_size);
//			// Randomly access one element.
//			if (deq.size(&deq) > 0) {
//				sum += deq.at(&deq, rand(0, deq.size(&deq) - 1)(e));
//			}
//		}
//		// Print it out to prevent optimizer from optimizing out the at() calls.
//		fprintf(devnull, "%lu", sum);
//		printf("%zu max size\n", max_size);
//		printf("%d push_backs, %d push_fronts, %d pop_backs, %d pop_fronts, %d size\n", pb, pf, pob, pof, (int) deq.size(&deq));
//		deq.dtor(&deq);
//	}
//
//	// Test random access performance
//	{
//		size_t sum = 0;
//		int lo = 0, hi = 10000000;
//		Deque_int deq;
//		Deque_int_ctor(&deq, int_less);
//
//		for(int i = lo; i < hi; i++) {
//			deq.push_back(&deq, i);
//		}
//
//		for(int i = lo; i < hi; i++) {
//			sum += deq.at(&deq, i);
//		}
//		printf("Sum of all integers between %d and %d calculated using a deque is %lu.\n", lo, hi, sum);
//		deq.dtor(&deq);
//	}
//
//	// Test sort.
//	// You must be able to work with the correct less-than function.
//	{
//		Deque_int deq;
//		Deque_int_ctor(&deq, int_less);
//		std::default_random_engine e;
//		using rand = std::uniform_int_distribution<int>;
//
//		for (int i = 0; i < 10000; i++) {
//			deq.push_back(&deq, rand(-1000000, 1000000)(e));
//		}
//
//		deq.sort(&deq, deq.begin(&deq), deq.end(&deq));
//
//		deq.dtor(&deq);
//	}
//
//
//	// Sorting Test 2
//	{
//		Deque_int deq1;
//		Deque_int_ctor(&deq1, int_less);
//
//		for (int i=0;i<10000;i++) {
//			deq1.push_back(&deq1, i);
//		}
//
//		for (int i=20000;i>=10000;i--) {
//			deq1.push_back(&deq1,i);
//		}
//
//		deq1.push_back(&deq1,20001);
//
//		auto iter1 =  deq1.end(&deq1);
//		iter1.dec(&iter1);
//
//		auto iter2 = deq1.begin(&deq1);
//
//		for (int i=0;i<10000;i++) {
//			iter2.inc(&iter2);
//		}
//
//		deq1.sort(&deq1, iter2,iter1);
//
//		Deque_int deq2;
//		Deque_int_ctor(&deq2 , int_less);
//
//		for(int i=0;i<=20001;i++) {
//			deq2.push_back(&deq2,i);
//		}
//
//		assert(Deque_int_equal(deq1, deq2));
//
//		deq1.dtor(&deq1);
//		deq2.dtor(&deq2);
//	}
//
//		// Performance testing for sorting
//		{
//
//			Deque_int deq1;
//			Deque_int_ctor(&deq1, int_less);
//
//			std::default_random_engine e;
//			using rand = std::uniform_int_distribution<int>;
//
//			for (int i = 0; i < 1000000; i++) {
//				deq1.push_back(&deq1, rand(-1000000, 1000000)(e));
//			}
//
//			auto iter1 = deq1.begin(&deq1);
//			auto iter2 = deq1.begin(&deq1);
//
//			for(int i=0;i<10;i++)
//				iter1.inc(&iter1);
//
//			for(int i=0;i<20;i++)
//				iter2.inc(&iter2);
//
//			for(int i=0;i<1000000;i++)
//				deq1.sort(&deq1, iter1,iter2);
//
//			deq1.dtor(&deq1);
//			//deq1.print(&deq1);
//		}

	int rv = fclose(devnull);
	assert(rv == 0);
}