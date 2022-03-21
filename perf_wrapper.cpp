#include "complexinette.hpp"

namespace lib_complexinette {
	static long
	perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
					int cpu, int group_fd, unsigned long flags) {
		int ret;

		ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
					  group_fd, flags);
		return ret;
	}

	int perf_count_begin(pid_t pid) {
		int fd;
		struct perf_event_attr conf = {
				.type = PERF_TYPE_HARDWARE,
				.size = sizeof(struct perf_event_attr),
				.config = PERF_COUNT_HW_INSTRUCTIONS,
				.disabled = 1,
				.exclude_kernel = 1,
				.exclude_hv = 1
		};

		fd = perf_event_open(&conf, pid, -1, -1, 0);
		if (fd == -1) {
			perror("complexinette: perf");
			exit(1);
		}

		ioctl(fd, PERF_EVENT_IOC_RESET, 0);
		ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
		return (fd);
	}

	long long int perf_count_stop(int fd) {
		ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
		int ret;
		long long int count;
		ret = read(fd, &count, sizeof(long long));
		close(fd);
		if (ret == -1)
			return (-1);
		return (count);
	}
}