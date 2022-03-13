//
// Created by joachim on 3/12/22.
//

#ifndef COMPLEXINETTE_I_MEASURABLE_CLASS_HPP
#define COMPLEXINETTE_I_MEASURABLE_CLASS_HPP

namespace lib_complexinette {
	class I_measurable_class {

		/**
		 * instanciate an object for the measure n
		 */
//	virtual constructor(int n) = 0;
		/**
		 * set the class for the next call
		 */
		virtual void set() = 0;

		/**
		 * the measured call (must contain only the instructions to measure)
		 */
		virtual void operator()(void) = 0;
	};
}

#endif //COMPLEXINETTE_I_MEASURABLE_CLASS_HPP
