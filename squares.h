#ifndef squaresH
#define squaresH

#include "structs.h"
#include "defines.h"

squareInfo* find_squares(const ushort *widthsN, const ushort *heightsN);
squareInfo* find_all_squares(const ushort *widthsN, const ushort *heightsN);
squareInfo* add_square(ushort size, squareInfo* head);
void free_square(squareInfo* current);

/* squaresH */
#endif