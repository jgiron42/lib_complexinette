//
// Created by joachim on 3/13/22.
//
#include "complexinette.hpp"

namespace lib_complexinette {
	int my_waitpid(pid_t pid, int *status, int options, long long int timeout) {
		int ret;
		long long int time = 0;
		while (!(ret = waitpid(pid, status, options | WNOHANG)) && time < timeout) {
			usleep(1000);
			time++;
		}
		return (time >= timeout);
	}
}