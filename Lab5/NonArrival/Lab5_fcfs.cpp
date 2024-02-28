#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("lab5.txt", "r", stdin);
    int burstTime, priority;
    vector<int> res;
    res.push_back(0);
    for(int i=0; i<5; i++){
        cin >> burstTime >> priority;
        res.push_back(burstTime);
    }
    cout << "|---p1---|---p2---|---p3---|---p4---|---p5---|" << endl;
    printf("%-9d", 0);
    vector<int> turn, wait;
    int currTime = 0;
    for(int i=1; i<6; i++){
        currTime += res[i];
        printf("%-9d", currTime);
        turn.push_back(currTime);
        wait.push_back(currTime - res[i]);
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