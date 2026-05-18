#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Check if page is already in frames
bool isHit(int page, const vector<int>& frames) {
    for (int p : frames) {
        if (p == page) return true;
    }
    return false;
}

// Function to print frames
void printFrames(const vector<int>& frames, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (i < frames.size())
            cout << frames[i] << " ";
        else
            cout << "- ";
    }
}

// FIFO Algorithm
void fifo(const vector<int>& pages, int capacity) {
    vector<int> frames;
    int pageFaults = 0, index = 0;

    cout << "\nFIFO Algorithm:\n";
    cout << "Page\tFrames\t\tStatus\n";

    for (int page : pages) {
        cout << page << "\t";

        if (!isHit(page, frames)) {
            pageFaults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                frames[index] = page;
                index = (index + 1) % capacity;
            }

            printFrames(frames, capacity);
            cout << "\tFault\n";
        } else {
            printFrames(frames, capacity);
            cout << "\tHit\n";
        }
    }

    cout << "Total Page Faults (FIFO): " << pageFaults << "\n";
}

// LRU Algorithm
void lru(const vector<int>& pages, int capacity) {
    vector<int> frames;
    vector<int> lastUsed(capacity, 0);
    int pageFaults = 0, time = 0;

    cout << "\nLRU Algorithm:\n";
    cout << "Page\tFrames\t\tStatus\n";

    for (int page : pages) {
        time++;
        cout << page << "\t";

        bool hit = false;

        for (int i = 0; i < frames.size(); i++) {
            if (frames[i] == page) {
                hit = true;
                lastUsed[i] = time;
                break;
            }
        }

        if (!hit) {
            pageFaults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
                lastUsed[frames.size() - 1] = time;
            } else {
                int lruIndex = 0;
                for (int i = 1; i < capacity; i++) {
                    if (lastUsed[i] < lastUsed[lruIndex]) {
                        lruIndex = i;
                    }
                }
                frames[lruIndex] = page;
                lastUsed[lruIndex] = time;
            }

            printFrames(frames, capacity);
            cout << "\tFault\n";
        } else {
            printFrames(frames, capacity);
            cout << "\tHit\n";
        }
    }

    cout << "Total Page Faults (LRU): " << pageFaults << "\n";
}

// Optimal Algorithm
void optimal(const vector<int>& pages, int capacity) {
    vector<int> frames;
    int pageFaults = 0;

    cout << "\nOptimal Algorithm:\n";
    cout << "Page\tFrames\t\tStatus\n";

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << page << "\t";

        if (!isHit(page, frames)) {
            pageFaults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                int replaceIndex = -1;
                int farthest = -1;

                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (frames[j] == pages[k]) break;
                    }

                    if (k == pages.size()) { // not used again
                        replaceIndex = j;
                        break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = page;
            }

            printFrames(frames, capacity);
            cout << "\tFault\n";
        } else {
            printFrames(frames, capacity);
            cout << "\tHit\n";
        }
    }

    cout << "Total Page Faults (Optimal): " << pageFaults << "\n";
}

int main() {
    int capacity, n;

    cout << "Enter number of frames: ";
    cin >> capacity;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    fifo(pages, capacity);
    lru(pages, capacity);
    optimal(pages, capacity);

    return 0;
}