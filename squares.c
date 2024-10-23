#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "defines.h"
#include "argParse/flags.h"


squareInfo* add_square(ushort size, squareInfo* head){

	if (head == NULL){
		head = malloc(sizeof(squareInfo));

		if (head  == NULL){
			puts("MEMORY LOW!");
			exit(-1);
		}

		head->size = size;
		head->count = 1;
		head->next = NULL;

		return head;
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
			current->count = 1;
			current->next = NULL;
			break;
		}
		
		current = current->next;
	}

	return head;
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



squareInfo* find_squares(const ushort *widthsN, const ushort *heightsN){

	squareInfo* head = NULL;

	for (int widthsI = 0; widthsI < widthsC; widthsI++){
		for (int heightI = 0; heightI < heightsC; heightI++){
			if (widthsN[widthsI] == heightsN[heightI])
				head = add_square(widthsN[widthsI],head);
		}
	}

	return head;

}



/* helper for find_all_squares 
	this is to avoid 4 times nesting
*/
squareInfo* find_all_squares_for_square(const ushort *widthsN, const ushort *heightsN, int widthsI, int heightI, squareInfo* head){

	int xsize = 0,ysize = 0;

	int ysum = 0;
	for (int y = heightI; y < heightsC; y++)
		ysum += heightsN[y];


	for (int x = widthsI; x < widthsC; x++){
		xsize += widthsN[x];

		if (xsize > ysum)
			break;

		ysize = 0;
		for (int y = heightI; y < heightsC; y++){
			ysize += heightsN[y];

			
			if (xsize == ysize){
				head = add_square(xsize,head);
				break;
			}

			if (xsize < ysize)
				break;


		}
	}

	return head;

}

squareInfo* find_all_squares(const ushort *widthsN, const ushort *heightsN){

	squareInfo* head = NULL;

	for (int widthsI = 0; widthsI < widthsC; widthsI++)
		for (int heightI = 0; heightI < heightsC; heightI++)
			head = find_all_squares_for_square(widthsN,heightsN,widthsI,heightI,head);	
	
	return head;
}

