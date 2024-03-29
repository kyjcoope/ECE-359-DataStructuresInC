// heap.c
/*Program relies heaviliy on functions given in lecture 9 slides*/
#include "stdafx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct { //heap
	void** heapAry;
	int last;
	int size;
	int(*compare)(void* arg1, void* arg2);
	int maxSize;
	
}HEAP;
typedef struct { //print job
	int priority;
	int arrival;
	int id;
}PRINT;

//Function Prototypes
PRINT* createPrint(void);
HEAP* heapCreate(int maxSize, int(*compare)(void* arg1, void* arg2));
int compareInt(void* x, void* y);
bool heapInsert(HEAP* heap, void* dataPtr);
bool heapDelete(HEAP* heap, void** dataOutPtr);
void process(HEAP* queue);
void outputHeap(HEAP* heap, int);
int isUnique(HEAP* heap, int numPrint, int id_check);
char menu(void);
static void _reheapUp(HEAP* heap, int childLoc);
static void _reheapDown(HEAP* heap, int root);

int main()
{	
	HEAP* heap = heapCreate(10, &compareInt);
	process(heap);
	getchar();
    return 0;
}
void process(HEAP* queue) { //heavily modified version of lecture 9 slide function
	PRINT* print;
	bool result;
	char option;
	int numPrint = -1;
	int test_id;
	time_t t;
	srand((unsigned)time(&t));
	
	do {
		option = menu();
		switch (option){
			case 'i':
				print = createPrint();
				print->priority = rand() % 10 + 1; //random priority from 1-10
				test_id = rand() % 10000; //random id from 0000-9999
				while (isUnique(queue,numPrint,test_id)) { //check heap to see if id is used, if used keep making new ids until unique id found
					test_id = rand() % 10000;
				}
				print->id = test_id;
				print->arrival = (int)time(NULL);
				heapInsert(queue, print);
				numPrint++;
				break;
			case 'd':
				heapDelete(queue, (void**)&print);
				numPrint--;
				break;
			case 'p':
				outputHeap(queue,numPrint);
		}
	} while (option != 'q');
	return;
}
char menu(void) { //heavily modified version of lecture 9 slide function
	char option;
	bool valid;
	printf("\n=========MENU=========\n");
	printf("p:         Print\n");
	printf("i:         Insert\n");
	printf("d:         Delete\n");
	printf("q:         Quit\n");
	printf("Enter option: ");
	do {
		option = getchar();
		option = tolower(option);
		if (option == 'i' || option == 'q' || option == 'd' || option == 'p')
			return option;
	} while (1);
}
PRINT* createPrint(void) { //creates print job
	PRINT* print = (PRINT*)malloc(sizeof(PRINT));
	return print;
}
HEAP* heapCreate(int maxSize, int(*compare)(void* arg1, void* arg2)) { //copied from lecture 9 slides, creates heap
	HEAP* heap;
	heap = (HEAP*)malloc(sizeof(HEAP));
	if (!heap) {
		return NULL;
	}
	heap->last = -1;
	heap->compare = compare;
	heap->size = 0;
	heap->maxSize = (int)pow(2, ceil(log2(maxSize))) - 1;
	heap->heapAry = (void**)calloc(heap->maxSize, sizeof(void*));
	return heap;
}
int compareInt(void* arg1, void* arg2) //compares agr1 and agr2, 0 agr2 bigger,1 arg1 bigger
{ //higher priority is greater, if same earliest arrived is greater
	PRINT p1;
	PRINT p2;
	p1 = *(PRINT*)arg1;
	p2 = *(PRINT*)arg2;

	if (p1.priority < p2.priority) {
		return 0;
	}
	if (p1.priority > p2.priority) {
		return 1;
	}
	if (p1.arrival < p2.arrival) { //p1 arrived first
		return 1;
	}
	else { //p2 arrived first
		return 0;
	}
}
bool heapInsert(HEAP* heap, void* dataPtr) { //copied from lecture 9 slides, inserts print job onto the heap
	if (heap->size == 0) {
		heap->size = 1;
		heap->last = 0;
		heap->heapAry[heap->last] = dataPtr;
		return true;
	}
	if (heap->last == heap->maxSize - 1) {
		return false;
	}
	++(heap->last);
	++(heap->size);
	heap->heapAry[heap->last] = dataPtr;
	_reheapUp(heap, heap->last);
	return true;
}
bool heapDelete(HEAP* heap, void** dataOutPtr) { //copied from lecture 9 slides, deletes top of heap and reheaps
	if (heap->size == 0) {
		return false;
	}
	*dataOutPtr = heap->heapAry[0];
	heap->heapAry[0] = heap->heapAry[heap->last];
	(heap->last)--;
	(heap->size)--;
	_reheapDown(heap, 0);
	return true;
}
void outputHeap(HEAP* heap,int numPrint) { //prints out complete heap
	int i = 0;
	PRINT p;
	while (i <= numPrint) {
		p = *(PRINT*)heap->heapAry[i++];
		printf("{ID: %d, PRIORITY: %d, ARRIVAL: %d}\n", p.id,p.priority,p.arrival);
	}
}
int isUnique(HEAP* heap, int numPrint, int id_check) { //checks if id of print job is unique
	int i = 0;
	PRINT p;
	while (i <= numPrint&&numPrint>-1) {
		p = *(PRINT*)heap->heapAry[i++];
		if (p.id == id_check) {
			return 1;
		}
	}
	return 0;
}
void _reheapUp(HEAP* heap, int childLoc) { //copied from lecture 9 slides, pulls up print job from bottom of heap to where it belongs
	int parent;
	void** heapAry;
	void* hold;
	if (childLoc) {
		heapAry = heap->heapAry;
		parent = (childLoc - 1) / 2;
		if (heap->compare(heapAry[childLoc], heapAry[parent]) > 0) {
			hold = heapAry[parent];
			heapAry[parent] = heapAry[childLoc];
			heapAry[childLoc] = hold;
			_reheapUp(heap, parent);
		}
	}
	return;
}
void _reheapDown(HEAP* heap, int root) { //copied from lecture 9 slides, pushes print job at top of heap down to where it belongs
	void* hold;
	void* leftData;
	void* rightData;
	int largeLoc;
	int last;
	last = heap->last;
	if((root*2+1)<=last){
		leftData = heap->heapAry[root * 2 + 1];
		if ((root * 2 + 2) <= last)
			rightData = heap->heapAry[root * 2 + 2];
		else
			rightData = NULL;
		if ((!rightData) || heap->compare(leftData, rightData) > 0) {
			largeLoc = root * 2 + 1;
		}
		else {
			largeLoc = root * 2 + 2;
		}
		if (heap->compare(heap->heapAry[root], heap->heapAry[largeLoc]) <= 0) { //0 agr2 bigger,1 arg1 bigger, this line was modified from original "<" changed to "<="
			hold = heap->heapAry[root];
			heap->heapAry[root] = heap->heapAry[largeLoc];
			heap->heapAry[largeLoc] = hold;
			_reheapDown(heap, largeLoc);
		}
	}
	return;
}