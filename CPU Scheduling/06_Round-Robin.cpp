#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process
{
    int pid, at, bt;
    int rt;
    int ct, tat, wt;
};

// -------- PRINT INPUT --------
void print_input(vector<Process> &p,
                 int quantum)
{
    cout << "\nINPUT:\n";

    cout << "Time Quantum = "
         << quantum << endl;

    cout << "\nProcess\tArrival Time\tBurst Time\n";

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
void print_gantt(vector<int> &gantt,
                 vector<int> &timeline)
{
    int width = 6;

    for(int i = 0; i < gantt.size(); i++)
        cout << "------";

    cout << "-\n";

    for(int i = 0; i < gantt.size(); i++)
        cout << "| P" << gantt[i] << " ";

    cout << "|\n";

    for(int i = 0; i < gantt.size(); i++)
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
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter Arrival Time and Burst Time:\n";

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        cin >> p[i].at >> p[i].bt;

        p[i].rt = p[i].bt;
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    print_input(p, quantum);

    queue<int> q;

    vector<bool> inQueue(n, false);

    int time = 0;
    int completed = 0;

    vector<int> gantt;
    vector<int> timeline;

    timeline.push_back(0);

    // Add initially arrived processes
    for(int i = 0; i < n; i++)
    {
        if(p[i].at == 0)
        {
            q.push(i);

            inQueue[i] = true;
        }
    }

    while(completed < n)
    {
        // CPU Idle
        if(q.empty())
        {
            time++;

            for(int i = 0; i < n; i++)
            {
                if(!inQueue[i] &&
                   p[i].at <= time)
                {
                    q.push(i);

                    inQueue[i] = true;
                }
            }

            continue;
        }

        int idx = q.front();

        q.pop();

        gantt.push_back(p[idx].pid);

        // Execute process
        int exec =
        min(quantum, p[idx].rt);

        time += exec;

        p[idx].rt -= exec;

        timeline.push_back(time);

        // Add newly arrived processes
        for(int i = 0; i < n; i++)
        {
            if(!inQueue[i] &&
               p[i].at <= time)
            {
                q.push(i);

                inQueue[i] = true;
            }
        }

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
        else
        {
            // Push again into queue
            q.push(idx);
        }
    }

    cout << "\nGANTT CHART:\n";

    print_gantt(gantt, timeline);

    print_output(p);

    return 0;
}