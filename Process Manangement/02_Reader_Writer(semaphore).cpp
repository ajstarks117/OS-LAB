#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

const int R = 5;
const int W = 2;

sem_t mutex, wrt;
pthread_mutex_t print_mutex;

int readcnt = 0;

// Thread-safe print
void print_table(string process, int id, string operation) {
    pthread_mutex_lock(&print_mutex);
    cout << process << " " << id << "\t\t" << operation << endl;
    pthread_mutex_unlock(&print_mutex);
}

// Reader
void* reader(void* arg) {
    int id = *(int*)arg;

    while (true) {
        sem_wait(&mutex);
        readcnt++;

        if (readcnt == 1)
            sem_wait(&wrt);   // First reader blocks writers

        sem_post(&mutex);

        print_table("Reader", id, "Reading");
        usleep(500000);

        sem_wait(&mutex);
        readcnt--;

        if (readcnt == 0)
            sem_post(&wrt);   // Last reader allows writers

        sem_post(&mutex);

        usleep(500000);
    }
    return NULL;
}

// Writer
void* writer(void* arg) {
    int id = *(int*)arg;

    while (true) {
        sem_wait(&wrt);

        print_table("Writer", id, "Writing");
        usleep(700000);

        sem_post(&wrt);

        usleep(700000);
    }
    return NULL;
}

int main() {
    pthread_t r[R], w[W];
    int r_id[R], w_id[W];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&print_mutex, NULL);

    cout << "Process\t\tOperation\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < R; i++) {
        r_id[i] = i;
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    }

    for (int i = 0; i < W; i++) {
        w_id[i] = i;
        pthread_create(&w[i], NULL, writer, &w_id[i]);
    }

    for (int i = 0; i < R; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < W; i++)
        pthread_join(w[i], NULL);

    return 0;
}