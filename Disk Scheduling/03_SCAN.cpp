#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(){
    int n , head, seek_time = 0;

    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> req(n);

    cout<<"Enter the requests: ";
    for(int i = 0; i<n; i++){
        cin>>req[i];
    }

    cout<<"Enter initial position of head: ";
    cin >> head;

    vector<int> left, right;

    for(int i =0; i<n; i++){
        if(req[i] < head){
            left.push_back(req[i]);
        } else {
            right.push_back(req[i]);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << endl;

    cout << "seek sequence: ";
    for(int i = 0; i < right.size(); i++){
        cout << right[i] << " ";
    }
    for(int i = left.size()-1; i >=0; i--){
        cout << left[i] << " ";
    }

    cout << endl;

    cout << "----------------------------------------------------"<<endl;
    cout << " " << "from\t->\tto\t\t|\tmovement" << endl;
    cout << "----------------------------------------------------"<<endl;

    vector<int> movements;

    for(int i = 0; i <right.size(); i++){
        int movement = abs(right[i] - head);
        movements.push_back(movement);
        cout << " " << head << "\t->\t" << right[i] << "\t\t|\t" << movement << endl;
        seek_time += movement;
        head = right[i];
    }

    for(int i = left.size()-1; i >=0; i--){
        int movement = abs(left[i] - head);
        movements.push_back(movement);
        cout << " " << head << "\t->\t" << left[i] << "\t\t|\t" << movement << endl;
        seek_time += movement;
        head = left[i];
    }

    cout << "----------------------------------------------------"<<endl;

    cout << endl;
    cout << "Total Seek Time: ";
    for(int i = 0; i < movements.size(); i++){
        if(i>0) cout << " + ";
        cout << movements[i];
    }
    cout << " = " << seek_time << endl;

    return 0;
}