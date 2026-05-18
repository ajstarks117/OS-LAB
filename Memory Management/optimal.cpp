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

    // Initialize memory
    for(int i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    int pageFaults = 0;

    for(int i = 0; i < n; i++) {

        bool found = false;

        // Check page hit
        for(int j = 0; j < frames; j++) {
            if(memory[j] == pages[i]) {
                found = true;
                break;
            }
        }

        // Page fault
        if(!found) {

            int replaceIndex = -1;
            int farthest = i + 1;

            // Find page to replace
            for(int j = 0; j < frames; j++) {

                int k;

                for(k = i + 1; k < n; k++) {
                    if(memory[j] == pages[k]) {
                        break;
                    }
                }

                // Page never used again
                if(k == n) {
                    replaceIndex = j;
                    break;
                }

                // Farthest future use
                if(k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            // If empty frame exists
            if(replaceIndex == -1) {
                replaceIndex = 0;
            }

            memory[replaceIndex] = pages[i];

            pageFaults++;
        }

        // Print frame status
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