#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process
{
    int pid, at, bt;
    int ct, tat, wt;
    bool done = false;
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
             << "\t\t" << pr.bt
             << endl;
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

// -------- GANTT CHART --------
void print_gantt(vector<int> &order,
                 vector<int> &timeline)
{
    int width = 6;

    for(int i = 0; i < order.size(); i++)
        cout << "------";

    cout << "-\n";

    for(int i = 0; i < order.size(); i++)
        cout << "| P" << order[i] << " ";

    cout << "|\n";

    for(int i = 0; i < order.size(); i++)
        cout << "------";

    cout << "-\n";

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

// -------- MAIN --------
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
    int completed = 0;

    vector<int> order;
    vector<int> timeline;

    timeline.push_back(0);

    while(completed < n)
    {
        int idx = -1;
        int min_bt = INT_MAX;

        // Find shortest arrived process
        for(int i = 0; i < n; i++)
        {
            if(!p[i].done &&
               p[i].at <= time &&
               p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        // CPU Idle
        if(idx == -1)
        {
            time++;
        }
        else
        {
            order.push_back(p[idx].pid);

            time += p[idx].bt;

            timeline.push_back(time);

            p[idx].ct = time;

            p[idx].tat =
            p[idx].ct - p[idx].at;

            p[idx].wt =
            p[idx].tat - p[idx].bt;

            p[idx].done = true;

            completed++;
        }
    }

    cout << "\nGANTT CHART:\n";

    print_gantt(order, timeline);

    print_output(p);

    return 0;
}