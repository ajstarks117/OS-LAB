#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <iomanip>

using namespace std;

pthread_mutex_t mtx;        
pthread_mutex_t read_mtx;   
pthread_mutex_t print_mtx;  

int read_count = 0;
int shared_data = 0;

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);

    while (true) {
        // Entry Section
        pthread_mutex_lock(&read_mtx);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&mtx); 
        }
        pthread_mutex_unlock(&read_mtx);

        // Critical Section (Reading)
        pthread_mutex_lock(&print_mtx);
        cout << left << setw(10) << ("Reader " + to_string(id))
             << setw(15) << "READ"
             << shared_data << endl;
        pthread_mutex_unlock(&print_mtx);

        sleep(1);

        // Exit Section
        pthread_mutex_lock(&read_mtx);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&mtx); 
        }
        pthread_mutex_unlock(&read_mtx);

        sleep(1); 
    }

    return NULL;
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);

    while (true) {
        pthread_mutex_lock(&mtx); 

        // Critical Section (Writing)
        shared_data++;

        pthread_mutex_lock(&print_mtx);
        cout << left << setw(10) << ("Writer " + to_string(id))
             << setw(15) << "WRITE"
             << shared_data << endl;
        pthread_mutex_unlock(&print_mtx);

        sleep(1);

        pthread_mutex_unlock(&mtx);

        sleep(2); 
    }

    return NULL;
}

int main() {
    int r, w;

    cout << "Enter number of Readers: ";
    cin >> r;

    cout << "Enter number of Writers: ";
    cin >> w;

    pthread_t readers[r], writers[w];

    // Separate ID arrays (IMPORTANT FIX)
    int reader_ids[r];
    int writer_ids[w];

    // Initialize mutex
    pthread_mutex_init(&mtx, NULL);
    pthread_mutex_init(&read_mtx, NULL);
    pthread_mutex_init(&print_mtx, NULL);

    // Table Header
    cout << "\n";
    cout << left << setw(10) << "Thread"
         << setw(15) << "Operation"
         << "Value" << endl;
    cout << "-----------------------------------\n";

    // Create reader threads
    for (int i = 0; i < r; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < w; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (runs forever)
    for (int i = 0; i < r; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < w; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutex (never reached)
    pthread_mutex_destroy(&mtx);
    pthread_mutex_destroy(&read_mtx);
    pthread_mutex_destroy(&print_mtx);

    return 0;
}