#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>
#include <iomanip>
#include <semaphore.h>

using namespace std;

#define MAX_SIZE 5

queue<int> buffer;

sem_t empty_slots;   
sem_t filled_slots;  

pthread_mutex_t mutex1;
pthread_mutex_t print_mtx;

int item = 0;

void* producer(void* arg) {

    int id = *((int*)arg);

    for (int i = 1; i <= 5; i++) {

        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex1);

        item++;
        buffer.push(item);

        pthread_mutex_lock(&print_mtx);

        cout << left << setw(12)
             << ("Producer " + to_string(id))
             << setw(15)
             << "PRODUCE"
             << item << endl;

        pthread_mutex_unlock(&print_mtx);

        pthread_mutex_unlock(&mutex1);

        sem_post(&filled_slots);

        sleep(1);
    }

    return NULL;
}

void* consumer(void* arg) {

    int id = *((int*)arg);

    for (int i = 1; i <= 5; i++) {

        sem_wait(&filled_slots);
        pthread_mutex_lock(&mutex1);

        int val = buffer.front();
        buffer.pop();

        pthread_mutex_lock(&print_mtx);

        cout << left << setw(12)
             << ("Consumer " + to_string(id))
             << setw(15)
             << "CONSUME"
             << val << endl;

        pthread_mutex_unlock(&print_mtx);

        pthread_mutex_unlock(&mutex1);

        sem_post(&empty_slots);

        sleep(1);
    }

    return NULL;
}

int main() {

    int p, c;

    cout << "Enter number of Producers: ";
    cin >> p;

    cout << "Enter number of Consumers: ";
    cin >> c;

    pthread_t producers[p], consumers[c];

    int ids[p > c ? p : c];

    // Initialize Mutex
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&print_mtx, NULL);

    // Initialize Semaphores
    sem_init(&empty_slots, 0, MAX_SIZE);
    sem_init(&filled_slots, 0, 0);

    cout << "\n";

    cout << left
         << setw(12) << "Thread"
         << setw(15) << "Operation"
         << "Value" << endl;

    cout << "-----------------------------------" << endl;

    for (int i = 0; i < p; i++) {

        ids[i] = i + 1;

        pthread_create(&producers[i],
                       NULL,
                       producer,
                       &ids[i]);
    }

    for (int i = 0; i < c; i++) {

        ids[i] = i + 1;

        pthread_create(&consumers[i],
                       NULL,
                       consumer,
                       &ids[i]);
    }

    for (int i = 0; i < p; i++) {

        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < c; i++) {

        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&print_mtx);

    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);

    return 0;
}