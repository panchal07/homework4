/* Implementation of a simple circular queue using a static array */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "queue.h"

/*
Reference: from Homework 4 files->queue.tar
*/
/* create the queue data structure and initialize it */
queue *queue_init(int n)
{
    queue *q = malloc(sizeof(queue));
    q->size = n;
    q->buffer = malloc(sizeof(job *) * n);
    q->start = 0;
    q->end = 0;
    q->count = 0;

    return q;
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
job *queue_delete(queue *q)
{
    if ((q == NULL) || (q->count == 0))
        return (job *)-1;

    job *j = q->buffer[q->start];
    q->start = (q->start + 1) % q->size;
    --q->count;

    return j;
}

/* delete an item from the queue, update the pointers and count, and 
   return the item deleted (-1 if queue is null or empty) */
int queue_delete(queue *q) {
	if ((q == NULL) || (q->count == 0))
	   return -1;

	int x = q->buffer[q->start];
	q->start = (q->start + 1) % q->size;
	q->count--;

	return x;
}

/* display the contents of the queue data structure */
void queue_display(queue *q) {
	int i;
	if (q != NULL && q->count != 0) {
		printf("queue has %d elements, start = %d, end = %d\n", q->count, q->start, q->end);
		printf("queue contents: ");
		for (i = 0; i < q->count; i++)
	    		printf("%d ", q->buffer[(q->start + i) % q->size]);
		printf("\n");
	} else
		printf("queue empty, nothing to display\n");
}

/* delete the queue data structure */
void queue_destroy(queue *q)
{
    free(q->buffer);
    free(q);
}

//job Functions
jobVal newjob(char *command, int jid)
{
    job j;
    j.jid = jid;
    j.cmd = get_copy(command);
    j.stat = "waiting";
    j.estat = -1;
    j.start = NULL;
    j.stop = NULL;
    sprintf(j.fnout, "%d.out", j.jid);
    sprintf(j.fnerr, "%d.err", j.jid);
    return j;
}

int getcmd(char *lineInfo, int numb)
{
    int i, str;
    for (i = 0; i < numb - 1 && (str = getchar()) != '\n'; ++i)
    {
        if (str == EOF){
            return -1;
        }
        lineInfo[i] = str;
    }
    lineInfo[i] = '\0';
    return i;
}

char *getstring(char *str)
{
    int i=-1; 
    int chars;
    char *newstr;
    newstr = malloc(sizeof(char) * strlen(str));
    while (chars = str[++i]){
        if(chars !='\0'){
            newstr[i] = chars;
        }
    }
    newstr[i] = '\0'; 
    return newstr;
}


/*Implemented using github code*/
/*
https://github.com/eolatham/job-scheduler/blob/master/job_scheduler.c
*/
void jobsDetails(jobval *jobsList, int val, char *com)
{
    int i;
    if (jobsList != NULL && val != 0)
    {
        if (strcmp(com, "showjobs") == 0)
        {
            printf("jobid \t command \t\t\t status\n");
            for (i = 0; i < val; ++i)
            {
                if (strcmp(jobsList[i].stat, "success") != 0)
                    printf("%d\t%s\t\t\t%s\n",jobsList[i].jid,
                           jobsList[i].cmd,
                           jobsList[i].stat);
            }
        }
        else if (strcmp(com, "submithistory") == 0)
        {
            printf("jobid \t command \t\t\t starttime \t endtime \t status\n");
            for (i = 0; i < val; ++i)
            {
                if (strcmp(jobsList[i].stat, "success") == 0)
                    printf(" %d  %s %s %s %s\n",
                           jobsList[i].jid,
                           jobsList[i].cmd,
                           jobsList[i].start,
                           jobsList[i].stop,
                           jobsList[i].stat
                           );
            }
        }
    }
}