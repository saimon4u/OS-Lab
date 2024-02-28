#include<bits/stdc++.h>
using namespace std;

struct Process{
    string name;
    int burstTime;
    int priority;
};

struct Result{
    string name;
    int start;
    int end;
};


int main(){

    int quantum;
    cout << "Enter quantum -> ";
    cin >> quantum;

    freopen("lab5.txt", "r", stdin);
    int burstTime, priority;
    Process processes[5];
    vector<int> bTime;
    for(int i=0; i<5; i++){
        cin >> burstTime >> priority;
        processes[i].name = "P" + to_string(i+1);
        processes[i].burstTime = burstTime;
        processes[i].priority = priority;
        bTime.push_back(burstTime);
    }


    vector<Result> ans;
    int count = 0, Time = 0;
    while(count < 5){
        for(auto &p: processes){
            if(p.burstTime > 0){
                if(p.burstTime <= quantum){
                Result res;
                res.name = p.name;
                res.start = Time;
                res.end = Time + p.burstTime;
                ans.push_back(res);
                Time += p.burstTime;
                p.burstTime = 0;
                count++;
                }
                else{
                    Result res;
                    res.name = p.name;
                    res.start = Time;
                    res.end = Time + quantum;
                    p.burstTime -= quantum;
                    ans.push_back(res);
                    Time += quantum;
                }
            }
        }
    }

    cout << "|";

    for(auto a: ans){
        printf("---%s---|", a.name.c_str());
    }
    cout << endl;
    printf("%-9d", 0);
    map<string, int> turn, wait;
    for(auto a: ans){
        printf("%-9d", a.end);
        turn[a.name] = a.end;
    }
    cout << endl << endl;

    map<string, int>::iterator it = turn.begin();
 
    while(it != turn.end()) {
        for(int i=0; i<5; i++){
            if(processes[i].name == it->first){
                wait[it->first] = it->second - bTime[i];
                break;
            }
        }
        ++it;
    }


    printf("%10s %10s %10s\n", "Process ID", "Turn Time", "Wait Time");

    map<string, int>::iterator it2 = turn.begin();
    map<string, int>::iterator it3 = wait.begin();
    
    int avgTurn = 0, avgWait = 0;

    while(it2 != turn.end()) {
        printf("%-10s %10d %10d\n", it2->first.c_str(), it2->second, it3->second);\
        avgTurn += it2->second;
        avgWait += it3->second;
        ++it2;
        ++it3;
    }
    
    printf("Average Turn Around Time: %.2lf\n", avgTurn/5.0);
    printf("Average Waiting Time: %.2lf\n", avgWait/5.0);
    
}