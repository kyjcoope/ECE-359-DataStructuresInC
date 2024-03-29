// BTree.c
/*Program is not complete and does not work at all in it's current state*/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
const int ORDER = 3; 
const int MIN_ENTRIES = ((ORDER+1)/2)-1;
//structs
typedef struct {
	int dataPtr;
	struct node* rightPtr;
} ENTRY;
typedef struct node {
	struct node* firstPtr;
	int numEntries;
	ENTRY entries[ORDER - 1];
} NODE;
typedef struct {
	int count;
	NODE* root;
	//int(*compare)(void* arg1, void* arg2);
} BTREE;
//function prototypes
int BTree_Search(BTREE* tree, int targetPtr);
int _search(BTREE* tree, int targetPtr, NODE* root);
void BTree_Traverse(BTREE* tree);
void _traverse(NODE* root);
void BTree_Insert(BTREE* tree, int dataInPtr);
bool _insert(BTREE* tree, NODE* root, int dataInPtr, ENTRY* upEntry);
void _splitNode(NODE* node, int entryNdx, int compResult, ENTRY* upEntry);
bool BTree_Delete(BTREE* tree, int dltKey);
bool _delete(BTREE* tree, NODE* root, int dltKeyPtr, bool* success);
bool _deleteMid(NODE* root, int entryNdx, NODE* subtreePtr);
bool _reFlow(NODE* root, int entryNdx);
void _borrowRight(NODE* root, int entryNdx, NODE* leftTreePtr, NODE* rightTreePtr);
void _borrowLeft(NODE* root, int entryNdx, NODE* leftTreePtr, NODE* rightTreePtr);
void _combine(NODE* root, int entryNdx, NODE* leftTreePtr, NODE* rightTreePtr);
void _insertEntry(NODE* root, int entryNdx, ENTRY upEntry);
int _deleteEntry(NODE* root, int entryNdx);
int compareInt(int x, int y);
int main()
{
	int num;
	BTREE* btree = (BTREE*)malloc(sizeof(BTREE)); //create btree
	btree->root = NULL;
	btree->count = 0;
	for (int i = 0; i < 5; i++) { //test insert
		scanf_s("%d", &num);
		BTree_Insert(btree, num);
	}
	scanf_s("%d", &num);
	num = BTree_Search(btree, num); //test search
	printf("%d\n", num);
	getchar();
    return 0;
}
int compareInt(int arg1, int arg2) //compares agr1 and agr2, 0 agr2 bigger,1 arg1 bigger
{ //higher priority is greater, if same earliest arrived is greater
	return (arg2 - arg1);
}
int BTree_Search(BTREE* tree, int targetPtr) { //search tree for node with key
	if (tree->root) {
		return _search(tree, targetPtr, tree->root);
	}
	else {
		return NULL;
	}
}
int _search(BTREE* tree, int targetPtr, NODE* root) { //search entry
	int entryNo;
	if (!root) {
		return NULL;
	}
	if (compareInt(targetPtr, root->entries[0].dataPtr) < 0) {
		return _search(tree, targetPtr, root->firstPtr);
	}
	entryNo = root->numEntries - 1;
	while (compareInt(targetPtr, root->entries[entryNo].dataPtr) < 0) {
		entryNo--;
	}
	if (compareInt(targetPtr, root->entries[entryNo].dataPtr) == 0) {
		return (root->entries[entryNo].dataPtr);
	}
}
void BTree_Traverse(BTREE* tree) {
	if (tree->root) {
		_traverse(tree->root);
	}
	return;
}
void _traverse(NODE* root) {
	int scanCount = 0;
	NODE* ptr;
	ptr = root->firstPtr;
	while (scanCount <= root->numEntries) {
		if (ptr) {
			_traverse(ptr);
		}
		if (scanCount < root->numEntries) {
			printf("%d\n",root->entries[scanCount].dataPtr);
			ptr = root->entries[scanCount].rightPtr;
		}
		scanCount++;
	}
	return;
}
void BTree_Insert(BTREE* tree, int dataInPtr) {
	bool taller;
	NODE* newPtr;
	ENTRY upEntry;

	if (tree->root == NULL) {
		if (newPtr = (NODE*)malloc(sizeof(NODE))) {
			newPtr->firstPtr = NULL;
			newPtr->numEntries = 1;
			newPtr->entries[0].dataPtr = dataInPtr;
			newPtr->entries[0].rightPtr = NULL;
			tree->root = newPtr;
			(tree->count)++;
			for (int i = 1; i < ORDER - 1; i++) {
				newPtr->entries[i].dataPtr = NULL;
				newPtr->entries[i].rightPtr = NULL;
			}
			return;
		}
		else {
			printf("ERROR 100 in BTree_Insert\a\n"), exit(100);
		}
	}
	taller = _insert(tree, tree->root, dataInPtr, &upEntry);
	if (taller) {
		newPtr = (NODE*)malloc(sizeof(NODE));
		if (newPtr) {
			newPtr->entries[0] = upEntry;
			newPtr->firstPtr = tree->root;
			newPtr->numEntries = 1;
			tree->root = newPtr;
		}
		else {
			printf("Overflow error 101\a\n"), exit(100);
		}
	}
	(tree->count)++;
	return;
}
bool _insert(BTREE* tree, NODE* root, int dataInPtr, ENTRY* upEntry) {
	int compResult;
	int entryNdx;
	bool taller;

	NODE* subtreePtr;

	if (!root) {
		(*upEntry).dataPtr = dataInPtr;
		(*upEntry).rightPtr = NULL;
		return true;
	}
	entryNdx = (int)_search(tree, dataInPtr, root);
	compResult = compareInt(dataInPtr, root->entries[entryNdx].dataPtr);
	if (entryNdx <= 0 && compResult < 0) {
		subtreePtr = root->firstPtr;
	}
	else {
		subtreePtr = root->entries[entryNdx].rightPtr;
	}
	taller = _insert(tree, subtreePtr, dataInPtr, upEntry);
	if (taller) {
		if (root->numEntries >= ORDER - 1) {
			_splitNode(root, entryNdx, compResult, upEntry);
			taller = true;
		}
		else {
			if (compResult >= 0) {
				_insertEntry(root, entryNdx + 1, *upEntry);
			}
			else {
				_insertEntry(root, entryNdx, *upEntry);
			}
			(root->numEntries)++;
			taller = false;
		}
	}
	return taller;
}
void _splitNode(NODE* node, int entryNdx, int compResult, ENTRY* upEntry) {
	int fromNdx;
	int toNdx;
	NODE* rightPtr;

	rightPtr = (NODE*)malloc(sizeof(NODE));
	if (!rightPtr) {
		printf("Overflow error 101 in _splitNode\a\n"), exit(100);
	}
	if (entryNdx < MIN_ENTRIES) {
		fromNdx = MIN_ENTRIES;
	}
	else {
		fromNdx = MIN_ENTRIES + 1;
	}
	toNdx = 0;
	rightPtr->numEntries = node->numEntries - fromNdx;
	while (fromNdx < node->numEntries) {
		rightPtr->entries[toNdx++] = node->entries[fromNdx++];
	}
	node->numEntries = node->numEntries - rightPtr->numEntries;
	if (entryNdx < MIN_ENTRIES) {
		if (compResult < 0) {
			_insertEntry(node, entryNdx, *upEntry);
		}
		else {
			_insertEntry(node, entryNdx + 1, *upEntry);
		}
	}
	else {
		_insertEntry(rightPtr, entryNdx - MIN_ENTRIES, *upEntry);
		(rightPtr->numEntries)++;
		(node->numEntries)--;
	}
	upEntry->dataPtr = node->entries[MIN_ENTRIES].dataPtr;
	upEntry->rightPtr = rightPtr;
	rightPtr->firstPtr = node->entries[MIN_ENTRIES].rightPtr;
	return;
}
bool BTree_Delete(BTREE* tree, int dltKey) {
	bool success;
	NODE* dltPtr;

	if (!tree->root) {
		return false;
	}
	_delete(tree, tree->root, dltKey, &success);
	if (success) {
		(tree->count)--;
		if (tree->root->numEntries == 0) {
			dltPtr = tree->root;
			tree->root = tree->root->firstPtr;
			free(dltPtr);
		}
	}
	return success;

}
bool _delete(BTREE* tree, NODE* root, int dltKeyPtr, bool* success) {
	NODE* leftPtr;
	NODE* subTreePtr;
	int entryNdx;
	int underflow;

	if (!root) {
		*success = false;
		return false;
	}
	entryNdx = _search(tree, dltKeyPtr, root);
	if (compareInt(dltKeyPtr, root->entries[entryNdx].dataPtr) == 0) {
		*success = true;
		if (root->entries[entryNdx].rightPtr == NULL) {
			underflow = _deleteEntry(root, entryNdx);
		}
		else {
			if (entryNdx > 0) {
				leftPtr = root->entries[entryNdx - 1].rightPtr;
			}
			else {
				leftPtr = root->firstPtr;
			}
			underflow = _deleteMid(root, entryNdx, leftPtr);
			if (underflow) {
				underflow = _reFlow(root, entryNdx);
			}
		}
	}
	else {
		if (compareInt(dltKeyPtr, root->entries[0].dataPtr) < 0) {
			subTreePtr = root->firstPtr;
		}
		else {
			subTreePtr = root->entries[entryNdx].rightPtr;
		}
		underflow = _delete(tree, subTreePtr, dltKeyPtr, success);
		if (underflow) {
			underflow = _reFlow(root, entryNdx);
		}
	}
	return underflow;
}
bool _deleteMid(NODE* root, int entryNdx, NODE* subtreePtr) {
	int dltNdx;
	int rightNdx;
	bool underflow;

	if (subtreePtr->firstPtr == NULL) {
		dltNdx = subtreePtr->numEntries - 1;
		root->entries[entryNdx].dataPtr = subtreePtr->entries[dltNdx].dataPtr;
		underflow = subtreePtr->numEntries < MIN_ENTRIES;
	}
	else {
		rightNdx = subtreePtr->numEntries - 1;
		underflow = _deleteMid(root, entryNdx, subtreePtr->entries[rightNdx].rightPtr);
		if (underflow) {
			underflow = _reFlow(subtreePtr, rightNdx);
		}
	}
	return underflow;
}
bool _reFlow(NODE* root, int entryNdx) {
	NODE* leftTreePtr;
	NODE* rightTreePtr;
	bool underflow;

	if (entryNdx == 0) {
		leftTreePtr = root->firstPtr;
	}
	else {
		leftTreePtr = root->entries[entryNdx - 1].rightPtr;
	}
	rightTreePtr = root->entries[entryNdx].rightPtr;
	if (rightTreePtr->numEntries < MIN_ENTRIES) {
		_borrowRight(root, entryNdx, leftTreePtr, rightTreePtr);
		underflow = false;
	}
	else {
		if (leftTreePtr->numEntries > MIN_ENTRIES) {
			_borrowLeft(root, entryNdx, leftTreePtr, rightTreePtr);
			underflow = false;
		}
		else {
			_combine(root, entryNdx, leftTreePtr, rightTreePtr);
			underflow = (root->numEntries < MIN_ENTRIES);
		}
	}
	return underflow;
}
void _borrowRight(NODE* root, int entryNdx, NODE* leftTreePtr, NODE* rightTreePtr) {
	int toNdx;
	int shifter;
	toNdx = leftTreePtr->numEntries;
	leftTreePtr->entries[toNdx].dataPtr = root->entries[entryNdx].dataPtr;
	leftTreePtr->entries[toNdx].rightPtr = rightTreePtr->firstPtr;
	++leftTreePtr->numEntries;
	root->entries[entryNdx].dataPtr = rightTreePtr->entries[0].dataPtr;
	rightTreePtr->firstPtr = rightTreePtr->entries[0].rightPtr;
	shifter = 0;
	while (shifter < rightTreePtr->numEntries - 1) {
		rightTreePtr->entries[shifter] = rightTreePtr->entries[shifter + 1];
		shifter++;
	}
	--rightTreePtr->numEntries;
	return;
}
void _borrowLeft(NODE* root, int entryNdx, NODE* leftTreePtr, NODE* rightTreePtr) {
	int toNdx;
	int shifter;
	toNdx = rightTreePtr->numEntries;
	rightTreePtr->entries[toNdx].dataPtr = root->entries[entryNdx].dataPtr;
	rightTreePtr->entries[toNdx].rightPtr = leftTreePtr->firstPtr;
	++rightTreePtr->numEntries;
	root->entries[entryNdx].dataPtr = leftTreePtr->entries[0].dataPtr;
	leftTreePtr->firstPtr = leftTreePtr->entries[0].rightPtr;
	shifter = 0;
	while (shifter < leftTreePtr->numEntries - 1) {
		leftTreePtr->entries[shifter] = leftTreePtr->entries[shifter + 1];
		shifter++;
	}
	--leftTreePtr->numEntries;
	return;
}
void _combine(NODE* root, int entryNdx, NODE* leftTreePtr, NODE* rightTreePtr) {
	int toNdx;
	int fromNdx;
	int shifter;

	toNdx = leftTreePtr->numEntries;
	leftTreePtr->entries[toNdx].dataPtr = root->entries[entryNdx].dataPtr;
	leftTreePtr->entries[toNdx].rightPtr = rightTreePtr->firstPtr;
	++leftTreePtr->numEntries;
	--root->numEntries;
	fromNdx = 0;
	toNdx++;
	while (fromNdx < rightTreePtr->numEntries) {
		leftTreePtr->entries[toNdx++] = rightTreePtr->entries[fromNdx++];
	}
	leftTreePtr->numEntries += rightTreePtr->numEntries;
	free(rightTreePtr);
	shifter = entryNdx;
	while (shifter < root->numEntries) {
		root->entries[shifter] = root->entries[shifter + 1];
		shifter++;
	}
	return;
}
void _insertEntry(NODE* root, int entryNdx, ENTRY upEntry) {

}
int _deleteEntry(NODE* root, int entryNdx) {
	return 0;
}
void inorder(NODE* node, ENTRY* entry) {
	for (int i = 0; i < 3; i++) {

	}
}