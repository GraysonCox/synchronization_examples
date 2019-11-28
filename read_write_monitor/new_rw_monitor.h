//
// Created by Grayson on 11/13/19.
//

#ifndef SYNCHRONIZATION_EXAMPLES_NEW_RW_MONITOR_H
#define SYNCHRONIZATION_EXAMPLES_NEW_RW_MONITOR_H

#include <pthread.h>

class new_rw_monitor {
public:
	new_rw_monitor();

	virtual ~new_rw_monitor();

	void begin_read();

	void end_read();

	void begin_write();

	void end_write();

private:
	int reader_count, num_waiting_readers;
	bool busy;
	pthread_mutex_t m;
	pthread_cond_t okay_to_read, okay_to_write;
};

#endif //SYNCHRONIZATION_EXAMPLES_NEW_RW_MONITOR_H
