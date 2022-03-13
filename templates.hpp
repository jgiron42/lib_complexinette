//
// Created by joachim on 3/13/22.
//

#ifndef FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP
#define FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP
#include "complexinette.hpp"

namespace lib_complexinette
{

	template <class C>
	complexities get_complexity()
	{
		std::map<int, float> result;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			float ret = evaluate_function(new C(powl(2, i)));
#ifdef COMPLEXINETTE_DEBUG
			std::cout << powl(2, i) << " -> " << ret << std::endl;
#endif
			result[powl(2, i)] = ret;
		}
		return (aprox(result));
	}
}

#endif //FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP