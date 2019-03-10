#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
main()
{
printf("Przemyslaw Szymoniak, pid: %d\n", getpid());
}
