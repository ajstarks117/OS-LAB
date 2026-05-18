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

// -------- PRINT BLOCKS --------
void print_blocks(vector<int> &blocks)
{
    cout << "\nMEMORY BLOCKS:\n";

    cout << "Block No.\tSize\n";

    for(int i = 0; i < blocks.size(); i++)
    {
        cout << i + 1
             << "\t\t"
             << blocks[i]
             << endl;
    }
}

// -------- PRINT PROCESSES --------
void print_processes(vector<int> &processes)
{
    cout << "\nPROCESSES:\n";

    cout << "Process No.\tSize\n";

    for(int i = 0; i < processes.size(); i++)
    {
        cout << "P" << i + 1
             << "\t\t"
             << processes[i]
             << endl;
    }
}

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

    print_blocks(blocks);

    print_processes(processes);

    vector<Allocation> result;

    // First Fit Logic
    for(int i = 0; i < np; i++)
    {
        bool allocated = false;

        for(int j = 0; j < nb; j++)
        {
            // FIRST suitable block
            if(blocks[j] >= processes[i])
            {
                Allocation temp;

                temp.process_no = i + 1;

                temp.process_size = processes[i];

                temp.block_no = j + 1;

                temp.block_size = blocks[j];

                blocks[j] -= processes[i];

                temp.remaining = blocks[j];

                result.push_back(temp);

                allocated = true;

                break;
            }
        }

        // Not allocated
        if(!allocated)
        {
            Allocation temp;

            temp.process_no = i + 1;

            temp.process_size = processes[i];

            temp.block_no = -1;

            result.push_back(temp);
        }
    }

    print_output(result);

    return 0;
}