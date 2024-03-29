// SortedLinkedList.c
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//prototypes/declarations
struct LinkedList{
	int num;
	LinkedList* nextNode;
};
typedef struct LinkedList *node;
node addLink(node link, int num);
void recursiveFind(node node, int num);
void iterativeFind(node node, int num);
void freeList(node head);

int main()
{	
	//declarations
	node walker,head = (node)malloc(sizeof(struct LinkedList));
	srand(time(NULL));
	int r,i;
	head->num = NULL;
	head->nextNode = NULL;
	char word[256];

	//program commands/options
	printf("Press 'a', then enter to add a number into the linkedlist.\n"); 
	printf("Press 'i', to preform an iterative search for a number.\n");
	printf("Press 'r', to preform a recursive search for a number.\n\n");
	printf("Press 'p', to display list.\n\n");
	printf("Press 'q', to end program.\n\n");

	//make a list of 100 random numbers from 1-100
	for (i = 0; i < 100; i++) { 
		r = rand()%100+1;
		head = addLink(head, r);
	}
	while (1) {
		printf("Enter command: ");
		fgets(word, sizeof(word), stdin); //gets input for user selection
		if (!strcmp(word,"i\n")) { //iterative search
			printf("Enter an integer to find: ");
			fgets(word, sizeof(word), stdin);
			iterativeFind(head, atoi(word));
		}
		if (!strcmp(word, "a\n")) { //add integer to list
			printf("Enter an integer to add: ");
			fgets(word, sizeof(word), stdin);
			head = addLink(head, atoi(word));
		}
		if (!strcmp(word, "r\n")) { //recursive search
			printf("Enter an integer to find: ");
			fgets(word, sizeof(word), stdin);
			recursiveFind(head, atoi(word));
		}
		if (!strcmp(word, "p\n")) { //print list
			walker = head;
			while (walker != NULL) {
				printf("%d\n", walker->num);
				walker = walker->nextNode;
			}
		}
		if (!strcmp(word, "q\n")) { //quit program
			freeList(head);
			return 0;
		}
	}
    return 0;
}
node addLink(node head,int num) {
	if (head->num==NULL) { //if first number
		head->num = num;
	}
	else {
		node temp,walker;
		temp = (node)malloc(sizeof(struct LinkedList));
		if (head->num >= num) {//if replacing first number
			temp->nextNode = head;
			temp->num = num;
			head = temp;
		}
		else {
			walker = head;
			while (walker->nextNode != NULL) {//finding number
				if (walker->nextNode->num>num) {
					temp->nextNode = walker->nextNode;
					walker->nextNode = temp;
					temp->num = num;
					return head; //found number so leave now
				}
				walker = walker->nextNode;
			}
			walker->nextNode = temp; //if number wasn't found add to the end
			temp->nextNode = NULL;
			temp->num = num;
		}	
	}
	return head; //incase a node was added to the front so head can be updated.
}
void recursiveFind(node node, int num) {//recursive search
	if (node->num == num) {//found
		printf("%d was in the list\n",node->num);
		return;
	}
	else if(node->nextNode != NULL){//keep searching
		recursiveFind(node->nextNode, num);
	}
	else {//not in list
		printf("%d was not in the list.\n", num);
	}
}
void iterativeFind(node node, int num) {//iterative search

	while (node != NULL) {//searching list
		if (node->num == num) {
			printf("%d was in the list.\n", node->num);//found
			return;
		}
		node = node->nextNode;
	}
	printf("%d was not in the list.\n", num);//not found
}
void freeList(node head) {//free list
	node temp;
	while (head != NULL) {//keep freeing until done
		temp = head;
		head = head->nextNode;
		free(temp);
	}
}