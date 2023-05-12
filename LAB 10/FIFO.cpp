#include<iostream>
#include<queue>
using namespace std;

void fifo(int n,int page[],int capacity){
    bool present[100];
    int pagef=0;
    int pageh=0;
    queue<int> q;
    cout<<"page values\tfault/hit"<<endl;
    for(int i=0;i<100;i++){
        present[i] = false;
    }

    for(int i=0;i<n;i++){
        if(present[page[i]]==false){
            if(q.size()==capacity){
                int val=q.front();
                q.pop();
                present[val] = false;
            }
                      q.push(page[i]);
            present[page[i]]=true;
            pagef++;
            cout<<page[i]<<"\t\tfault"<<endl;;
        }
            else{
                pageh++;
                cout<<page[i]<<"\t\thit"<<endl;
            }
    }
    cout<<"total pagefaults:"<<pagef<<endl;
    cout<<"total pagehits:"<<pageh<<endl;
}

int main(){
    int n;
    cout<<"enter no pages: ";
    cin>>n;
    int page[n];
    for(int i=0;i<n;i++){
        cout<<"tenter the page value: ";
        cin>>page[i];
    }
    int capacity;
    cout<<"enter the capacity of a frame: ";
    cin>>capacity;
    fifo(n,page,capacity);
}
