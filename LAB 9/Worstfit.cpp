#include<iostream>
using namespace std;

void bestfit(int bs[],int ps[],int b,int p){
    int alloc[p];
    for(int i=0;i<p;i++){
        alloc[i]=-1;
    }    

    for(int i=0;i<p;i++){
        int minidx=-1;
        for(int j=0;j<b;j++){
            if(bs[j]>=ps[i]){
                if(minidx==-1)
                    minidx=j;
                    else if(bs[minidx]<bs[j])
                        minidx=j;
            }
        }
            if(minidx!=-1){
                alloc[i]=minidx;
                bs[minidx]=bs[minidx]-ps[i];
        }
    }

    cout<<"process number\tprocess size\tblock number"<<endl;
    for(int i=0;i<p;i++){
        cout<<i+1<<"\t\t"<<ps[i]<<"\t\t";
        if(alloc[i]==-1){
            cout<<"not allocated";
        }
        else{
            cout<<alloc[i]+1;
        }
        cout<<endl;
    }

}

int main(){
    int p,b;
    cout<<"Enter the number of processes: ";
    cin>>p;
    cout<<"Enter the number of blocks: ";
    cin>>b;
    int blocksize[b];
    int process[p];
    for(int i=0;i<p;i++){
        cout<<"Enter the size of process: ";
        cin>>process[i];
    }
    for(int i=0;i<b;i++){
        cout<<"Enter the size of block: ";
        cin>>blocksize[i];
    }
    bestfit(blocksize,process,b,p);
    return 0;
}
