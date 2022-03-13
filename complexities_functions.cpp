#include "complexinette.hpp"

namespace lib_complexinette
{

	float comp_const(int n, params p) { return (p.a); }

	float comp_log(int n, params p) { return (p.a + p.b * log(p.c + p.d * n)); }

	float comp_sqrt(int n, params p) { return (p.a + p.b * sqrt(p.c + p.d * n)); }

	float comp_linear(int n, params p) { return (p.a + p.b * n); }

	float comp_linearithmic(int n, params p) { return (p.a + p.b * (p.c + p.d * n) * log(p.c + p.d * n)); }

	float comp_quad(int n, params p) { return (p.a + p.b * (p.c + p.d * n) * (p.c + p.d * n)); }

	float comp_cub(int n, params p) { return (p.a + p.b * (p.c + p.d * n) * (p.c + p.d * n) * (p.c + p.d * n)); }

	float comp_exp(int n, params p) { return (p.a + p.b * exp(p.c + p.d * n)); }

	float comp_fact_rec(int n) {
		if (n < 0)
			return (INFINITY);
		if (n == 0)
			return (1);
		return (n * comp_fact_rec(n - 1));
	}

	float comp_fact(int n, params p) {
		return (p.a + p.b * comp_fact_rec(p.c + p.d * n));
	}
}