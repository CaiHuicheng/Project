/*
 * libm/fabsf.c
 */

#include <math.h>

float fabsf(float x)
{
	u32_t ix;

	GET_FLOAT_WORD(ix, x);
	SET_FLOAT_WORD(x, ix & 0x7fffffff);
	return x;
}
