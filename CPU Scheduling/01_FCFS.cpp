#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    int pid, at, bt;
    int ct, tat, wt;
};

// -------- PRINT INPUT --------
void print_input(vector<Process> &p)
{
    cout << "\nINPUT:\n";

    cout << "Process\tArrival Time\tBurst Time\n";

    for(auto &pr : p)
    {
        cout << "P" << pr.pid
             << "\t" << pr.at
             << "\t\t" << pr.bt << endl;
    }
}

// -------- PRINT OUTPUT --------
void print_output(vector<Process> &p)
{
    float total_tat = 0;
    float total_wt = 0;

    cout << "\nOUTPUT TABLE:\n";

    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";

    for(auto &pr : p)
    {
        cout << "P" << pr.pid
             << "\t" << pr.at
             << "\t\t" << pr.bt
             << "\t\t" << pr.ct
             << "\t\t" << pr.tat
             << "\t\t" << pr.wt
             << endl;

        total_tat += pr.tat;
        total_wt += pr.wt;
    }

    cout << "\nAverage Turnaround Time = "
         << total_tat / p.size();

    cout << "\nAverage Waiting Time = "
         << total_wt / p.size()
         << endl;
}

// -------- PRINT GANTT CHART --------
void print_gantt(vector<int> &order,
                 vector<int> &timeline)
{
    int width = 6;

    // Top Border
    for(int i = 0; i < order.size(); i++)
        cout << "------";

    cout << "-\n";

    // Process Row
    for(int i = 0; i < order.size(); i++)
    {
        cout << "| P" << order[i] << " ";
    }

    cout << "|\n";

    // Bottom Border
    for(int i = 0; i < order.size(); i++)
        cout << "------";

    cout << "-\n";

    // Timeline
    for(int i = 0; i < timeline.size(); i++)
    {
        cout << timeline[i];

        int spaces =
        width - to_string(timeline[i]).length();

        for(int j = 0; j < spaces; j++)
            cout << " ";
    }

    cout << endl;
}

// -------- FCFS --------
int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter Arrival Time and Burst Time:\n";

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        cin >> p[i].at >> p[i].bt;
    }

    print_input(p);

    int time = 0;

    vector<int> order;
    vector<int> timeline;

    timeline.push_back(0);

    // FCFS Logic
    for(int i = 0; i < n; i++)
    {
        // CPU idle case
        if(time < p[i].at)
            time = p[i].at;

        order.push_back(p[i].pid);

        time += p[i].bt;

        timeline.push_back(time);

        p[i].ct = time;

        p[i].tat = p[i].ct - p[i].at;

        p[i].wt = p[i].tat - p[i].bt;
    }

    cout << "\nGANTT CHART:\n";

    print_gantt(order, timeline);

    print_output(p);

    return 0;
}