#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter the number of resources: ";
    cin >> m;

    int allocation[20][10], max_need[20][10], need[20][10];
    int available[10];

    cout << "\nEnter the Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "\nEnter the Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max_need[i][j];

    cout << "\nEnter the Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> available[i];

    cout << "\nNeed Matrix (Max - Allocation):\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++) {
            need[i][j] = max_need[i][j] - allocation[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    bool finish[20] = {false};
    int safe_sequence[20], work[10];

    // Initialize Work
    cout << "\nInitial Work = Available = (";
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
        cout << work[i] << " ";
    }
    cout << ")\n";

    int count = 0;

    cout << "Finish = [ ";
    for (int i = 0; i < n; i++) cout << "F ";
    cout << "]\n";

    cout << "\n------------------------------------------\n";

    while (count < n) {
        bool found = false;

        cout << "\nChecking processes whose Need <= Work:\n";

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {

                cout << "P" << i << ": Need (";
                for (int j = 0; j < m; j++) {
                    cout << need[i][j] << " ";
                }
                cout << ") ";

                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    cout << "<= Work (";
                    for (int j = 0; j < m; j++) cout << work[j] << " ";
                    cout << ") -> Can execute\n";

                    cout << "--> Executing P" << i << endl;

                    // Update Work
                    cout << "Updated Work = Work + Allocation(P" << i << ")\n";
                    cout << "Work = (";
                    for (int j = 0; j < m; j++) cout << work[j] << " ";
                    cout << ") + (";
                    for (int j = 0; j < m; j++) cout << allocation[i][j] << " ";
                    cout << ") = (";

                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                        cout << work[j] << " ";
                    }
                    cout << ")\n";

                    finish[i] = true;
                    safe_sequence[count++] = i;
                    found = true;

                    cout << "Finish = [ ";
                    for (int k = 0; k < n; k++)
                        cout << (finish[k] ? "T " : "F ");
                    cout << "]\n";

                    cout << "\n------------------------------------------\n";

                    break; 
                } else {
                    cout << "> Work (";
                    for (int j = 0; j < m; j++) cout << work[j] << " ";
                    cout << ") -> Cannot execute\n";
                }
            }
        }

        if (!found) {
            cout << "\nSystem is in UNSAFE state\n";
            return 0;
        }
    }

    cout << "\nSystem is in SAFE state\n";
    cout << "Safe Sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safe_sequence[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}