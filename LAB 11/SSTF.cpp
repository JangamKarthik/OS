#include<iostream>
using namespace std;

int absdiff(int a, int b)
{
    return abs(a-b);
}
void sstf(int start, int arr[], int n)
{
    int visited[n];
    int head=start;
    int sum=0;
    for(int i=0;i<n;i++)
    {
        visited[i]=-1;
    }
    for(int i=0;i<n;i++)
    {
        int mindist=100000;
        int minidx=-1;
        for(int j=0;j<n;j++)
        {
            if(visited[j]==-1)
            {
                int x=absdiff(head, arr[j]);
            if(mindist>x)
            {
                mindist=x;
                minidx=j;
            }
            }

        }
        cout<<arr[minidx]<<endl;
        head=arr[minidx];
        visited[minidx]=1;
        sum+=mindist;
    }
    cout<<sum;
}
int main(){
            int start;
            int n;
            cout<<"enter no of pages: ";
            cin>>n;
            cout<<"enter the head: ";
            cin>>start;
            int arr[n];
            for(int i=0;i<n;i++){
                cout<<"enter the page: ";
                cin>>arr[i];
            }
            sstf(start, arr, n);
    }
