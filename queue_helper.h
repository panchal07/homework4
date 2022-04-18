/* Header file for the simple circular queue example */
#include <pthread.h>
#ifndef __QUEUE_H__
#define __QUEUE_H__

/*
Reference from Homework 4 files->queue.c
*/
	
typedef struct _queue {
	int size;    
	int *buffer; 
	int start;   
	int end;     
	int count;   
} queue;


typedef struct job
{
    int jid;        
    pthread_t tid;  
    char *cmd;      
    char *stat;     
    int estat;      
    char *start;    
    char *stop;     
    char fnout[10]; 
    char fnerr[10]; 
} jobVal;

//job functions
jobVal newjob(char *command, int jobID);
void jobsDetails(jobVal *jobsList, int val, char *com)

//Queue functions
queue *queue_init(int n);
int queue_insert(queue *q, int item);
int queue_delete(queue *q);
void queue_display(queue *q);
void queue_destroy(queue *q);

//helper functions
int getcmd(char *lineInfo, int numb);
char *getstring(char *str)



#endif
