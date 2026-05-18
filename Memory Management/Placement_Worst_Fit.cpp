#include <iostream>
#include <vector>

using namespace std;

struct Allocation
{
    int process_no;
    int process_size;
    int block_no;
    int block_size;
    int remaining;
};

// -------- PRINT OUTPUT --------
void print_output(vector<Allocation> &result)
{
    cout << "\nALLOCATION TABLE:\n";

    cout << "Process\tProcess Size\tBlock No.\tOriginal Block\tRemaining Block\n";

    for(auto &r : result)
    {
        cout << "P" << r.process_no
             << "\t" << r.process_size
             << "\t\t";

        if(r.block_no == -1)
        {
            cout << "NOT ALLOCATED\n";
        }
        else
        {
            cout << r.block_no
                 << "\t\t"
                 << r.block_size
                 << "\t\t"
                 << r.remaining
                 << endl;
        }
    }
}

// -------- MAIN --------
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

    vector<Allocation> result;

    // Worst Fit Logic
    for(int i = 0; i < np; i++)
    {
        int worstIdx = -1;

        // Find largest suitable block
        for(int j = 0; j < nb; j++)
        {
            if(blocks[j] >= processes[i])
            {
                if(worstIdx == -1 ||
                   blocks[j] > blocks[worstIdx])
                {
                    worstIdx = j;
                }
            }
        }

        Allocation temp;

        temp.process_no = i + 1;
        temp.process_size = processes[i];

        if(worstIdx != -1)
        {
            temp.block_no = worstIdx + 1;

            temp.block_size = blocks[worstIdx];

            blocks[worstIdx] -= processes[i];

            temp.remaining = blocks[worstIdx];
        }
        else
        {
            temp.block_no = -1;
        }

        result.push_back(temp);
    }

    print_output(result);

    return 0;
}