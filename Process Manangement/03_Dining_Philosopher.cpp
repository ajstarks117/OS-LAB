#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

const int N = 5;

sem_t forks[N]; // binary Sem
sem_t room; // counting Sem

pthread_mutex_t print_mutex;  //This prevents multiple threads from creating messy output

int step = 1;

// Thread-safe print
void print_table(int id, string operation) {
    pthread_mutex_lock(&print_mutex);

    cout << step++ << "\t\tPhilosopher " << id << "\t\t" << operation << endl;

    pthread_mutex_unlock(&print_mutex);
}

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (true) {
        print_table(id, "Thinking");
        usleep(500000);

        sem_wait(&room);

        sem_wait(&forks[id]);
        print_table(id, "Picks Left Fork");

        sem_wait(&forks[(id + 1) % N]);
        print_table(id, "Picks Right Fork");

        print_table(id, "Eating");
        usleep(500000);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        print_table(id, "Releases Forks");

        sem_post(&room);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    sem_init(&room, 0, 4);
    pthread_mutex_init(&print_mutex, NULL);

    cout << "Step\t\tProcess\t\t\tOperation\n";
    cout << "--------------------------------------------------------\n";

    // Create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}