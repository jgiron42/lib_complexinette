//
// Created by joachim on 3/12/22.
//

#ifndef COMPLEXINETTE_COMPLEXINETTE_HPP
#define COMPLEXINETTE_COMPLEXINETTE_HPP
//#define _GNU_SOURCE
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <signal.h>
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
#include <cstring>
#include <errno.h>
#include <sched.h>
#ifndef NTEST
#define NTEST 20
#endif
#ifndef MAX_SIZE
#define MAX_SIZE 9
#endif
#define WORST_CASE
#include <cmath>
#include "measurable_concept.hpp"
//#define COMPLEXINETTE_DEBUG
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
		LINEARITHMIC,
		QUAD,
		CUB,
		EXP,

		TIMEOUT,
		ERROR,
		SIGNALED
	}	complexities;

	long long int perf_count_stop(int fd);
	int	perf_count_begin(pid_t pid);
	complexities aprox(std::map<int, float> &stats);

	float comp_const(int n, params p);
	float comp_log(int n, params p);
	float comp_sqrt(int n, params p);
	float comp_linear(int n, params p);
	float comp_linearithmic(int n, params p);
	float comp_quad(int n, params p);
	float comp_cub(int n, params p);
	float comp_exp(int n, params p);
	template <class C>
	complexities get_complexity();
	int my_waitpid(pid_t pid, int *status, int options, long long int timeout);
	template <class C>
	float	evaluate_function(measurable_class *c);
	extern float (*complexitiesf[])(int, params);
	extern std::string names[];

}
#include "templates.hpp"
#endif //COMPLEXINETTE_COMPLEXINETTE_HPP
