#ifndef definesH
#define definesH

#include <stdint.h>

#ifndef NULL
	#define NULL 0
#endif

#ifndef bool
	#define bool int
	#define true 1
	#define false 0
#endif


/*/#####\*/
/*|Helper|*/
/*\#####/*/

#define caller_free /* Caller Frees */

/*/#####\*/
/*|FLAGS|*/
/*\#####/*/

#define flags_h 0x01 /* 0b0000_0000_0000_0001 */
#define flags_n 0x02 /* 0b0000_0000_0000_0010 */
#define flags_x 0x04 /* 0b0000_0000_0000_0100 */
#define flags_y 0x08 /* 0b0000_0000_0000_1000 */
#define flags_a 0x10 /* 0b0000_0000_0001_0000 */

typedef uint16_t ushort;

/* definesH */
#endif 

