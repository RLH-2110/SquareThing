#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "argParse/args.h"
#include "argParse/flags.h"

#include "structs.h"
#include "print.h"
#include "squares.h"


bool draw_table = false;
bool all_squares = false;









int main(int argc, char* argv[]){

	get_args(argc,argv); /* get arguments. might unset draw_table */


	if ((argumentFlags & flags_n) == 0) /* if -n was not set*/
		draw_table = true;

	if ((argumentFlags & flags_a) != 0) /* if -a was set set*/
		all_squares = true;

	for (int i = 0; i < widthsC;i++)
		printf("%s ",widths[i]);
	puts("");
	for (int i = 0; i < heightsC;i++)
		printf("%s ",heights[i]);
	puts("");
	

	/* list of how column withds as numbers*/
	ushort* widthsN = malloc(widthsC*sizeof(ushort));

	/* list of how row heights as numbers*/
	ushort* heightsN = malloc(heightsC * sizeof(ushort));




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
	squareInfo* head;

	if (all_squares)
		head = find_all_squares(widthsN,heightsN);
	else
		head = find_squares(widthsN,heightsN);


	int squareSum = 0;

	squareInfo* current = head;
	while(current != NULL){
		printf("There are %d squares of size %d\n",current->count, current->size);
		squareSum += current->count;
		current = current->next;
	}


	printf("there is a total of %d squares!\n",squareSum);



	widthsC = 0;
	free(widths); widths = NULL;
	free(widthsN); widthsN = NULL;
	
	heightsC = 0;
	free(heights); heights = NULL;
	free(heightsN); heightsN = NULL;
	free_square(head);

	return 0;
}












