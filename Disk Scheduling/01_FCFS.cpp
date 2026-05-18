#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


int main(){
    int n, head, seek_time = 0;

    cout << "Enter the no of requests: ";
    cin >> n;
    cout << endl;
    
    vector<int> req(n);
    
    cout << "Enter the requests: ";
    for(int i = 0; i<n; i++){
        cin >> req[i];
    }
    cout << endl;
    
    cout << "Enter the Initial Position of Head: ";
    cin >> head;
    cout << endl;
    
    cout << "Seek Sequence: ";
    for(int i = 0; i<n; i++){
        cout << req[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    cout << "----------------------------------------------------" << endl;
    cout << "From\t" << "->\t" << "to\t\t" << "|\t" << "Movement" << endl;
    cout << "----------------------------------------------------" << endl;

    vector<int> movements;

    for(int i = 0; i<n; i++){
        int movement = abs(req[i] - head);
        movements.push_back(movement);
        cout << " " << head << "\t" << "->\t" << req[i] << "\t\t" << "|\t" << movement << endl;
        head = req[i];
        seek_time += movement;
    }

    cout << "---------------------------------------------------" << endl;
    cout << endl;
    
    cout << "Total Seek Time: ";
    for(int i = 0; i<movements.size();i++){
        if(i > 0){
            cout << " + ";
        }
        cout << movements[i];
    }
    cout << " = " << seek_time;

    return 0;
}