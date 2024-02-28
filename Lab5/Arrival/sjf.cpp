#include<bits/stdc++.h>
using namespace std;

struct Process{
    string name;
    int burstTime;
    int priority;
    int arrivalTime;
};

struct Result{
    string name;
    int start;
    int end;
    int taTime;
    int waitTime;
};

void takeInput(int size, vector<Process> &processes){
    Process process;
    for(int i=0; i<size; i++){
        process.name = "P" + to_string(i+1);
        cin >> process.burstTime >> process.priority >> process.arrivalTime;
        processes.push_back(process);
    }
}

bool compareTwoProcess(Process a, Process b){
    if(a.arrivalTime == b.arrivalTime) return a.burstTime < b.burstTime;
    return a.arrivalTime < b.arrivalTime;
}

bool compareTwoResult(Result a, Result b){
    return a.name < b.name;
}

bool sortReady(Process a, Process b){
    return a.burstTime < b.burstTime;
}

void makeReadyQueue(vector<Process> &ready, int currTime, vector<Process> processes){
    ready.clear();
    for(auto p: processes){
        if(p.arrivalTime <= currTime){
            ready.push_back(p);
        }
    }
    sort(ready.begin(), ready.end(), sortReady);
}

void print(vector<Process> a){
    for(auto ab: a){
        cout << ab.name << "  " << ab.burstTime << "  " << ab.arrivalTime << endl;
    }
}

void printR(vector<Result> a){
    for(auto ab: a){
        cout << ab.name << "  " << ab.start << "  " << ab.end << endl;
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    vector<Process> processes;
    vector<Process> temp;
    takeInput(4, processes);
    temp = processes;
    sort(temp.begin(), temp.end(), compareTwoProcess);
    int currTime = 0;
    vector<Process> ready;
    vector<Result> results;
    while(!temp.empty()){
        makeReadyQueue(ready, currTime, temp);
        if(ready.empty()){
            Result result;
            result.name = "Dl";
            result.start = currTime;
            currTime = temp[0].arrivalTime;
            result.end = currTime;
            results.push_back(result);
        }
        else{
            Process currP = ready.front();
            Result result;
            result.name = currP.name;
            result.start = currTime;
            currTime += currP.burstTime;
            result.end = currTime;
            result.taTime = result.end - currP.arrivalTime;
            result.waitTime = result.taTime - currP.burstTime;
            results.push_back(result);
            auto it = temp.begin();
            while(it != temp.end()){
                if((*it).name == currP.name){
                    temp.erase(it);
                    break;
                }
                it++;
            }
        }
        
    }

    printf("|");

    for(auto r: results){
        printf("---%s---|", r.name.c_str());
    }

    cout << endl;
    
    printf("%-9d", 0);

    for(auto r: results){
        printf("%-9d", r.end);
    }

    cout << endl << endl;

    sort(results.begin(), results.end(), compareTwoResult);

    printf("%10s %10s %10s\n", "Process ID", "Turn Time", "Wait Time");

    int totalTurnTime = 0, totalWaitTime = 0;
    for(int i=0; i<results.size(); i++){
        if(results[i].name != "Dl"){
            printf("%-10s %10d %10d\n", results[i].name.c_str(), results[i].taTime, results[i].waitTime);
            totalTurnTime += results[i].taTime;
            totalWaitTime += results[i].waitTime;
        }
    }

    printf("Average Turn Around Time: %.2lf\n", totalTurnTime/double(processes.size()));
    printf("Average Waiting Time: %.2lf\n", totalWaitTime/double(processes.size()));
}