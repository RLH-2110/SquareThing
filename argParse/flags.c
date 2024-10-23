#include "../defines.h"
#include <stdint.h>

/* This file handles the command line flags */

uint32_t argumentFlags = 0; /* the flags that are set with the command line! */

/* list of how column withds */
char** widths = NULL;
int widthsC = 0; 

/* list of how row heights */
char** heights = NULL;
int heightsC = 0; 
