// AVLTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
typedef struct tree {
	char line[128];
	struct tree *left;
	struct tree *right;
	struct tree *parent;
}*node;
node newnode(char *b);
node AVLInsert(node root, char *newData);
node leftBalance(node root);
node rightBalance(node root);
node rotateRight(node root);
node rotateLeft(node root);
int height(node root);
void inorder(node);
int findheight(node n);
void deleteTree(node n);
int main()
{
	char line[128];
	FILE *f_source;
	node root = NULL;
	char *pos;
	if ((fopen_s(&f_source,"text.txt", "r")) != NULL) {
		perror("Error");
		return 0;
	}
	while (fgets(line, sizeof(line), f_source) != NULL) {
		if ((pos = strchr(line, '\n')) != NULL) //remove \n from line
			*pos = '\0';
		root = AVLInsert(root, line);
	}
	fclose(f_source);
	printf("inorder\n");
	inorder(root);
	deleteTree(root);
    return 0;
}
node newnode(char *b) {
	node temp;
	temp = (struct tree*)malloc(sizeof(struct tree));
	strcpy_s(temp->line, b);
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	return(temp);
}
node AVLInsert(node root, char *newData) {
	if (root == NULL) {
		root = newnode(newData);
		return root;
	}
	if (strcmp(newData,root->line)<0) {
		root->left = AVLInsert(root->left, newData);
		root->left->parent = root;
		if (height(root->left)-1>height(root->right)) { // -1 cause 1 lvl diff is still balanced
			root = leftBalance(root);
		}
	}
	else {
		root->right = AVLInsert(root->right, newData);
		root->right->parent = root;
		if (height(root->right)-1>height(root->left)) { // -1 cause 1 lvl diff is still balanced
			root = rightBalance(root);
		}
	}
	return root;
}
node leftBalance(node root) {
	if (height(root->left->left)>height(root->left->right)) { //root->left->left and root->left->right
		root = rotateRight(root); //rotates might need return value
	}
	else {
		root->left = rotateLeft(root->left); //
		root = rotateRight(root); //
	}
	return root;
}
node rightBalance(node root) {
	if (height(root->right->right)>height(root->right->left)) { //root->right->left and root->right->right
		root = rotateLeft(root); //
	}
	else {
		root->right = rotateRight(root->right); //
		root = rotateLeft(root); //
	}
	return root;
}
node rotateRight(node root) {
	node temp1, temp2;
	temp1 = root->left->right;
	temp2 = root;
	root->parent = root->left;
	root = root->left;
	root->parent = NULL;
	root->right = temp2;
	root->right->left = temp1;
	if (root->right->left != NULL) {
		root->right->left->parent = root->right;
	}
	
	return root;
}
node rotateLeft(node root) {
	node temp1, temp2;
	temp1 = root->right->left;
	temp2 = root;
	root->parent = root->right;
	root = root->right;
	root->parent = NULL;
	root->left = temp2;
	root->left->right = temp1;
	if (root->left->right != NULL) {
		root->left->right->parent = root->right;
	}
	return root;
}
int height(node root) {
	int left, right;
	if (root == NULL) {
		return 0;
	}
	left = height(root->left);
	right = height(root->right);
	if (left > right) {
		return left+1;
	}
	if (right > left) {
		return right+1;
	}
	if (right == left) {
		return right+1;
	}
}
void inorder(node n) {
	int i;
	if (n != NULL)
	{
		inorder(n->left);
		i = findheight(n);
		printf("%s\t%d\n", n->line,i);
		inorder(n->right);
	}
}
int findheight(node n) {
	int i = 0;
	while (n->parent != NULL) {
		i++;
		n = n->parent;
	}
	return i;
}
void deleteTree(node n) {
	if (n != NULL)
	{
		deleteTree(n->left);
		deleteTree(n->right);
		free(n);
	}
}
