#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int main() {
    int n, head, seek_time = 0;

    cout << "Enter no of requests: ";
    cin >> n;

    vector<int> req(n);

    cout << "Enter the requests: ";
    for(int i=0;i<n;i++){
        cin >> req[i];
    }

    cout << "Enter initial position of Head: ";
    cin >> head;

    vector<bool> visited(n, false);

    cout << endl;
    cout << "Seek sequence: " << head;
    
    cout << endl;
    cout << endl;

    cout << "----------------------------------------------------"<<endl;
    cout << "from\t->\tto\t\t|\tMovement" << endl;
    cout << "----------------------------------------------------" << endl;

    vector<int> movements;

    for(int i=0; i<n; i++){
        int idx = -1;
        int minDist = INT_MAX;

        for(int j = 0; j < n; j++){
            if(!visited[j] && abs(req[j] - head) < minDist){
                minDist = abs(req[j] - head);
                idx = j;
            }
            
        }

        visited[idx] = true;

        movements.push_back(minDist);
        seek_time += minDist;
        cout << " " << head << "\t->\t" << req[idx] << "\t\t|\t" << minDist << endl; 
        head = req[idx];
    }

    cout << "--------------------------------------------------------" << endl;


    cout << "Total Seek Time: ";
    for(int i =0; i<movements.size(); i++){
        if(i>0) cout << " + ";
        cout << movements[i];
    }
    cout << " = " << seek_time << endl;

    return 0;
}