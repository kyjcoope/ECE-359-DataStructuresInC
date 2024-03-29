// AdjacencyList.c
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct edgeList {
	int data;
	struct edgeList *next;
} *edge; //node
typedef struct adjacencyList {
	edge data;
	struct adjacencyList *next;
} *list; //ad_node
void deleteList(list l);
edge createEdgeNode(int);
list createVertNode(void);
int main()
{
	int c,flag = 1, i = 0, j;
	FILE *fp;
	fopen_s(&fp,"graph.txt", "r");
	list ad_list = (adjacencyList*)malloc(sizeof(adjacencyList));
	ad_list->next = NULL;
	ad_list->data = NULL;
	list walker = ad_list;
	edge temp = walker->data;
	while (1) {
		c = fgetc(fp); //get character from file
		if (feof(fp)) { //end of file stop check
			break;
		}
		if (c != 9) { //tab check
			if (c == 10) { //newline check
				walker->next = createVertNode(); //if newline then need new node
				walker = walker->next;
				flag = 1;
			}
			else if(c==49){ //only add edge to vertexs edges if c=='1' 
				if (flag) { //first node in linklist check
					flag = 0;
					temp = createEdgeNode(c);
					walker->data = temp;
				}
				else {
					temp->next = createEdgeNode(c); //new edge node
					temp = temp->next;
				}
			}
		}
	}
	walker = ad_list;
	i = 0;
	while (walker->next!=NULL) { //outputs vertex degrees
		j = 0;
		temp = walker->data;
		while (temp != NULL) {
			j++;
			temp = temp->next;
		}
		printf("Vertex %d has a degree of %d.\n",i+1,j);
		walker = walker->next;
		i++;
	}
	getchar(); //pause
	deleteList(ad_list); //deletes adjacencyList and all adjacencyList vertex Nodes edge lists
    return 0;
}
edge createEdgeNode(int num) {
	edge temp = (edgeList*)malloc(sizeof(edgeList));
	temp->data = num;
	temp->next = NULL;
	return temp;
}
list createVertNode(void) {
	list temp = (adjacencyList*)malloc(sizeof(adjacencyList));
	temp->next = NULL;
	temp->data = NULL;
	return temp;
}
void deleteList(list l) {
	edge walker1;
	list walker2;
	edge temp1;
	list temp2;
	walker2 = l;
	while (walker2 != NULL) {
		walker1 = walker2->data;
		while (walker1 != NULL) {
			temp1 = walker1;
			walker1 = walker1->next;
			free(temp1);
		}
		temp2 = walker2;
		walker2 = walker2->next;
		free(temp2);
	}
}