//
// Created by Grayson Cox on 10/25/19.
//

#ifndef RW_MONITOR_H
#define RW_MONITOR_H

#include <pthread.h>

class rw_monitor {
public:
	rw_monitor();

	virtual ~rw_monitor();

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


#endif //RW_MONITOR_H
