#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore.h>

using namespace std;

const int BUFFER_SIZE = 5; // Size of the buffer
int buffer[BUFFER_SIZE] = {0}; // The buffer
sem_t mutex, empty, full; // Semaphores for synchronization

const int MAX_ITEMS = 10; // Maximum number of items to produce/consume
int num_produced = 0; // Number of items produced
int num_consumed = 0; // Number of items consumed

// Producer function
void producer() {
    int item = 1;
    while (num_produced < MAX_ITEMS) {
        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        // Acquire the mutex
        sem_wait(&mutex);
        // Produce an item and add it to the buffer
        buffer[(item - 1) % BUFFER_SIZE] = item;
        cout << "Producer produced item " << item << endl;
        item++;
        num_produced++;
        // Release the mutex
        sem_post(&mutex);
        // Signal that there is a full slot in the buffer
        sem_post(&full);
        // Sleep for some time to simulate work
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Consumer function
void consumer() {
    while (num_consumed < MAX_ITEMS) {
        // Wait for a full slot in the buffer
        sem_wait(&full);
        // Acquire the mutex
        sem_wait(&mutex);
        // Consume an item from the buffer
        int item = buffer[0];
        for (int i = 1; i < BUFFER_SIZE; i++) {
            buffer[i - 1] = buffer[i];
        }
        buffer[BUFFER_SIZE - 1] = 0;
        cout << "Consumer consumed item " << item << endl;
        num_consumed++;
        // Release the mutex
        sem_post(&mutex);
        // Signal that there is an empty slot in the buffer
        sem_post(&empty);
        // Sleep for some time to simulate work
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    // Initialize the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create the producer and consumer threads
    thread producer_thread(producer);
    thread consumer_thread(consumer);

    // Wait for the threads to finish
    producer_thread.join();
    consumer_thread.join();

    // Clean up the semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
