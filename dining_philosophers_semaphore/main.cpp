//
// Created by Grayson Cox on 11/13/19.
//

#include <stdio.h>
#include <unistd.h>
#include <random>
#include "parbegin.h"

const int NUM_PHILOSOPHERS = 5;

typedef enum {
	THINKING,
	HUNGRY,
	EATING
} state_t;

sem_t *self[NUM_PHILOSOPHERS];
sem_t *m;
state_t states[NUM_PHILOSOPHERS];

void wait_for_a_bit() {
	int n = ((random() % 5) * 100000);
	usleep(n);
}

void think(int pid) {
	printf("%d: Thinking\n", pid);
	wait_for_a_bit();
	printf("%d: Done thinking\n", pid);
}

void eat(int pid) {
	fprintf(stderr, "%d: Eating\n", pid);
	wait_for_a_bit();
	fprintf(stderr, "%d: Done eating\n", pid);
}

void test(int pid) {
	if (states[pid] == HUNGRY
		&& states[right(pid)] != EATING
		&& states[left(pid)] != EATING) {
		states[pid] = EATING;
		sem_post(self[pid]);
	}
}

void pickup_forks(int pid) {
	sem_wait(m);
	states[pid] = HUNGRY;
	test(pid);
	sem_signal(m);
	sem_wait(self[pid]);
}

void release_forks(int pid) {
	sem_wait(m);
	states[pid] = THINKING;
	test(left(pid));
	test(right(pid));
	sem_post(m);
}

void *philosopher(void *arg) {
	int pid = atoi((char *) arg);
	while (true) {
		think(pid);
		monitor.pickup_forks(pid);
		eat(pid);
		monitor.release_forks(pid);
	}
}

int main() {

	parbegin({
					 process(philosopher, (void *) "0"),
					 process(philosopher, (void *) "1"),
					 process(philosopher, (void *) "2"),
					 process(philosopher, (void *) "3"),
					 process(philosopher, (void *) "4")
			 });

	return 0;
}