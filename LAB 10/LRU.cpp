#include<iostream>
using namespace std;

int main(){
    int pagefaults=0;
    int n;
    int capacity;
    int pages[n];int loaded[capacity];int index[capacity];

    cout<<"enter the no of pages: ";
    cin>>n;
    cout<<"enter the capacity of the frame: ";
    cin>>capacity;

    for(int i=0;i<n;i++){
        cout<<"enter the page: ";
        cin>>pages[i];
    }
    for(int i=0;i<n;i++){
        int j=0;
        for(j=0;j<capacity;j++){
            if(loaded[j]==pages[i]){
                index[j]=i;
                break;
            }
        }
        if(j==capacity){
            int lru=0;
            for(int k=1;k<capacity;k++){
                if(index[k]<index[lru]){
                    lru=k;
                }
            }
            loaded[lru]=pages[i];
            index[lru]=i;
            pagefaults++;
            cout<<pages[i]<<"\t";
            for(int f=0;f<capacity;f++){
                cout<<loaded[f]<<"\t";
            }
            cout<<endl;
        }
        else{
            index[j]=i;
        }
    }
}
