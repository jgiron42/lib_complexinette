//
// Created by joachim on 3/13/22.
//
#include "complexinette.hpp"

namespace lib_complexinette {
	float evaluate_function(measurable_class *c) {
		float ret = 0;
		int fd;
		for (int i = 0; i < NTEST; ++i) {
			c->set();
			fd = perf_count_begin();
			(*c)();
			ret += (float) (perf_count_stop(fd));
		}
		return (ret / NTEST);
	}
}