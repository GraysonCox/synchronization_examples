#ifndef PARBEGIN_H
#define PARBEGIN_H

#include <initializer_list>
#include <functional>
#include <pthread.h>

class process {
public:
	void *(*p)(void *);

	void *arg;

	process(void *(*p)(void *), void *arg);
};

void parbegin(std::initializer_list<process> processes);

#endif //PARBEGIN_H
