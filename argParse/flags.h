#ifndef flagsH
#define flagsH

#include <stdint.h>

/* This file handles the command line flags */

/* View Defines.h section 'Flags' */
extern uint32_t argumentFlags; /* the flags that are set with the command line! */

/* list of how column withds */
extern char** widths;
extern int widthsC; 

/* list of how row heights */
extern char** heights;
extern int heightsC; 

#endif

