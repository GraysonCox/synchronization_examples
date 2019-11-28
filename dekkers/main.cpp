#include<iostream>
#include<unistd.h>
#include "parbegin.h"

using namespace std;

#define SLEEP_TIME 1000000

bool flag[2];
int turn;

void critical_section(int id) {
	printf("%d: enter\n", id);
	usleep(SLEEP_TIME);
	printf("%d: done\n", id);
}

void *p0(void *arg) {
	while (true) {
		flag[0] = true;
		while (flag[1]) {
			if (turn == 1) {
				flag[0] = false;
				while (turn == 1);
				flag[0] = true;
			}
		}

		critical_section(0);

		turn = 1;
		flag[0] = false;
		// Remainder
	}
}

void *p1(void *arg) {
	while (true) {
		flag[1] = true;
		while (flag[0]) {
			if (turn == 0) {
				flag[1] = false;
				while (turn == 0);
				flag[1] = true;
			}
		}

		critical_section(1);

		turn = 0;
		flag[1] = false;
		// Remainder
	}
}

int main() {

	flag[0] = false;
	flag[1] = false;

	turn = 1;

	parbegin({
					 process(p0, nullptr),
					 process(p1, nullptr)
			 });

	return 0;
}
