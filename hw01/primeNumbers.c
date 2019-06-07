// PrimeNumbers.c

#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct numberList { //struct for linked list
	int primeFlag;
	int number;
	struct numberList *nextNode;
};

typedef struct numberList *node; //function prototypes / typedef
node createNode();
node addNode(node, int);
void deleteList(node);

int main()
{
	//declarations
	int num, total = 1,newline=0;
	node primeList = createNode();
	primeList->number = 2;
	primeList->primeFlag = 0;
	node nextNode = primeList;

	//user input
	printf("Input integer: ");
	scanf("%d", &num);

	//build linked list
	clock_t begin = clock();
	printf("Building list\n");
	for (int i = 3; i <= num; i+=2) {
		nextNode = addNode(nextNode, i);
	}
	printf("Done building list\n");

	//skip over 2, evens are bad
	node walker1 = primeList->nextNode;
	node walker2;

	//find primes
	printf("Finding primes\n");
	for (int i = 3; i <= int(sqrt(num)); i+=2) { //only need to find multiples for primes up too sqrt(n)
		if (walker1->primeFlag == 0) { //if not marked will be the next prime
			walker2 = walker1;
			for (int j = i*2; j <= num-i; j+=i*2) { //increments list by current prime value to remove multiples of that prime
				for (int z = 0; z < i; z++) { //move through linked list
					walker2 = walker2->nextNode;
				}
				walker2->primeFlag = 1; //mark as not prime
			}
		}
		walker1 = walker1->nextNode;//move through linked list
	}
	printf("Done finding primes\n");
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //execution time

	printf("Saving list to output.txt\n");
	FILE *outFile = fopen("output.txt", "w");
	if (outFile == NULL)
	{
		printf("Error opening file!\n");
		return 0;
	}

	node walker = primeList->nextNode;
	fprintf(outFile, "%d, ", primeList->number); //output primes to output.txt
	while (walker!=NULL) {
		if (walker->primeFlag == 0) {
			total++;
			if (newline == 10) {
				fprintf(outFile,"\n");
				newline = 0;
			}
			else {
				newline++;
			}
			fprintf(outFile, "%d, ", walker->number);
		}
		walker = walker->nextNode;
	}
	fprintf(outFile,"\nTotal number of primes found: %d\n", total);
	fprintf(outFile,"Total execution time: %lf\n", time_spent);
	fclose(outFile);
	printf("Done saving list\n");
	
	deleteList(primeList);
	scanf("%d", &num); //this is just here to stop visual studio from ending program right away
    return 0;
}
node createNode() { //create new linked list node
	node temp;
	temp = (node)malloc(sizeof(struct numberList));
	temp->nextNode = NULL;
	return temp;
};
node addNode(node current, int value) { //add node to linked list
	node temp;
	temp = createNode();
	temp->number = value;
	temp->primeFlag = 0;
	current->nextNode = temp;
	return temp; 
};
void deleteList(node head){//delete linked list
	node current = head;
	node next;
	while (current != NULL)
	{
		next = current->nextNode;
		free(current);
		current = next;
	}
	head = NULL;
}