// Name: Maddie Waldie
// Date: 4/19/23
// Title: Lab3 – Step 1
// Description: Runs ls -l | more
// Instructions: Compile and run the following program and write your observations. Modify to pass -l option
// to the ls command.

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
    if (fork() == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("more", "more", 0); 
    }
    /*child 2 duplicates upstream into stdout */
    else if (fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        //execlp("ls", "ls", 0); 
        execlp("ls", "ls", "-l", 0);
    }
    else {  /*parent closes both ends and wait for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0); 
    }
    return 0;
}
