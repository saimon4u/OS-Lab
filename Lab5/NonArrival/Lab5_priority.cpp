#include<bits/stdc++.h>
using namespace std;

struct Process{
    string name;
    int burstTime;
    int priority;
};

bool compareTwoProcess(Process a, Process b){
    if(a.priority != b.priority)
        return a.priority > b.priority;
    
    return a.burstTime < b.burstTime;
}

int main(){
    freopen("lab5.txt", "r", stdin);
    int burstTime, priority;
    Process processes[5];
    for(int i=0; i<5; i++){
        cin >> burstTime >> priority;
        processes[i].name = "P" + to_string(i+1);
        processes[i].burstTime = burstTime;
        processes[i].priority = priority;
    }
    sort(processes, processes+5, compareTwoProcess);

    vector<int> turn, wait;
    int currTime = 0;
    cout << "|";
    for(auto p: processes){
        printf("---%s---|", p.name.c_str());
    }
    cout << endl;
    printf("%-9d", 0);
    for(int i=0; i<5; i++){
        currTime += processes[i].burstTime;
        printf("%-9d", currTime);
        turn.push_back(currTime);
        wait.push_back(currTime - processes[i].burstTime);
    }

    cout << endl << endl;

    printf("%10s %10s %10s\n", "Process ID", "Turn Time", "Wait Time");
    for(int i=0; i<turn.size(); i++){
        printf("P%-9d %10d %10d\n", i+1, turn[i], wait[i]);
    }

    int sum = 0;
    printf("Average Turn Around Time: %.2lf\n", accumulate(turn.begin(), turn.end(), sum)/5.0);
    sum = 0;
    printf("Average Waiting Time: %.2lf\n", accumulate(wait.begin(), wait.end(), sum)/5.0);
    
}