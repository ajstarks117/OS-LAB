#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int nb, np;

    cout << "Enter number of memory blocks: ";
    cin >> nb;

    vector<int> blocks(nb);

    cout << "Enter block sizes:\n";

    for(int i = 0; i < nb; i++)
        cin >> blocks[i];

    cout << "\nEnter number of processes: ";
    cin >> np;

    vector<int> processes(np);

    cout << "Enter process sizes:\n";

    for(int i = 0; i < np; i++)
        cin >> processes[i];

    cout << "\nALLOCATION TABLE:\n";

    cout << "Process\tSize\tBlock\tRemaining\n";

    for(int i = 0; i < np; i++)
    {
        int best = -1;
        int minBlock = INT_MAX;

        // Find smallest suitable block
        for(int j = 0; j < nb; j++)
        {
            if(blocks[j] >= processes[i] &&
               blocks[j] < minBlock)
            {
                minBlock = blocks[j];

                best = j;
            }
        }

        if(best != -1)
        {
            cout << "P" << i + 1
                 << "\t" << processes[i]
                 << "\t" << best + 1
                 << "\t" << blocks[best] - processes[i]
                 << endl;

            blocks[best] -= processes[i];
        }
        else
        {
            cout << "P" << i + 1
                 << "\t" << processes[i]
                 << "\tNOT ALLOCATED\n";
        }
    }

    return 0;
}