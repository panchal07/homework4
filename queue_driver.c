/* Driver program to test the queue implementation */
/* Use the Makefile provided or compile using: gcc -Wall queue_helper.c queue_driver.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "queue_helper.h"
#include "queue_driver.h"

queue *jobQ;  
int P;        
job listJ[1500]; 
int currjob;    


int main(int argc, char **argv) {
	pthread_t tid;
	queue *q;
	int i;
	
	if (argc != 2)
    {
        exit(EXIT_SUCCESS);
    }

	P = atoi(argv[1]);
    printf("Prompt: %d\n\n", P);
	
	/*https://github.com/eolatham/job-scheduler/blob/master/job_scheduler.c
	*/
	/* create a queue data structure */
	q = queue_init(P);
	
	pthread_create(&tid, NULL, complete_jobs, NULL);

    processJobs();
	
	exit(EXIT_SUCCESS);

}

void processJobs(){
	char *inputText;          
    char *command; 
    int i=0;              
    char data[1500];
	
	/*	https://github.com/eolatham/job-scheduler/blob/master/job_scheduler.c
	*/
	
	while (printf("Enter command> ") && getcmd(data, 1500) != -1)
    {
        if ((inputText = strtok(getstring(data), " \t\n\r\x0b\x0c")) != NULL)
        {
            if (strcmp(inputText, "submit") == 0)
            {
                if (jobQ->count >= jobQ->size){
                    printf("Add jobs after some time\n");
                }
                else
                {
                    command = retptr(strstr(data, "submit") + 6);
                    listJ[i] = newjob(command, i);
                    queue_insert(jobQ, listJ + i);
                    printf("job%d added to the queue\n", ++i);
                }
            }
            else if (strcmp(inputText, "showjobs") == 0 ||strcmp(inputText, "submithistory") == 0){
                jobsDetails(listJ, i, inputText);
            }
        }
    }
    kill(0, SIGINT); 
}

//lecture 17 fork.c 
void *complete_jobs(void *arg){
	pid_t pid;
	int status;
	
	pid = fork();
	if(pid==0){
		printf("This is a child process, PID %ld and parent PID is %ld\n",(long)getpid(), (long)getppid());
	}
	else if(pid>0){
		printf("This is a child process, PID %ld and parent PID is %ld\n",(long)getpid(), (long)pid);
		printf("Wait for child to terminate\n");
		wait(&status);
		if(WIFEXITED(status)){
		printf("Child process exited with status = %d\n",WEXITSTATUS(status));
		}else{
		printf("ERROR: Child process did not terminate. \n");
		}
	}
	 else
    {
        fprintf(stderr, "Error: process fork failed\n");
        perror("fork");
        exit(EXIT_FAILURE);
    }
	return 0;
}