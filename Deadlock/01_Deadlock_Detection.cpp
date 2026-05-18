#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> request(n, vector<int>(m));
    vector<int> available(m);
    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];
    cout << "Enter Request Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> request[i][j];
    cout << "Enter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> available[j];

    vector<bool> finish(n, false);
    vector<int> work = available;
    vector<int> safeSeq;

    bool found;

    cout << "\n========================================\n";
    cout << "   Step-wise Deadlock Detection Trace\n";
    cout << "========================================\n";

    cout << "\nInitial Work: [";
    for (int j = 0; j < m; j++) {
        if (j > 0) cout << ", ";
        cout << work[j];
    }
    cout << "]\n";

    for (int k = 0; k < n; k++)
    {
        found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canExecute = true;

                cout << "\nChecking P" << i << "\n";
                cout << "  Request[P" << i << "] = [";
                for (int j = 0; j < m; j++) {
                    if (j > 0) cout << ", ";
                    cout << request[i][j];
                }
                cout << "]  vs  Work = [";
                for (int j = 0; j < m; j++) {
                    if (j > 0) cout << ", ";
                    cout << work[j];
                }
                cout << "]\n";

                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute)
                {
                    cout << "  Reclaiming Allocation[P" << i << "] = [";
                    for (int j = 0; j < m; j++) {
                        if (j > 0) cout << ", ";
                        cout << allocation[i][j];
                    }
                    cout << "]\n";

                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    safeSeq.push_back(i);
                    found = true;

                    cout << "  Updated Work = [";
                    for (int j = 0; j < m; j++) {
                        if (j > 0) cout << ", ";
                        cout << work[j];
                    }
                    cout << "]\n";
                    cout << "  Finish = [";
                    for (int i2 = 0; i2 < n; i2++) {
                        if (i2 > 0) cout << ", ";
                        cout << (finish[i2] ? "T" : "F");
                    }
                    cout << "]\n";
                }
                else
                {
                    cout << "  Skip P" << i << "\n";
                }
            }
        }

        if (!found)
            break;
    }

    cout << "\n========================================\n";

    // Check deadlock
    bool deadlock = false;

    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            deadlock = true;
            break;
        }
    }
    if (deadlock)
    {
        cout << "\nDeadlock detected!\nProcesses in deadlock: ";
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
                cout << "P" << i << " ";
        }
    }
    else
    {
        cout << "\nNo Deadlock detected.\nSafe sequence: ";
        for (int x : safeSeq)
            cout << "P" << x << " ";
    }
    return 0;
}