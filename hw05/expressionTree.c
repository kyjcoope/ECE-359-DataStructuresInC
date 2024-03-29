// expressionTree.c
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<malloc.h>

//struct instantiation
typedef struct tree {
	char data;
	struct tree *left;
	struct tree *right;
}*node;
node newnode(char b) {
	node temp;
	temp = (struct tree*)malloc(sizeof(struct tree));
	temp->data = b;
	temp->left = NULL;
	temp->right = NULL;
	return(temp);
}

//used for stack
char stack[32];
int top = -1;

//function prototypes
void push(char);
char pop();
void inorder(node);
void preorder(node);
void postorder(node);
int precedence(char, char);
int isOperator(char);
int isOp(node);
void deleteTree(node);
void main() {
	//declarations
	char word[32];
	int i, j = 0;
	node pt[32] = { NULL };

	//take user input
	printf("\nEnter the infix expression\n");
	fgets(word, sizeof(word), stdin);

	//start converting infix str to postfix 
	for (i = 0; word[i] != '\n'; i++)
	{
		if (word[i] == '*' || word[i] == '+' || word[i] == '-')
		{
			if (top == -1 || stack[top] == '(') {
				push(word[i]);
			}
			else if (precedence(word[i], stack[top]) == 1) { // higher precedence
				push(word[i]);
			}
			else if (precedence(word[i], stack[top]) == 0) { // equal precedence
				pt[j++] = newnode(pop());
				push(word[i]);
			}
			else if (precedence(word[i], stack[top]) == -1) { // lower precedence
				pt[j++] = newnode(pop());
				while (precedence(word[i], stack[top]) == -1) { //keep doing while lower precedence
					pt[j++] = newnode(pop());
				}
				if (precedence(word[i], stack[top]) == 1) { // higher precedence
					push(word[i]);
				}
				if (precedence(word[i], stack[top]) == 0) { // equal precedence
					pt[j++] = newnode(pop());
					push(word[i]);
				}
				if (top == -1 || stack[top] == '(') {
					push(word[i]);
				}
			}
		}
		else if (word[i] == '(') {
			push(word[i]);
		}
		else if (word[i] == ')') {
			while (stack[top] != '(') {
				pt[j++] = newnode(pop());
			}
			pop(); //remove '('
		}
		else
		{
			pt[j++] = newnode(word[i]);
		}
	}
	while (top != -1) {
		pt[j++] = newnode(pop());
	} //infix done converting to postfix

	  //start building tree
	while (pt[1] != NULL) {
		i = 0;
		while (!isOp(pt[i++]));
		pt[i - 1]->left = pt[i - 3];
		pt[i - 1]->right = pt[i - 2];
		while (pt[i - 1] != NULL) {
			pt[i - 3] = pt[i - 1];
			i++;
		}
		pt[i - 2] = NULL;
		pt[i - 3] = NULL;

	}
	
	node n = pt[0]; //done building tree
	pt[0] = NULL; //just to prove tree is built and it's not just an array

	//output postorder, preorder, and inorder traversals of expression tree
	printf("Postorder: ");
	postorder(n);
	printf("\n");
	printf("Inorder: ");
	inorder(n);
	printf("\n");
	printf("Preorder: ");
	preorder(n);
	printf("\n");
	deleteTree(n);
	_getch();
}
void push(char c) {
	stack[++top] = c;
}
char pop() {
	char c;
	c = stack[top--];
	return(c);
}
void inorder(node n) {
	if (n != NULL)
	{
		inorder(n->left);
		printf("%c", n->data);
		inorder(n->right);
	}
}
void preorder(node n) {
	if (n != NULL)
	{
		printf("%c", n->data);
		preorder(n->left);
		preorder(n->right);
	}
}
void postorder(node n) {
	if (n != NULL)
	{
		postorder(n->left);
		postorder(n->right);
		printf("%c", n->data);
	}
}
void deleteTree(node n) {
	if (n != NULL) {
		deleteTree(n->left);
		deleteTree(n->right);
		free(n);
	}
}
int precedence(char a, char b) { // 0 == same, 1 == higher, -1 == lower
								 //same
	if (a == '+' && b == '-') {
		return 0;
	}
	if (a == '+' && b == '+') {
		return 0;
	}
	if (a == '-' && b == '-') {
		return 0;
	}
	if (a == '-' && b == '+') {
		return 0;
	}
	if (a == '*' && b == '*') {
		return 0;
	}
	//lower
	if (a == '+' && b == '*') {
		return -1;
	}
	if (a == '-' && b == '*') {
		return -1;
	}
	//higher
	if (a == '*' && b == '-') {
		return 1;
	}
	if (a == '*' && b == '+') {
		return 1;
	}
}
int isOperator(char c) {
	if (c == '*') {
		return 1;
	}
	if (c == '+') {
		return 1;
	}
	if (c == '-') {
		return 1;
	}
	return 0;
}
int isOp(node n) {
	if (n->left != NULL && n->right != NULL) {
		return 0;
	}
	if (n->data == '*' || n->data == '+' || n->data == '-') {
		return 1;
	}
	return 0;
}