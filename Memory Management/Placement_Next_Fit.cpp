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

    int last = 0;

    // Next Fit Logic
    for(int i = 0; i < np; i++)
    {
        bool allocated = false;

        int start = last;

        do
        {
            if(blocks[last] >= processes[i])
            {
                Allocation temp;

                temp.process_no = i + 1;

                temp.process_size = processes[i];

                temp.block_no = last + 1;

                temp.block_size = blocks[last];

                blocks[last] -= processes[i];

                temp.remaining = blocks[last];

                result.push_back(temp);

                allocated = true;

                break;
            }

            last = (last + 1) % nb;

        } while(last != start);

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