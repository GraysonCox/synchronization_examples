//
// Created by Grayson Cox on 11/11/19.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parbegin.h"
#include "rw_monitor.h"
#include "new_rw_monitor.h"

const int NUM_CYCLES = 10;

rw_monitor monitor;
//new_rw_monitor monitor;

void wait_for_a_bit() {
	int n = ((random() % 5) * 100000);
	usleep(n);
}

void read(int pid) {
	printf("r%d: reading\n", pid);
	wait_for_a_bit();
	printf("r%d: x\n", pid);
}

void write(int pid) {
	printf("w%d: writing\n", pid);
	wait_for_a_bit();
	printf("w%d: x\n", pid);
}

void *reader_process(void *arg) {
	int pid = atoi((char *) arg);
	for (int i = 0; i < NUM_CYCLES; i++) {

		monitor.begin_read();
		read(pid);
		monitor.end_read();

	}
	pthread_exit(nullptr);
}

void *writer_process(void *arg) {
	int pid = atoi((char *) arg);
	for (int i = 0; i < NUM_CYCLES; i++) {

		monitor.begin_write();
		write(pid);
		monitor.end_write();

	}
	pthread_exit(nullptr);
}

int main() {

	parbegin({
					 process(writer_process, (void *) "0"),
					 process(writer_process, (void *) "1"),

					 process(reader_process, (void *) "0"),
					 process(reader_process, (void *) "1"),
					 process(reader_process, (void *) "2")
			 });

	return 0;
}