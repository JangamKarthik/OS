#include <iostream>     // input/output stream library
#include <unistd.h>     // Unix standard library
#include <sys/wait.h>   // system wait library
#include <cstring>      // string handling library
using namespace std;    // using standard namespace

int main()
{
    char a[5][20], temp[20];  // declare two arrays of strings
    int i, j, status;         // declare integer variables for loop and process status

    // Get input from user
    cout << "Enter the 5 strings" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }

    pid_t pid = fork();     // create child process using fork()

    if (pid == 0) {         // child process
        cout << "In child process" << endl;

        // sort the strings
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4 - i; j++) {
                if (strcmp(a[j], a[j + 1]) > 0) {
                    strcpy(temp, a[j]);
                    strcpy(a[j], a[j + 1]);
                    strcpy(a[j + 1], temp);
                }
            }
        }

        // print the sorted list
        cout << "The list in sorted order are" << endl;
        for (i = 0; i < 5; i++) {
            cout << a[i] << endl;
        }
    }
    else if (pid > 0) {     // parent process
        wait(&status);      // wait for child process to finish
        if (WIFEXITED(status)) {
            cout << "Child returned" << endl;
        }
        cout << "In parent process" << endl;

        // print the unsorted list
        cout << "The list in unsorted order are" << endl;
        for (i = 0; i < 5; i++) {
            cout << a[i] << endl;
        }
    }

    return 0;   // exit program
}

