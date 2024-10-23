#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../defines.h"

#include "flags.h"


int fetch_flag_arg_count(int argc, char*argv[], int firstIndex); /* counts how many parameters there are after a flag */
void print_help(char* argv0); /* prints help screen */

/* arg = pointer to the raw text of the argument, THIS POINER MUST STAY ALIVE FOR THE ENTIRE RUNTIME!
   list = a pointer to a char** like inputFiles
   listC = pointer to the count of how many elements are in the list */
void append_arg(char *arg, char ***list, int *listC){

	if (!arg || !list){ /* if one param is NULL */
		fputs("ERROR: append_arg does not take NULL!\n",stdout);
		exit(1);
	} 



	if (*list == NULL){

		*list = malloc(sizeof(char*));
		if (*list == NULL){
			fputs("ERROR: append_arg is out of memory!\n",stdout);
			exit(1);
		}

		*listC = 1;
		*list[0] = arg; /* set the first element in the list to the argument pointer */	
	}else{
		*listC = *listC + 1;
		if (*listC == 0){
			/* If we got here, then that means there are so many parameters that we had an overflow. That sucks.*/
			fputs("ERROR: too many arguments for a flag! We had an overflow, what the fuck did you do to cause this?\n",stdout);
			exit(1);
		}

		*list = realloc(*list,*listC * sizeof(char*)); /* make space for one more pointer */


		if (*list == NULL){
			fputs("ERROR: append_arg is out of memory (realloc)!\n",stdout);
			exit(1);
		}


		(*list)[*listC - 1] = arg; /* set the last element to the argument pointer */



	}

}



void get_args(int argc, char*argv[]){
	

	int argI = 1; /* argument index, starts at first argument, ignores filename */
	int i;
	int result;

	for (;argI + 1 <= argc; argI++){ /* argc is a count, argI is an index thats why we need to increment argI */

		if (argv[argI][0] != '-') /* ignore if its not a flag */
			continue;

		switch (argv[argI][1]){

			case 'n':

				argumentFlags += flags_n;

				if (fetch_flag_arg_count(argc,argv,argI+1) != 0){
					fputs("Error: flag -n takes zero arguments!\n",stdout);
					print_help(argv[0]);
					exit(1);
				}

				break;

			case 'a':

				argumentFlags += flags_a;

				if (fetch_flag_arg_count(argc,argv,argI+1) != 0){
					fputs("Error: flag -a takes zero arguments!\n",stdout);
					print_help(argv[0]);
					exit(1);
				}

				break;

			case 'h':

				argumentFlags += flags_h;

				print_help(argv[0]);
				break;


			case 'x':

				if (argumentFlags & flags_x != 0){
					puts("please only use the -x flag once!");
					exit(1);
				}

				argumentFlags += flags_x;

				result = fetch_flag_arg_count(argc,argv,argI+1);

				if (result < 1){
					fputs("Error: flag -x needs at least one argument!\n",stdout);
					print_help(argv[0]);
					exit(1);
				}

				for (i = 1;i <= result; i++){ /* starts at 1, becuase argI + 0 == -i */
					if (strlen(argv[argI + i]) > 5){
						puts("Error: please do not provide a width greater than 9999!");
						exit(1);
					}


					append_arg(argv[argI + i],&widths,&widthsC);
				}
				break;

			case 'y':

				if (argumentFlags & flags_x != 0){
					puts("please only use the -y flag once!");
					exit(1);
				}

				argumentFlags += flags_y;

				result = fetch_flag_arg_count(argc,argv,argI+1);

				if (result < 1){
					fputs("Error: flag -w needs at least one argument!\n",stdout);
					print_help(argv[0]);
					exit(1);
				}

				for (i = 1;i <= result; i++){ /* starts at 1, becuase argI + 0 == -i */

					if (strlen(argv[argI + i]) > 5){
						puts("Error: please do not provide a height greater than 9999!");
						exit(1);
					}

					append_arg(argv[argI + i],&heights,&heightsC);
				}
				break;

			default:
				fprintf(stdout,"Error: unrecognized parameter: %s\n",argv[argI]);
				print_help(argv[0]);
				exit(1);
				
		}
	}


	if ((argumentFlags & flags_x) == 0){
		puts("Error: flag -x is required!");
		print_help(argv[0]);
		exit(1);
	}
	if ((argumentFlags & flags_y) == 0){
		puts("Error: flag -y is required!");
		print_help(argv[0]);
		exit(1);
	}

}

/* counts how many parameters there are after a flag */
int fetch_flag_arg_count(int argc, char*argv[], int firstIndex){
	
	int paramCount = 0;
	int i = firstIndex;


	if (firstIndex >= argc)	
		return 0;
	



	for (;i < argc && argv[i][0] != '-';i++)
		paramCount++;

	return paramCount;
}

void print_help(char* argv0){
	fprintf(stdout,"Usage: %s -x colum_widths... -y row_heights... [-nd]\n",argv0);
	fputs("  -x colum_widths...: at least one value for the width of the column(s)\n",stdout);
	fputs("  -y row_heights...: at least one value for the height of the row(s)\n",stdout);
	fputs("  -n: speciefies that the generated table should NOT be drawn\n",stdout);
	fputs("  -h: shows this help screen\n",stdout);
	fputs("  -a: shows all squares, even combined ones\n",stdout);
	
}


