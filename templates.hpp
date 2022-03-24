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
			if (ret == 0)
				return (ERROR);
			if (ret == -1)
				return (TIMEOUT);
			if (ret < 0)
				return (static_cast<enum e_complexities>(static_cast<int>(SIGNALED) - 1 - ((int)ret)));
#ifdef COMPLEXINETTE_DEBUG
			std::cout << powl(2, i) << " -> " << ret << std::endl;
#endif
			result[powl(2, i)] = ret;
		}
		return (aprox(result));
	}

	template <class C>
	float evaluate_function(C *c) {
		pid_t pid;
		float ret = 0;
		int	status;
		int fd;
		for (int i = 0; i < NTEST; ++i) {
			pid = fork();
			if (pid == -1)
				throw std::runtime_error( std::strerror(errno));
			if (pid == 0) {
				c->set();
				raise(SIGSTOP);
				(*c)();
				exit(0);
			}
			if (my_waitpid(pid, &status, WUNTRACED, 10000))
				return (0);
			if (WIFSTOPPED(status))
			{
				fd = perf_count_begin(pid);
				kill(pid, SIGCONT);
				if (my_waitpid(pid, &status, 0, 2000))
					return (-1);
			}
			else
				return (0);
			if (WIFSIGNALED(status))
				return (-1 - WTERMSIG(status));
#ifdef WORST_CASE
			{
				float tmp = (float) (perf_count_stop(fd));
				if (tmp > ret)
					ret = tmp;
			};
#else
			ret += (float) (perf_count_stop(fd));
#endif
		}
#ifdef WORST_CASE
		return (ret);
#else
		return (ret / NTEST);
#endif
	}
}

#endif //FT_CONTAINERS_COMPLEXINETTE_TEMPLATES_HPP
