#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Block
{
    int size;
    bool allocated;
    char process;
};

vector<Block> memory;

// get next power of 2
int nextPowerOf2(int n)
{
    int p = 1;
    while (p < n)
        p *= 2;
    return p;
}

// display memory
void display()
{
    cout << "Memory: ";
    for (auto &b : memory)
    {
        if (b.allocated)
            cout << "[" << b.process << "=" << b.size << "K] ";
        else
            cout << "[" << b.size << "K] ";
    }
    cout << "\n";
}

// allocate memory
void allocate()
{
    char name;
    int size;

    cout << "Enter process name (A/B/C...): ";
    cin >> name;
    cout << "Enter size: ";
    cin >> size;

    int required = nextPowerOf2(size);

    cout << "\nRequest " << name << " = " << size << "K\n";

    for (int i = 0; i < memory.size(); i++)
    {
        if (!memory[i].allocated && memory[i].size >= required)
        {

            // splitting
            while (memory[i].size > required)
            {
                int newSize = memory[i].size / 2;

                cout << "Splitting " << memory[i].size
                     << "K into " << newSize << "K blocks\n";

                memory[i].size = newSize;

                Block newBlock;
                newBlock.size = newSize;
                newBlock.allocated = false;

                memory.insert(memory.begin() + i + 1, newBlock);
            }

            memory[i].allocated = true;
            memory[i].process = name;

            cout << "Allocated " << required << "K to " << name << "\n";
            cout << "Internal Fragmentation = "
                 << required - size << "K\n";

            display();
            return;
        }
    }

    cout << "Allocation failed\n";
}

// deallocate
void deallocate()
{
    char name;
    cout << "Enter process name to free: ";
    cin >> name;

    for (int i = 0; i < memory.size(); i++)
    {
        if (memory[i].allocated && memory[i].process == name)
        {
            memory[i].allocated = false;

            cout << "\nRelease " << name << "\n";

            // merging buddies
            for (int j = 0; j < memory.size() - 1; j++)
            {
                if (!memory[j].allocated && !memory[j + 1].allocated &&
                    memory[j].size == memory[j + 1].size)
                {

                    memory[j].size *= 2;
                    memory.erase(memory.begin() + j + 1);
                    j = -1; // restart merging
                }
            }

            display();
            return;
        }
    }

    cout << "Process not found\n";
}

int main()
{
    int total;

    cout << "Enter total memory size (power of 2): ";
    cin >> total;

    memory.push_back({total, false, '-'});

    int choice;

    do
    {
        cout << "\n1. Allocate\n2. Deallocate\n3. Display\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            allocate();
            break;
        case 2:
            deallocate();
            break;
        case 3:
            display();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}