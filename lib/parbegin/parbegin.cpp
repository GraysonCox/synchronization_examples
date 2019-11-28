#include "parbegin.h"

void parbegin(std::initializer_list<process> processes) {
	pthread_t tids[processes.size()];
	size_t i = 0;
	for (auto p : processes) {
		pthread_create(&tids[i], nullptr, p.p, p.arg);
		i++;
	}
	for (i = 0; i < processes.size(); i++) {
		pthread_join(tids[i], nullptr);
	}
}

process::process(void *(*p)(void *), void *arg) : p(p), arg(arg) {}