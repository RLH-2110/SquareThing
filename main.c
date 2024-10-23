#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "argParse/args.h"
#include "argParse/flags.h"

bool draw_table = false;

void put(const int chr);
void print_full(int count, ushort *sizeX);
void print_empty(int count, ushort *sizeX);


typedef struct squareInfo
{
	ushort size;
	ushort count;
	struct squareInfo *next;
} squareInfo;


squareInfo* find_squares(const ushort *widthsN, const ushort *heightsN);
void add_square(ushort size, squareInfo* head);
void free_square(squareInfo* current);

int main(int argc, char* argv[]){

	get_args(argc,argv); /* get arguments. might unset draw_table */


	if ((argumentFlags & flags_n) == 0) /* if -n was not set*/
		draw_table = true;


	for (int i = 0; i < widthsC;i++)
		printf("%s ",widths[i]);
	puts("");
	for (int i = 0; i < heightsC;i++)
		printf("%s ",heights[i]);
	puts("");
	

	/* list of how column withds as numbers*/
	ushort* widthsN = malloc(widthsC);

	/* list of how row heights as numbers*/
	ushort* heightsN = malloc(heightsC);




	for (int i = 0; i < widthsC;i++)
		widthsN[i] = (ushort)atoi(widths[i]); /* bounds checking was during user input.*/
	
	for (int i = 0; i < heightsC;i++)
		heightsN[i] = (ushort)atoi(heights[i]); /* bounds checking was during user input.*/





	if (draw_table){

		for (int heightI = 0; heightI < heightsC;heightI++){

			/*if (heightsN[heightI] == ) geht hier njed. mach zählen anders*/

			/* also, make the check for printing outside of the print function.*/ 

			print_full(widthsC,widthsN);

			for (int heightC = heightsN[heightI]; heightC > 0; heightC--)
				print_empty(widthsC,widthsN);				
		}
		print_full(widthsC,widthsN);

	}
	
	/* gonna let the OS clean this one up for now*/
	squareInfo* head = find_squares(widthsN,heightsN);

	squareInfo* current = head;
	while(current != NULL){
		printf("There are %d squares of size %d\n",current->count, current->size);
		current = current->next;
	}



	free(widths); widths = NULL;
	free(widthsN); widthsN = NULL;
	free(heights); heights = NULL;
	free(heightsN); heightsN = NULL;
	free_square(head);

	return 0;
}




squareInfo* find_squares(const ushort *widthsN, const ushort *heightsN){

	squareInfo* head = NULL;

	for (int widthsI = 0; widthsI < widthsC; widthsI++){
		for (int heightI = 0; heightI < heightsC; heightI++){
			if (widthsN[widthsI] == heightsN[heightI])
				add_square(widthsN[widthsI],head);
		}
	}

}


void free_square(squareInfo* current){
	squareInfo* child = NULL;

	while (true){
		if (current == NULL)
			return;

		child = current->next;
		free(current);

		current = child;
	}
}

void add_square(ushort size, squareInfo* head){

	if (head == NULL){
		head = malloc(sizeof(squareInfo));

		if (head  == NULL){
			puts("MEMORY LOW!");
			exit(-1);
		}

		head->size = size;
		head->count = 1;
		head->next = NULL;
	}

	squareInfo* current = head;

	while(true){

		if (current->size == size){
			current->count++;
			break;
		}
		
		if (current->next == NULL){
			current->next = malloc(sizeof(squareInfo));

			if (current->next  == NULL){
				puts("MEMORY LOW!");
				exit(-1);
			}

			current = current->next;
			current->size = size;
			current->count = 0;
			current->next = NULL;
			break;
		}
		
		current = current->next;
	}

}


void print_full(int count, ushort *sizeX){

	putc('#',stdout);

	for (int xi = 0; xi < count;xi++){
		for (int xc = sizeX[xi]; xc > 0; xc--){
			putc('-',stdout);
		}
		putc('#',stdout);
	}

	putc('\n',stdout);
}


void print_empty(int count, ushort *sizeX){
	
	putc('|',stdout);

	for (int xi = 0; xi < count;xi++){
		for (int xc = sizeX[xi]; xc > 0; xc--){
			putc(' ',stdout);
		}
		putc('|',stdout);
	}

	putc('\n',stdout);

}