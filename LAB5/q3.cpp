#include <iostream>     // input/output stream library
#include <unistd.h>     // Unix standard library
#include <sys/wait.h>   // system wait library
#include <cstring>      // string handling library
#include <algorithm>    // algorithm library for sort()
using namespace std;    // using standard namespace

// Function to sort an array of strings using bubble sort
void bubbleSort(string arr[], int n) {
    string temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort an array of strings using selection sort
void selectionSort(string arr[], int n) {
    int minIndex;
    string temp;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main()
{
    int n;
    cout << "Enter the number of strings to read: ";
    cin >> n;

    string arr[n];
    cout << "Enter the " << n << " strings: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    pid_t pid1, pid2;

    pid1 = fork();  // create first child process

    if (pid1 == 0) {    // child process 1
        cout << "In child process 1" << endl;

        // sort the array using bubble sort
        bubbleSort(arr, n);

        // print the sorted array
        cout << "The list in sorted order using bubble sort: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else if (pid1 > 0) {    // parent process
        pid2 = fork();      // create second child process

        if (pid2 == 0) {    // child process 2
            cout << "In child process 2" << endl;

            // sort the array using selection sort
            selectionSort(arr, n);

            // print the sorted array
            cout << "The list in sorted order using selection sort: ";
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else if (pid2 > 0) {    // parent process
            wait(NULL);     // wait for one of the child processes to finish
            cout << "One of the child processes has finished" << endl;
        }
    }

    return 0;   // exit program
}

