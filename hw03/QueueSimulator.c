#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

struct queue {
	int min, hour;
	queue* nextNode;
};
struct doctorList {
	int seen,wait;
	doctorList* nextNode;
};
typedef struct queue *q_node;
typedef struct doctorList *d_node;
d_node createList();
d_node add_d_node(d_node);
q_node enqueue(q_node,int,int);
q_node dequeue(q_node);
q_node front();
d_node temp_d;
int start_hour, start_min, min = 0, hour = 0;

int main()
{
	//declarations
	srand(time(NULL));
	int temp = 0, count = 0,D, rp, rm,i=1,j=1,num=0,z=1;
	d_node d_list = NULL, current = NULL;
	q_node front = NULL, rear = NULL;
	

	//amount of doctors
	printf("Enter number of doctors: ");
	scanf_s("%d", &D);
	printf("\n");
	//build list of doctors
	while (D--) {
		if (d_list == NULL) {
			d_list = createList();
			current = d_list;
		}
		else {
			current = add_d_node(current);
		}
	}
	const char *delim1 = ":";
	const char *delim2 = " ";
	char *token1;
	char *token2;
	char *nextToken;
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	/* get the first token */
	token1 = strtok_s(str,delim2,&nextToken);
	while (token1 != NULL) {
		if (i == 4) {
			token2 = strtok_s(token1, delim1, &nextToken);
			while (token2 != NULL) {
				if (j == 1) {
					start_hour = atoi(token2);
				}
				else if (j == 2) {
					start_min = atoi(token2);
				}
				j++;
				token2 = strtok_s(NULL, delim1, &nextToken);			
			}
		}
		token1 = strtok_s(NULL, delim2, &nextToken);
		i++;
	}
	
	//run sim
	while (hour<2) {
		min++;
		if (min>=60) {
			hour++;
			min = 0;
		}		
		rp = rand() % 3; // 1 and 3 chance patient show up every min
		rm = rand() % 3;// 0, 1, or 2 patients show up when a patient shows up^
		if (!rp) { //place patient/patients in queue
			while (rm--) {
				if (front == NULL) {
					rear = enqueue(rear, hour, min);
					front = rear;
				}
				else {
					rear = enqueue(rear, hour, min);
				}
				count++;
				num++;
			}
		}
		current = d_list;
		while (current != NULL) {
				if (!current->wait&&front != NULL&&num) { //if not waiting
					if (current->seen) { //if doctor has seen someone before
						count--;
						printf("Patient %d\n", z++);
						front = dequeue(front);

					}
					current->wait = 14;
					current->seen++;
					num--;
				}
				else if (current->wait>0) { //dec waiting
					current->wait--;
				}
				current = current->nextNode;
		}
	}

	printf("%d patients left in queue.\n",count);
	current = d_list;
	i = 1;
	while (current != NULL) {
		printf("Doctor %d saw %d patients.\n", i, current->seen-1);
		current = current->nextNode;
		i++;
	}
	scanf_s(" %d", hour);
	
	while (d_list != NULL) {
		temp_d = d_list;
		d_list = d_list->nextNode;
		free(temp_d);
	}
	temp_d = NULL;
	d_list = NULL;
	current = NULL;
	rear = NULL;
	front = NULL;
    return 0;
}
d_node createList() {
	d_node temp;
	temp = (d_node)malloc(sizeof(struct queue));
	temp->nextNode = NULL;
	temp->seen = 0;
	temp->wait = 0;
	return temp;
 }
d_node add_d_node(d_node current) {
	d_node temp;
	temp = (d_node)malloc(sizeof(struct queue));
	current->nextNode = temp;
	temp->nextNode = NULL;
	temp->seen = 0;
	temp->wait = 0;
	return temp;
}
q_node enqueue(q_node current,int h,int m) {
	q_node temp;
	temp = (q_node)malloc(sizeof(struct queue));
	if (current != NULL) {
		current->nextNode = temp;
	}
	else {
		current = temp;
	}
	temp->nextNode = NULL;
	temp->hour = h;
	temp->min = m;
	return temp;
}
q_node dequeue(q_node current) {
	q_node temp;
	int min_sum,i=0,j=0,min_left,min_wait,k=0;
	if (current->min + start_min >= 60) {//arrive time
		min_sum = current->min + start_min;
		while (1) {
			if (min_sum >= 60) {
				i++;
				min_sum = min_sum - 60;
			}
			else {
				break;
			}
		}
	}
	else {
		min_sum = current->min + start_min;
	}
	if (min + start_min >= 60) { //left time
		min_left = min + start_min;
		while (1) {
			if (min_left >= 60) {
				j++;
				min_left = min_left - 60;
			}
			else {
				break;
			}
		}
	}
	else {
		min_left = min + start_min;
	}
	printf("Time arrived: %d:%d\n", start_hour + i, min_sum);
	printf("Time left: %d:%d\n", start_hour +j,min_left);
	printf("Time waited: %d minutes \n\n", hour*60+min-current->min);
	temp = current->nextNode;
	free(current);
	current = NULL;
	return temp;
}
q_node front() {
	q_node temp = NULL;
	return temp;
}