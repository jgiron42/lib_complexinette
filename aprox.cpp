#include "complexinette.hpp"

namespace lib_complexinette {

	float (*complexitiesf[])(int, params) = {
			&comp_const,
			&comp_log,
			&comp_sqrt,
			&comp_linear,
			&comp_linearithmic,
			&comp_quad,
			&comp_cub,
			&comp_exp,
			//			&comp_fact,
			NULL
	};

	std::string names[] = {
			"constant",
			"logarithmic",
			"square root",
			"linear",
			"linearithmic",
			"quadratic",
			"cubic",
			"exponential",
			//			"factorial",
	};

	float evaluate_R(std::map<int, float> &result, float (*f)(int, params), params p) {
		float a = 0;
		float b = 0;
		float tmp;
		for (auto i: result) {
			tmp = (f(i.first, p) - i.second);
			a += tmp * tmp;
			b += i.second * i.second;
		}
		return (sqrt(a / b));
	}

	float non_linear_regression(std::map<int, float> &result, float (*f)(int, params), params &p) {
		int it = 100000;
		float current_R = evaluate_R(result, f, p);
		float *current_param;
		float precision = 1;

		while (it > 0 && current_R != 0) {
			it--;
			current_param = (float *) &p + it % 4;
			*current_param += precision;
			if (it % 2 && *current_param == 0) // param is a factor
				*current_param -= precision;
			else if (evaluate_R(result, f, p) >= current_R)
				*current_param -= precision;
			else {
				current_R = evaluate_R(result, f, p);
				continue;
			}
			*current_param -= precision;
			if (it % 2 && *current_param == 0) // param is a factor
				*current_param += precision;
			else if (evaluate_R(result, f, p) >= current_R)
				*current_param += precision;
			current_R = evaluate_R(result, f, p);
		}
		return (current_R);
	}

	complexities aprox(std::map<int, float> &stats) {
		params p = {0, 1, 0, 1};
		float min = INFINITY;
		 complexities result = NONE;
		for (int i = 0; complexitiesf[i]; i++) {
			float ret = non_linear_regression(stats, complexitiesf[i], p);
#ifdef COMPLEXINETTE_DEBUG
			std::cout << std::left << std::setw(20) << names[i]
					  << "R = " << std::setw(15) << ret
					  << "a = " << std::setw(10) << p.a << "b = " << std::setw(10) << p.b << "c = " << std::setw(10)
					  << p.c << "d = " << std::setw(10) << p.d << std::endl;
#endif
			if (fabs(ret) < min) {
				min = fabs(ret);
				result = (complexities)i;
			}
			p = (params) {0, 1, 0, 1};
		}
		return (result);
	}
}