//
// Created by joachim on 3/13/22.
//

#ifndef FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP
#define FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP
#include "complexinette.hpp"

namespace lib_complexinette
{

	template <class C>
	float	evaluate_function(C c, int ntest)
	{
		float ret = 0;
		int fd;
		for (int i = 0; i < ntest; ++i)
		{
			c.set();
			fd = perf_count_begin();
			c();
			ret += (float)(perf_count_stop(fd));
		}
		return (ret / ntest);
	}template <class C>

	complexities get_complexity(int ntest)
	{
		std::map<int, float> result;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			float ret = evaluate_function(C(powl(10, i)), ntest);
#ifdef COMPLEXINETTE_DEBUG
			std::cout << powl(10, i) << " -> " << ret << std::endl;
#endif
			result[powl(10, i)] = ret;
		}
		return (aprox(result));
	}
}

#endif //FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP
