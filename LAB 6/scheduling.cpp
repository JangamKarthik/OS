#include<bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int art;
    int bt;
    int priority;// more value more priority
    int ct,wt, tat, rt, start_time;
}proc[100];

int compare(const void* a, const void* b){
    int art_a = ((struct process*)a)->art;
    int art_b = ((struct process*)b)->art;

    if(art_a < art_b)return -1;
    if(art_a > art_b)return 1;
    return 0;
}

void sjf(){
    int comp=0, curr_time=0;
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    int bt_rem[n];//stores the remaining time for each process
    int isComp[n];//checks if all the processes are completed or not
    cout<<"Enter the process id, art, bt: ";
    for(int i=0; i<n; i++){
        cin>>proc[i].pid>>proc[i].art>>proc[i].bt;
    }
    for(int i=0;i<n; i++){
        isComp[i] = 0 ;
        bt_rem[i] = proc[i].bt;
    }
    cout<<"data inputted"<<endl;
    int sumWT=0, sumTAT=0;
    while(comp!=n){
        int min_burst=INT_MAX; //stores the minimum burst time
        int min_idx=-1; //stotres the process index with min bt
        for(int i=0; i<n; i++){
            if(proc[i].art<=curr_time && isComp[i]==0){
                if(bt_rem[i]<min_burst){
                    min_burst = bt_rem[i];
                    min_idx = i;
                }

                if(bt_rem[i]==min_burst){
                    if(proc[i].art<proc[min_idx].art){
                        min_burst = bt_rem[i];
                        min_idx = i;
                    }
                }
            }
        }

        if(min_idx==-1){
            curr_time++;
        }
        else{
            if(bt_rem[min_idx]==proc[min_idx].bt){
                proc[min_idx].start_time = curr_time;
            }
            bt_rem[min_idx]--;
            curr_time++;
            if(bt_rem[min_idx]==0){
                proc[min_idx].ct = curr_time;
                proc[min_idx].tat = proc[min_idx].ct-proc[min_idx].art;
                proc[min_idx].wt = proc[min_idx].tat-proc[min_idx].bt;
                proc[min_idx].rt = proc[min_idx].start_time-proc[min_idx].art;

                sumTAT += proc[min_idx].tat;
                sumWT +=proc[min_idx].wt;
                comp++;
                isComp[min_idx] = 1;
            }
        }
        //cout<<"bt rem: "<<bt_rem[min_idx]<<endl;
        //cout<<"completed: "<<comp<<endl;
        //cout<<"current time: "<<curr_time<<endl;
    }

    cout<<"PID\t"<<"ART\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT"<<endl;
    for(int i=0; i<n; i++){
        cout<<proc[i].pid<<"\t"<<proc[i].art<<"\t"<<proc[i].bt<<"\t"<<proc[i].ct<<"\t"<<proc[i].tat<<"\t"<<proc[i].wt<<"\t"<<proc[i].rt<<endl;
    }
    cout<<endl;

    cout<<"Average Waiting time: "<<float(sumWT/n)<<endl;
}

void rr(){
    int comp=0, curr_time=0;
    int sumWT=0, sumTAT=0;
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    int tq;
    cout<<"Enter the time quanta: ";
    cin>>tq;
    int isComp[n], bt_rem[n];
    cout<<"Enter the process if, arrival time and burst time:"<<endl;
    for(int i=0; i<n; i++){
        cin>>proc[i].pid>>proc[i].art>>proc[i].bt;
        isComp[i] = 0;
        bt_rem[i] = proc[i].bt;
    }
    //sorting the proc array
    cout<<"Sorted array according to arrival time: "<<endl;
    qsort(proc,n, sizeof(struct process), compare);
    for(int i=0; i<n; i++){
        cout<<proc[i].pid<<"\t"<<proc[i].art<<"\t"<<proc[i].bt<<endl;
    }
    int vis[100] = {0};
    queue<struct process> ready;
    ready.push(proc[0]);
    vis[0] = 1;

    //cout<<ready.front().bt;
    //cout<<p.bt;
    while(comp!=n){
        process p = ready.front();
        ready.pop();

        if(bt_rem[p.pid]==proc[p.pid].bt){//checks if the process is just starting
            proc[p.pid].start_time = max(curr_time, proc[p.pid].art);//if it is, then it add the max of either the currTime or the arrival time
            curr_time = proc[p.pid].start_time;// then it in initialises the current time to start time
        }
        if(bt_rem[p.pid]-tq>0){//if remaining burst time is more than time quantum
            bt_rem[p.pid] -= tq;//reduce bt
            curr_time +=tq; //increment curr time
        }
        else{ //if remaining bt is less than tq
            curr_time += bt_rem[p.pid]; //incre curr time by tq
            bt_rem[p.pid] = 0; //make bt for that process as 0
            comp++;
            isComp[p.pid] = 1;//process marked complete the array
            //calc the necessary calculations
            proc[p.pid].ct = curr_time;
            proc[p.pid].tat = proc[p.pid].ct - proc[p.pid].art;
            proc[p.pid].wt = proc[p.pid].tat - proc[p.pid].bt;
            proc[p.pid].rt = proc[p.pid].start_time - proc[p.pid].art;

            sumWT += proc[p.pid].wt;
            sumTAT += proc[p.pid].tat;
        }

        //checking which new process needs to be inserted into the ready queue
        for(int i=0; i<n; i++){
            if(isComp[i]==0 && proc[i].art<=curr_time && vis[i]==0){//checks if process exists
                ready.push(proc[i]);
                vis[i] = 1;
            }
        }
        //checks if currently running process needs to be pushed back to ready queue
        if(bt_rem[p.pid]>0){
            ready.push(proc[p.pid]);
        }

        //if process is empty then push one process from the list whose remaining bursttime > 0
        if(ready.empty()){
            for(int i=0; i<n; i++){
                if(bt_rem[i]>0){
                    ready.push(proc[i]);
                    vis[i] = 1;
                    break;
                }
            }
        }
    }

    cout<<"PID\t"<<"ART\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT"<<endl;
    for(int i=0; i<n; i++){
        cout<<proc[i].pid<<"\t"<<proc[i].art<<"\t"<<proc[i].bt<<"\t"<<proc[i].ct<<"\t"<<proc[i].tat<<"\t"<<proc[i].wt<<"\t"<<proc[i].rt<<endl;
    }
    cout<<endl;

    cout<<"Average Waiting time: "<<float(sumWT/n)<<endl;
}

void priority(){
    int comp=0, curr_time=0;
    int sumWT=0, sumTAT=0;
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    int isComp[n];//checks if all the processes are completed or not
    for(int i=0;i<n; i++){
        isComp[i] = 0 ;
    }
    cout<<"Enter the process id, art, bt and priority: ";
    for(int i=0; i<n; i++){
        cin>>proc[i].pid>>proc[i].art>>proc[i].bt>>proc[i].priority;
    }

    //qsort(proc, n, sizeof(struct process), compare);
    /*for(int i=0; i<n; i++){
        cout<<proc[i].pid<<"\t"<<proc[i].art<<"\t"<<proc[i].bt<<"\t"<<proc[i].priority<<endl;
    }*/

    while(comp!=n){
        int max_prio = -1;
        int max_idx = -1;
        for(int i=0; i<n; i++){
            if(proc[i].art<=curr_time && isComp[i]==0){
                if(proc[i].priority>max_prio){
                    max_prio = proc[i].priority;
                    max_idx = i;
                }

                if(proc[i].priority==max_prio){
                    if(proc[i].art<proc[max_idx].art){
                        max_prio = proc[i].priority;
                        max_idx = i;
                    }
                }
            }

        }

        if(max_idx==-1){
            curr_time++;
        }
        else{
            proc[max_idx].start_time = curr_time;
            proc[max_idx].ct =  proc[max_idx].start_time+proc[max_idx].bt;
            proc[max_idx].tat = proc[max_idx].ct-proc[max_idx].art;
            proc[max_idx].wt = proc[max_idx].tat-proc[max_idx].bt;
            sumWT += proc[max_idx].wt;
            sumTAT += proc[max_idx].tat;
            comp++;
            isComp[max_idx] = 1;
            curr_time = proc[max_idx].ct;
        }
    }

    cout<<"PID\t"<<"ART\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT"<<endl;
    for(int i=0; i<n; i++){
        cout<<proc[i].pid<<"\t"<<proc[i].art<<"\t"<<proc[i].bt<<"\t"<<proc[i].ct<<"\t"<<proc[i].tat<<"\t"<<proc[i].wt<<endl;
    }
    cout<<endl;

    cout<<"Average Waiting time: "<<float(sumWT/n)<<endl;
}

int main(){
    int choice;
    cout<<"Enter your choice(1-sjf/2-rr/3-priority): ";
    cin>>choice;

    switch(choice){
        case 1:
            sjf();
            break;
        case 2:
            rr();
            break;
        case 3:
            priority();
            break;
    }
}