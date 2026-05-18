#include <iostream>
using namespace std;

int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    int pages[n];

    cout << "Enter page reference string: ";
    for(int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    int memory[frames];
    int recent[frames];

    // Initialize frames as empty
    for(int i = 0; i < frames; i++) {
        memory[i] = -1;
        recent[i] = -1;
    }

    int pageFaults = 0;
    int time = 0;

    for(int i = 0; i < n; i++) {

        bool found = false;

        // Check page hit
        for(int j = 0; j < frames; j++) {
            if(memory[j] == pages[i]) {
                found = true;
                recent[j] = time;
                break;
            }
        }

        // Page fault
        if(!found) {

            int replaceIndex = 0;

            // Find least recently used page
            for(int j = 1; j < frames; j++) {
                if(recent[j] < recent[replaceIndex]) {
                    replaceIndex = j;
                }
            }

            memory[replaceIndex] = pages[i];
            recent[replaceIndex] = time;

            pageFaults++;
        }

        time++;

        // Print memory frames
        cout << "Frames: ";

        for(int j = 0; j < frames; j++) {
            if(memory[j] != -1)
                cout << memory[j] << " ";
            else
                cout << "- ";
        }

        cout << endl;
    }

    cout << "Total Page Faults = "
         << pageFaults;

    return 0;
}