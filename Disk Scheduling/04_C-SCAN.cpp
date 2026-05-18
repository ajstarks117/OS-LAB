#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int n, head, seek_time = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> req(n);

    cout << "Enter requests: ";
    for(int i = 0; i < n; i++)
        cin >> req[i];

    cout << "Enter initial head position: ";
    cin >> head;

    vector<int> left, right;

    // Divide requests
    for(int i = 0; i < n; i++)
    {
        if(req[i] < head)
            left.push_back(req[i]);
        else
            right.push_back(req[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    vector<int> movements;

    cout << "\nSeek Sequence: " << head;

    cout << "\n\n----------------------------------------------------\n";
    cout << "From\t->\tTo\t\t|\tMovement\n";
    cout << "----------------------------------------------------\n";

    // Move right side
    for(int i = 0; i < right.size(); i++)
    {
        int movement = abs(right[i] - head);

        cout << " " << head
             << "\t->\t"
             << right[i]
             << "\t\t|\t"
             << movement << endl;

        seek_time += movement;

        movements.push_back(movement);

        head = right[i];
    }

    // Jump to 0
    int jump = head;

    cout << " " << head
         << "\t->\t0"
         << "\t\t|\t"
         << jump << endl;

    seek_time += jump;

    movements.push_back(jump);

    head = 0;

    // Service left side
    for(int i = 0; i < left.size(); i++)
    {
        int movement = abs(left[i] - head);

        cout << " " << head
             << "\t->\t"
             << left[i]
             << "\t\t|\t"
             << movement << endl;

        seek_time += movement;

        movements.push_back(movement);

        head = left[i];
    }

    cout << "----------------------------------------------------\n\n";

    cout << "Total Seek Time: ";

    for(int i = 0; i < movements.size(); i++)
    {
        if(i > 0)
            cout << " + ";

        cout << movements[i];
    }

    cout << " = " << seek_time;

    return 0;
}