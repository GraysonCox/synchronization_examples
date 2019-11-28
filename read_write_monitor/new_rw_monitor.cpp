//
// Created by Grayson Cox on 11/13/19.
//

#include "new_rw_monitor.h"

new_rw_monitor::new_rw_monitor() {
	reader_count = 0;
	busy = false;
	num_waiting_readers = 0;
	pthread_mutex_init(&m, nullptr);
	pthread_cond_init(&okay_to_read, nullptr);
	pthread_cond_init(&okay_to_write, nullptr);
}

new_rw_monitor::~new_rw_monitor() {
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&okay_to_read);
	pthread_cond_destroy(&okay_to_write);
}

void new_rw_monitor::begin_read() {
	pthread_mutex_lock(&m);
	num_waiting_readers++;
	while (busy) {
		pthread_cond_wait(&okay_to_read, &m);
	}
	num_waiting_readers--;
	reader_count++;
	pthread_mutex_unlock(&m);
}

void new_rw_monitor::end_read() {
	pthread_mutex_lock(&m);
	reader_count--;
	if (reader_count == 0) {
		pthread_cond_signal(&okay_to_write);
	}
	pthread_mutex_unlock(&m);
}

void new_rw_monitor::begin_write() {
	pthread_mutex_lock(&m);
	while (busy || reader_count != 0) {
		pthread_cond_wait(&okay_to_write, &m);
	}
	busy = true;
	pthread_mutex_unlock(&m);
}

void new_rw_monitor::end_write() {
	pthread_mutex_lock(&m);
	busy = false;
	if (num_waiting_readers == 0) {
		pthread_cond_signal(&okay_to_write);
	} else {
		pthread_cond_signal(&okay_to_read);
	}
	pthread_mutex_unlock(&m);
}
