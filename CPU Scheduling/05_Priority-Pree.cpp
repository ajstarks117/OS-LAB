#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process
{
    int pid, at, bt, priority;
    int rt;
    int ct, tat, wt;
};

// -------- PRINT INPUT --------
void print_input(vector<Process> &p)
{
    cout << "\nINPUT:\n";

    cout << "Process\tArrival Time\tBurst Time\tPriority\n";

    for(auto &pr : p)
    {
        cout << "P" << pr.pid
             << "\t" << pr.at
             << "\t\t" << pr.bt
             << "\t\t" << pr.priority
             << endl;
    }
}

// -------- PRINT OUTPUT --------
void print_output(vector<Process> &p)
{
    float total_tat = 0;
    float total_wt = 0;

    cout << "\nOUTPUT TABLE:\n";

    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";

    for(auto &pr : p)
    {
        cout << "P" << pr.pid
             << "\t" << pr.at
             << "\t\t" << pr.bt
             << "\t\t" << pr.priority
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
void print_gantt(vector<int> &gantt)
{
    int width = 6;

    for(int i = 0; i < gantt.size(); i++)
        cout << "------";

    cout << "-\n";

    for(int i = 0; i < gantt.size(); i++)
    {
        if(gantt[i] == -1)
            cout << "|Idle ";
        else
            cout << "| P" << gantt[i] << " ";
    }

    cout << "|\n";

    for(int i = 0; i < gantt.size(); i++)
        cout << "------";

    cout << "-\n";

    for(int i = 0; i <= gantt.size(); i++)
    {
        cout << i;

        int spaces =
        width - to_string(i).length();

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

    cout << "Enter Arrival Time, Burst Time and Priority:\n";

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        cin >> p[i].at
            >> p[i].bt
            >> p[i].priority;

        p[i].rt = p[i].bt;
    }

    print_input(p);

    int time = 0;
    int completed = 0;

    vector<int> gantt;

    while(completed < n)
    {
        int idx = -1;
        int best_priority = INT_MAX;

        // Find highest priority
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time &&
               p[i].rt > 0 &&
               p[i].priority < best_priority)
            {
                best_priority = p[i].priority;

                idx = i;
            }
        }

        // CPU Idle
        if(idx == -1)
        {
            gantt.push_back(-1);

            time++;
        }
        else
        {
            gantt.push_back(p[idx].pid);

            p[idx].rt--;

            time++;

            // Process completed
            if(p[idx].rt == 0)
            {
                completed++;

                p[idx].ct = time;

                p[idx].tat =
                p[idx].ct - p[idx].at;

                p[idx].wt =
                p[idx].tat - p[idx].bt;
            }
        }
    }

    cout << "\nGANTT CHART:\n";

    print_gantt(gantt);

    print_output(p);

    return 0;
}