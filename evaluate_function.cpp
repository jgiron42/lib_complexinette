//
// Created by joachim on 3/13/22.
//
#include "complexinette.hpp"

int my_waitpid(pid_t pid, int *status, int options, long long int timeout)
{
	int ret;
	long long int time = 0;
	while (!(ret = waitpid(pid, status, options | WNOHANG)) && time < timeout)
	{
		usleep(1000);
		time++;
	}
	return (time >= timeout);
}

namespace lib_complexinette {
	float evaluate_function(measurable_class *c) {
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
			ret += (float) (perf_count_stop(fd));
		}
		return (ret / NTEST);
	}
}