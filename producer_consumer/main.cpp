#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <unistd.h>
#include "../lib/parbegin/parbegin.h"
#include "bounded_buffer.h"

using namespace std;

const int RUN_TIME = 5;
const int NUM_CONSUMERS = 5;
const int BUF_SIZE = 3;

bounded_buffer<string> buf = bounded_buffer<string>(BUF_SIZE);
sem_t *my_mutex, *num_files, *space_left, *num_consumers;
int num_reads = 0;

// ---------- producer ----------

string produce_file() {
    sleep(random() % 2);
    string s = "YOOO!#" + to_string(random() % 100);
    printf("Produced '%s'\n", s.c_str());
    return s;
}

void *producer(void *arg) {
    string filename;

    for (int i = 0; i < RUN_TIME; i++) {

        filename = produce_file();

        sem_wait(space_left);
        sem_wait(my_mutex);

        buf.add_to_buffer(filename);

        sem_post(my_mutex);
        sem_post(num_files);

    }
    return nullptr;
}

// ---------- consumer ----------

void copy_file(string file) {
    // Do shit with file, I guess.
    sleep(random() % 2);
}

// This one is most correct.
void *consumer(void *arg) {
    int id = atoi((char *)arg);
    string file_received;
    int sequence_num = 0;
    for (int i = 0; i < RUN_TIME; i++) {

        sem_wait(num_consumers);
        sem_wait(num_files);
        sem_wait(my_mutex);
        file_received = buf.copy_first_item_from_buffer();
        copy_file(file_received);
        printf("%d: Copied '%s'\n", id, file_received.c_str());
        num_reads++;
        sequence_num = num_reads;
        if (sequence_num == NUM_CONSUMERS) {
            buf.remove_first_item_from_buffer();
            sem_post(space_left);
            num_reads = 0;
        }
        sem_post(my_mutex);

        if (sequence_num == NUM_CONSUMERS) {
            for (int x = 0; x < NUM_CONSUMERS; x++) {
                sem_post(num_consumers);
            }
        } else {
            sem_post(num_files);
        }
    }
    return nullptr;
}

void *consumer_correct(void *arg) {
    int id = *((int *) arg);
    string file_received;
    int sequence_num = 0;
    for (int i = 0; i < RUN_TIME; i++) {

        sem_wait(num_consumers);
        sem_wait(num_files);
        sem_wait(my_mutex);
        file_received = buf.copy_first_item_from_buffer();
        printf("%d: Copied '%s'\n", id, file_received.c_str());
        num_reads++;
        sequence_num = num_reads;
        if (sequence_num == NUM_CONSUMERS) {
            buf.remove_first_item_from_buffer();
            sem_post(space_left);
            num_reads = 0;
        }
        sem_post(my_mutex);
        copy_file(file_received);
        if (sequence_num == NUM_CONSUMERS) {
            for (int x = 0; x < NUM_CONSUMERS; x++) {
                sem_post(num_consumers);
            }
        } else {
            sem_post(num_files);
        }
    }
    return nullptr;
}

// ---------- main ----------

int main() {

    sem_unlink("/s_sem");
    sem_unlink("/c_sem");
    sem_unlink("/space_left_sem");
    sem_unlink("/num_consumers_sem");

    my_mutex = sem_open("/s_sem", O_CREAT, 0644, 1);
    num_files = sem_open("/c_sem", O_CREAT, 0644, 0);
    space_left = sem_open("/space_left_sem", O_CREAT, 0644, BUF_SIZE);
    num_consumers = sem_open("/num_consumers_sem", O_CREAT, 0644, NUM_CONSUMERS);

//    pthread_t tids[NUM_CONSUMERS + 1];
//    int ids[NUM_CONSUMERS];
//    for (int i = 0; i < NUM_CONSUMERS; i++) {
//        ids[i] = i;
//    }
//    pthread_create(&tids[0], nullptr, producer, &tids[0]);
//    for (int i = 1; i <= NUM_CONSUMERS; i++) {
//        pthread_create(&tids[i], nullptr, consumer, (void *)&ids[i-1]);
//    }
//    for (int i = 0; i <= NUM_CONSUMERS; i++) {
//        pthread_join(tids[i], nullptr);
//    }

    parbegin({
        process(producer, nullptr),

        process(consumer, (void *)"0"),
        process(consumer, (void *)"1"),
        process(consumer, (void *)"2"),
        process(consumer, (void *)"3"),
        process(consumer, (void *)"4")
    });

    sem_unlink("/s_sem");
    sem_unlink("/c_sem");
    sem_unlink("/space_left_sem");
    sem_close(my_mutex);
    sem_close(num_files);
    sem_close(space_left);

    return 0;
}