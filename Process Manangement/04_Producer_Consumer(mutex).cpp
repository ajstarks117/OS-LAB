#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>
#include <iomanip>

using namespace std;

#define MAX_SIZE 5

queue<int> buffer;

pthread_mutex_t mutex1;
pthread_cond_t not_full;
pthread_cond_t not_empty;
pthread_mutex_t print_mtx;

int item = 0;

void* producer(void* arg) {
    int id = *((int*)arg);

    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex1);

        while (buffer.size() == MAX_SIZE) {
            pthread_cond_wait(&not_full, &mutex1);
        }

        item++;
        buffer.push(item);

        pthread_mutex_lock(&print_mtx);
        cout << left << setw(12) << ("Producer " + to_string(id))
             << setw(15) << "PRODUCE"
             << item << endl;
        pthread_mutex_unlock(&print_mtx);

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex1);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *((int*)arg);

    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex1);

        while (buffer.empty()) {
            pthread_cond_wait(&not_empty, &mutex1);
        }

        int val = buffer.front();
        buffer.pop();

        pthread_mutex_lock(&print_mtx);
        cout << left << setw(12) << ("Consumer " + to_string(id))
             << setw(15) << "CONSUME"
             << val << endl;
        pthread_mutex_unlock(&print_mtx);

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex1);

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

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&print_mtx, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    cout << "\n";
    cout << left << setw(12) << "Thread"
         << setw(15) << "Operation"
         << "Value" << endl;
    cout << "-----------------------------------" << endl;

    for (int i = 0; i < p; i++) {
        ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &ids[i]);
    }

    for (int i = 0; i < c; i++) {
        ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < p; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < c; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&print_mtx);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}