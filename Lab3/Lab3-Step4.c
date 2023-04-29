// Name: Maddie Waldie
// Date: 4/19/23
// Title: Lab3 – Step
// Description: Implements the shell command: cat /etc/passwd | grep root

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>

// main
int main()
{
	int fds[2];
	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0)
	{
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("grep", "grep", "root", 0);
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", 0);
	}
	else
	{ /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
}