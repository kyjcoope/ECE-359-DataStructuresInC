// bib_gen.c

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

struct  article { //struct for articles
	char title[256] = "\0";
	char author[256] = "\0";
	char journal[256] = "\0";
	char volume[256] = "\0";
	char number[256] = "\0";
	char pages[256] = "\0";
	char year[256] = "\0";
	char publisher[256] = "\0";
};
struct  inproceedings { //struct for inproceedings
	char title[256] = "\0";
	char author[256] = "\0";
	char booktitle[256] = "\0";
	char pages[256] = "\0";
	char volume[256] = "\0";
	char year[256] = "\0";
	char organization[256] = "\0";
};
struct  misc { //struct for misc
	char title[256] = "\0";
	char author[256] = "\0";
	char note[256] = "\0";
	char year[256] = "\0";
	char howpublished[256] = "\0";
};
struct  book { //struct for book
	char title[256] = "\0";
	char author[256] = "\0";
	char year[256] = "\0";
	char publisher[256] = "\0";
};
struct  bib_lists { //struct for linked list
	struct article* Article;
	struct inproceedings* Inproceedings;
	struct misc* Misc;
	struct book* Book;
	int type_flag;
	struct bib_lists* nextNode;
};
typedef struct bib_lists *node; //function prototypes / typedef
typedef struct article* node_a; 
typedef struct book* node_b; 
typedef struct misc* node_m;
typedef struct inproceedings* node_i;
void printRecord(node current);
node deleteNode(node, char*);
node createNode();
node addNode(node);
void lookupPub(node , char*);
void lookupYear(node, char*);
void deleteList(node);

int main()
{
	int i,j,k,z, num,brace_flag = 0,start_up = 1,exit_flag = 1; //declarations
	char c,user_input[256];
	char temp[256],temp2[256],temp3[256];
	node bib_list = createNode();
	node  current;
	FILE* f_source;
	//open bib file
	if ((fopen_s(&f_source,"bib.txt", "r")) != 0) { //if read file doesn't exist print error and close program
		printf("Error: source file bib.txt does not exist.\n");
		return 0;
	}
	//parse file into linked list
	while ((c = fgetc(f_source)) != EOF) {

		if (c == '@') {
			i = 0;
			while ((c = fgetc(f_source)) != '{') {
				temp[i] = c;
				i++;
			}
			temp[i] = '\0';

			if (start_up) {
				current = bib_list;
				start_up = 0;
			}
			else {
				current = addNode(current);
			}

			while (1) {
				c = fgetc(f_source);
				if (c == '\n') {
					c = fgetc(f_source);
					if (c == '}') {
						break;
					}
					j = 0;
					c = fgetc(f_source);
					while ((c = fgetc(f_source)) != '=') {
						temp2[j] = c;
						j++;
					}
					temp2[j] = '\0';
					c = fgetc(f_source);
					brace_flag = 1;
					k = 0;
					while (brace_flag) {
						c = fgetc(f_source);
						if (c == '{') {
							brace_flag++;
						}
						else if (c == '}') {
							brace_flag--;
							if (brace_flag == 0) {
								break;
							}
						}
						
						temp3[k] = c;
						k++;
					}
					temp3[k] = '\0';
					if (!strcmp(temp, "article")) {
						current->type_flag = 1;
						if (!strcmp(temp2, "title")) {
							z = 0;
							while(temp3[z]!= '\0') {
								current->Article->title[z] = temp3[z];
								z++;
							}
							current->Article->title[z] = '\0';
						}
						else if (!strcmp(temp2, "author")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->author[z] = temp3[z];
								z++;
							}
							current->Article->author[z] = '\0';
						}
						else if (!strcmp(temp2, "journal")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->journal[z] = temp3[z];
								z++;
							}
							current->Article->journal[z] = '\0';
						}
						else if (!strcmp(temp2, "volume")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->volume[z] = temp3[z];
								z++;
							}
							current->Article->volume[z] = '\0';
						}
						else if (!strcmp(temp2, "number")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->number[z] = temp3[z];
								z++;
							}
							current->Article->number[z] = '\0';
						}
						else if (!strcmp(temp2, "pages")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->pages[z] = temp3[z];
								z++;
							}
							current->Article->pages[z] = '\0';
						}
						else if (!strcmp(temp2, "year")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->year[z] = temp3[z];
								z++;
							}
							current->Article->year[z] = '\0';
						}
						else if (!strcmp(temp2, "publisher")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Article->publisher[z] = temp3[z];
								z++;
							}
							current->Article->publisher[z] = '\0';
						}
					}
					else if (!strcmp(temp, "inproceedings")) {
						current->type_flag = 2;
						if (!strcmp(temp2, "title")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->title[z] = temp3[z];
								z++;
							}
							current->Inproceedings->title[z] = '\0';
						}
						else if (!strcmp(temp2, "author")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->author[z] = temp3[z];
								z++;
							}
							current->Inproceedings->author[z] = '\0';
						}
						else if (!strcmp(temp2, "volume")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->volume[z] = temp3[z];
								z++;
							}
							current->Inproceedings->volume[z] = '\0';
						}
						else if (!strcmp(temp2, "pages")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->pages[z] = temp3[z];
								z++;
							}
							current->Inproceedings->pages[z] = '\0';
						}
						else if (!strcmp(temp2, "year")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->year[z] = temp3[z];
								z++;
							}
							current->Inproceedings->year[z] = '\0';
						}
						else if (!strcmp(temp2, "organization")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->organization[z] = temp3[z];
								z++;
							}
							current->Inproceedings->organization[z] = '\0';
						}
						else if (!strcmp(temp2, "booktitle")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Inproceedings->booktitle[z] = temp3[z];
								z++;
							}
							current->Inproceedings->booktitle[z] = '\0';
						}
					}
					else if (!strcmp(temp, "misc")) {
						current->type_flag = 3;
						if (!strcmp(temp2, "title")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Misc->title[z] = temp3[z];
								z++;
							}
							current->Misc->title[z] = '\0';
						}
						else if (!strcmp(temp2, "author")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Misc->author[z] = temp3[z];
								z++;
							}
							current->Misc->author[z] = '\0';
						}
						else if (!strcmp(temp2, "note")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Misc->note[z] = temp3[z];
								z++;
							}
							current->Misc->note[z] = '\0';
						}
						else if (!strcmp(temp2, "year")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Misc->year[z] = temp3[z];
								z++;
							}
							current->Misc->year[z] = '\0';
						}
						else if (!strcmp(temp2, "howpublished")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Misc->howpublished[z] = temp3[z];
								z++;
							}
							current->Misc->howpublished[z] = '\0';
						}
					}
					else if (!strcmp(temp, "book")) {
						current->type_flag = 4;
						if (!strcmp(temp2, "title")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Book->title[z] = temp3[z];
								z++;
							}
							current->Book->title[z] = '\0';
						}
						else if (!strcmp(temp2, "author")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Book->author[z] = temp3[z];
								z++;
							}
							current->Book->author[z] = '\0';
						}
						else if (!strcmp(temp2, "year")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Book->year[z] = temp3[z];
								z++;
							}
							current->Book->year[z] = '\0';
						}
						else if (!strcmp(temp2, "publisher")) {
							z = 0;
							while (temp3[z] != '\0') {
								current->Book->publisher[z] = temp2[3];
								z++;
							}
							current->Book->publisher[z] = '\0';
						}
					}

				}
			}
		}
	}	\
	while (exit_flag) { //user interface
		printf("Commands: search, quit, show all, delete.\n"); //show commands
		gets_s(user_input); //get user input
		if (!strcmp(user_input, "search")) { //search command
			printf("Search Options: year, publisher.\n");
			gets_s(user_input);
			if (!strcmp(user_input, "publisher")) {
				printf("Enter publisher: \n");
				gets_s(user_input);
				lookupPub(bib_list, user_input);
			}
			if (!strcmp(user_input, "year")) {
				printf("Enter year: \n");
				gets_s(user_input);
				lookupYear(bib_list,user_input);
			}

		}
		else if (!strcmp(user_input, "quit")) { //quit command
			exit_flag = 0;
		}
		else if (!strcmp(user_input, "show all")) { //show all command
			current = bib_list;
			while (current) {
				printRecord(current);
				current = current->nextNode;
			}
		}
		else if (!strcmp(user_input, "delete")) { //delete command
			printf("Enter title to delete: \n");
			gets_s(user_input);
			bib_list = deleteNode(bib_list, user_input);
		}
	}
	deleteList(bib_list);
	return 0;
}
void printRecord(node current) { //print signle record
	printf("\n");
	if (current->type_flag == 1) {
		printf("Article\n");

		if (current->Article->title[0] == -51) {
			printf("Title: \n");
		}
		else {
			printf("Title: %s\n", current->Article->title);
		}

		if (current->Article->author[0] == -51) {
			printf("Author: \n");
		}
		else {
			printf("Author: %s\n", current->Article->author);
		}

		if (current->Article->journal[0] == -51) {
			printf("Journal: \n");
		}

		else {
			printf("Journal: %s\n", current->Article->journal);
		}

		if (current->Article->volume[0] == -51) {
			printf("Volume: \n");
		}
		else {
			printf("Volume: %s\n", current->Article->volume);
		}
		if (current->Article->number[0] == -51) {
			printf("Number: \n");
		}
		else {
			printf("Number: %s\n", current->Article->number);
		}
		if (current->Article->pages[0] == -51) {
			printf("Pages: \n");
		}
		else {
			printf("Pages: %s\n", current->Article->pages);
		}
		if (current->Article->year[0] == -51) {
			printf("Year: \n");
		}
		else {
			printf("Year: %s\n", current->Article->year);
		}
		if (current->Article->publisher[0] == -51) {
			printf("Publisher: \n");
		}
		else {
			printf("Publisher: %s\n", current->Article->publisher);
		}
	}
	else if (current->type_flag == 2) {
		printf("Inproceeding\n");

		if (current->Inproceedings->title[0] == -51) {
			printf("Title: \n");
		}
		else {
			printf("Title: %s\n", current->Inproceedings->title);
		}

		if (current->Inproceedings->author[0] == -51) {
			printf("Author: \n");
		}
		else {
			printf("Author: %s\n", current->Inproceedings->author);
		}

		if (current->Inproceedings->booktitle[0] == -51) {
			printf("Booktitle: \n");
		}
		else {
			printf("Booktitle: %s\n", current->Inproceedings->booktitle);
		}

		if (current->Inproceedings->volume[0] == -51) {
			printf("Volume: \n");
		}
		else {
			printf("Volume: %s\n", current->Inproceedings->volume);
		}

		if (current->Inproceedings->pages[0] == -51) {
			printf("Pages: \n");
		}
		else {
			printf("Pages: %s\n", current->Inproceedings->pages);
		}

		if (current->Inproceedings->year[0] == -51) {
			printf("Year: \n");
		}
		else {
			printf("Year: %s\n", current->Inproceedings->year);
		}

		if (current->Inproceedings->organization[0] == -51) {
			printf("Organization: \n");
		}
		else {
			printf("Organization: %s\n", current->Inproceedings->organization);
		}
	}
	else if (current->type_flag == 3) {
		printf("Misc\n");

		if (current->Misc->title[0] == -51) {
			printf("Title: \n");
		}
		else {
			printf("Title: %s\n", current->Misc->title);
		}
		if (current->Misc->author[0] == -51) {
			printf("Author: \n");
		}
		else {
			printf("Author: %s\n", current->Misc->author);
		}

		if (current->Misc->note[0] == -51) {
			printf("Note: \n");
		}
		else {
			printf("Note: %s\n", current->Misc->note);
		}

		if (current->Misc->year[0] == -51) {
			printf("Year: \n");
		}
		else {
			printf("Year: %s\n", current->Misc->year);
		}

		if (current->Misc->howpublished[0] == -51) {
			printf("Howpublished: \n");
		}
		else {
			printf("Howpublished: %s\n", current->Misc->howpublished);
		}
	}
	else if (current->type_flag == 4) {
		printf("Book\n");

		if (current->Book->title[0] == -51) {
			printf("Title: \n");
		}
		else {
			printf("Title: %s\n", current->Book->title);
		}
		if (current->Book->author[0] == -51) {
			printf("Author: \n");
		}
		else {
			printf("Author: %s\n", current->Book->author);
		}
		if (current->Book->year[0] == -51) {
			printf("Year: \n");
		}
		else {
			printf("Year: %s\n", current->Book->year);
		}
		if (current->Book->publisher[0] == -51) {
			printf("Publisher: \n");
		}
		else {
			printf("Publisher: %s\n", current->Book->publisher);
		}
	}
	printf("\n\n");
}
node createNode() { //create new linked list node
	node temp1;
	node_a temp2;
	node_b temp3;
	node_m temp4;
	node_i temp5;
	temp1 = (node)malloc(sizeof(struct bib_lists));
	temp2 = (node_a)malloc(sizeof(struct article));
	temp3 = (node_b)malloc(sizeof(struct book));
	temp4 = (node_m)malloc(sizeof(struct misc));
	temp5 = (node_i)malloc(sizeof(struct inproceedings));
	temp1->Article = temp2;
	temp1->Book = temp3;
	temp1->Misc = temp4;
	temp1->Inproceedings = temp5;

	temp1->nextNode = NULL;
	return temp1;
};
node addNode(node current) { //add node to linked list
	node temp;
	temp = createNode();
	current->nextNode = temp;
	return temp;
};
void deleteList(node head) {//delete linked list
	node current = head;
	node next;
	while (current != NULL)
	{
		next = current->nextNode;
		free(current->Article);
		free(current->Book);
		free(current->Inproceedings);
		free(current->Misc);
		free(current);
		current = next;
	}
	head = NULL;
}
node deleteNode(node head,char* arry) {//delete single link list node
	node current = head;
	node prev = head;
	node temp;
	int found_flag = 0;
	while (current != NULL) {
		if (!strcmp(current->Article->title, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Inproceedings->title, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Misc->title, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Book->title, arry)) {
			found_flag = 1;
			}
		if (found_flag) {
			if (current == head) {
				temp = current->nextNode;
				free(current->Article);
				current->Article = NULL;
				free(current->Book);
				current->Book = NULL;
				free(current->Inproceedings);
				current->Inproceedings = NULL;
				free(current->Misc);
				current->Misc = NULL;
				free(current);
				current = NULL;
				return temp;
			}
			else {
				prev->nextNode = current->nextNode;
				temp = current->nextNode;
				free(current->Article);
				current->Article = NULL;
				free(current->Book);
				current->Book = NULL;
				free(current->Inproceedings);
				current->Inproceedings = NULL;
				free(current->Misc);
				current->Misc = NULL;
				free(current);
				current = NULL;
				current = temp;
				return head;
			}
		}
		prev = current;
		current = current->nextNode;
	}
}
void lookupYear(node head, char* arry) { //lookup year
	node current = head;
	int found_flag = 0;
	while (current != NULL) {
		if (!strcmp(current->Article->year, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Inproceedings->year, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Misc->year, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Book->year, arry)) {
			found_flag = 1;
		}

		if (found_flag) {
			printRecord(current);
			found_flag = 0;
		}
		current = current->nextNode;
	}
}
void lookupPub(node head, char* arry) { //lookup publisher
	node current = head;
	int found_flag = 0;
	while (current != NULL) {
		if (!strcmp(current->Article->publisher, arry)) {
			found_flag = 1;
		}
		else if (!strcmp(current->Book->publisher, arry)) {
			found_flag = 1;
		}

		if (found_flag) {
			printRecord(current);
			found_flag = 0;
		}
		current = current->nextNode;
	}
}