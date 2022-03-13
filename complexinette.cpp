#include "complexinette.hpp"

namespace lib_complexinette
{
	int ntest;

	template <class C>
	float	evaluate_function(C c)
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
	}

	template <class C>
	lib_complexinette::complexities get_complexity(int n)
	{
		std::map<int, float> result;
		ntest = n;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			float ret = evaluate_function(C(powl(10, i)));
#ifdef COMPLEXINETTE_DEBUG
			std::cout << powl(10, i) << " -> " << ret << std::endl;
#endif
			result[powl(10, i)] = ret;
		}
		return (aprox(result));
	}
}