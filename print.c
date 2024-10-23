#include <stdio.h>

#include "defines.h"

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