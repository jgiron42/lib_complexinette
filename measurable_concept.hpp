//
// Created by joachim on 3/12/22.
//

#ifndef COMPLEXINETTE_I_MEASURABLE_CLASS_HPP
#define COMPLEXINETTE_I_MEASURABLE_CLASS_HPP
#include <unistd.h>
#include <stdlib.h>

// c++20 snif snif
//template <class C>
//concept Measurable = requires (C c, int n)
//{
//	{ delete new C(n) };
//	{c.n} -> std::same_as<long int>;
//	c.set();
//	c();
//};

namespace lib_complexinette {
	class measurable_class {
	public:
		long int n;
		/**
		 * instanciate an object for the measure n
		 */
		measurable_class() : n(0) {srand(time(NULL));};
		measurable_class(int n) : n(n) {};
		/**
		 * set the class for the next call
		 */
		virtual void set() {};

		/**
		 * the measured call (must contain only the instructions to measure)
		 */
		virtual void operator()(void) = 0;
	};
}

#endif //COMPLEXINETTE_I_MEASURABLE_CLASS_HPP
