//
// Created by Grayson on 11/13/19.
//

#include "fork_monitor.h"

fork_monitor::fork_monitor(int numPhilosophers) : num_philosophers(numPhilosophers) {
	states = new state_t[numPhilosophers];
	pthread_cond_t cond;
	for (int i = 0; i < numPhilosophers; i++) {
		states[i] = THINKING;
		pthread_cond_init(&cond, nullptr);
		self.push_back(cond);
	}
	pthread_mutex_init(&m, nullptr);
}

fork_monitor::~fork_monitor() {
	for (auto cond : self) {
		pthread_cond_destroy(&cond);
	}
	pthread_mutex_destroy(&m);
}

int fork_monitor::left(int pid) {
	return (pid + num_philosophers - 1) % num_philosophers;
}

int fork_monitor::right(int pid) {
	return (pid + 1) % num_philosophers;
}

void fork_monitor::test(int pid) {
	if (states[pid] == HUNGRY
		&& states[right(pid)] != EATING
		&& states[left(pid)] != EATING
			) {
		states[pid] = EATING;
		pthread_cond_signal(&self.at(pid));
	}
}

void fork_monitor::pickup_forks(int pid) {
	pthread_mutex_lock(&m);
	states[pid] = HUNGRY;
	test(pid);
	if (states[pid] != EATING) {
		pthread_cond_wait(&self.at(pid), &m);
	}
	pthread_mutex_unlock(&m);
}

void fork_monitor::release_forks(int pid) {
	pthread_mutex_lock(&m);
	states[pid] = THINKING;
	test(right(pid));
	test(left(pid));
	pthread_mutex_unlock(&m);
}


