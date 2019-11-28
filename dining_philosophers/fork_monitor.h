//
// Created by Grayson on 11/13/19.
//

#ifndef SYNCHRONIZATION_EXAMPLES_FORK_MONITOR_H
#define SYNCHRONIZATION_EXAMPLES_FORK_MONITOR_H

#include <pthread.h>
#include <vector>

typedef enum {
	THINKING,
	HUNGRY,
	EATING
} state_t;

class fork_monitor {
public:
	fork_monitor(int numPhilosophers);

	virtual ~fork_monitor();

	void pickup_forks(int pid);
	void release_forks(int pid);

private:
	int num_philosophers;
	state_t *states;
	pthread_mutex_t m;
	std::vector<pthread_cond_t> self;
	int left(int pid);
	int right(int pid);
	void test(int pid);
};


#endif //SYNCHRONIZATION_EXAMPLES_FORK_MONITOR_H
