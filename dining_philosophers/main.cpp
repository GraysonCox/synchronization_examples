//
// Created by Grayson Cox on 11/13/19.
//

#include <stdio.h>
#include <unistd.h>
#include <random>
#include "parbegin.h"
#include "fork_monitor.h"

const int NUM_PHILOSOPHERS = 5;

fork_monitor monitor(NUM_PHILOSOPHERS);

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