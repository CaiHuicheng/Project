/*
 * libc/ctype/islower.c
 */

#include <ctype.h>

/*
 * Checks if a byte is lower case
 */
int islower(int c)
{
	return (c == -1 ? 0 : (((const char *)__const_ctype + 1)[(unsigned char)c] & _L));
}
