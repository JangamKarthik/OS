#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

// shared data
int data = 0;

// reader and writer semaphores
sem_t read_mutex, mutex;

// number of active reader threads
int readers = 0;

// reader thread function
void* reader(void* arg) {
    int iterations = *((int*) arg); // number of iterations
    while (iterations--) {
        sem_wait(&read_mutex); // enter reader priority section
        readers++; // increment number of active reader threads
        if (readers == 1) { // if this is the first active reader thread
            sem_wait(&mutex); // acquire the shared data lock
        }
        sem_post(&read_mutex); // leave reader priority section
        // read the shared data
        cout << "Reader " << pthread_self() << " read data: " << ::data << endl;
        sem_wait(&read_mutex); // enter reader priority section
        readers--; // decrement number of active reader threads
        if (readers == 0) { // if there are no active reader threads
            sem_post(&mutex); // release the shared data lock
        }
        sem_post(&read_mutex); // leave reader priority section
        usleep(1000000); // wait for 1 second
    }
    pthread_exit(NULL);
}

// writer thread function
void* writer(void* arg) {
    int iterations = *((int*) arg); // number of iterations
    while (iterations--) {
        sem_wait(&mutex); // acquire the shared data lock
        // write to the shared data
        ::data = rand() % 100;
        cout << "Writer " << pthread_self() << " wrote data: " <<::data << endl;
        sem_post(&mutex); // release the shared data lock
        usleep(1000000); // wait for 1 second
    }
    pthread_exit(NULL);
}

int main() {
    // initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&read_mutex, 0, 1);

    // get number of iterations from user
    int iterations;
    cout << "Enter the number of iterations: ";
    cin >> iterations;

    // create reader and writer threads
    pthread_t reader_thread1, reader_thread2, writer_thread1, writer_thread2;
    pthread_create(&reader_thread1, NULL, reader, &iterations);
    pthread_create(&reader_thread2, NULL, reader, &iterations);
    pthread_create(&writer_thread1, NULL, writer, &iterations);
    pthread_create(&writer_thread2, NULL, writer, &iterations);

    // wait for threads to finish
    pthread_join(reader_thread1, NULL);
    pthread_join(reader_thread2, NULL);
    pthread_join(writer_thread1, NULL);
    pthread_join(writer_thread2, NULL);

    // destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&read_mutex);

    return 0;
}

