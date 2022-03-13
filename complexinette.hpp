//
// Created by joachim on 3/12/22.
//

#ifndef COMPLEXINETTE_COMPLEXINETTE_HPP
#define COMPLEXINETTE_COMPLEXINETTE_HPP
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <asm/unistd.h>
#include <string>
#include <unistd.h>
#include <set>
#include <map>
#include <iomanip>
#include <iostream>
#include <vector>
#ifndef NTEST
#define NTEST 10
#endif
#ifndef MAX_SIZE
#define MAX_SIZE 6
#endif
#include <cmath>

namespace lib_complexinette
{
	typedef struct s_params {
		float a;
		float b;
		float c;
		float d;
	} params;

	typedef enum e_complexities {
		NONE = -1,
		CONST,
		LOG,
		SQRT,
		LINEAR,
		NLOGN,
		QUAD,
		CUB,
		EXP
	}	complexities;

	long long int perf_count_stop(int fd);
	int	perf_count_begin();
	complexities aprox(std::map<int, float> &stats);

	float comp_const(int n, params p);
	float comp_log(int n, params p);
	float comp_sqrt(int n, params p);
	float comp_linear(int n, params p);
	float comp_linearithmic(int n, params p);
	float comp_quad(int n, params p);
	float comp_cub(int n, params p);
	float comp_exp(int n, params p);
	complexities get_complexity(int n);

	extern float (*complexitiesf[])(int, params);
	extern std::string names[];

	extern int ntest;
}
#endif //COMPLEXINETTE_COMPLEXINETTE_HPP
