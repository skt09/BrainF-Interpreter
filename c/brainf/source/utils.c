#include <stdint.h>
#include <math.h>
#include "utils.h"

inline int64_t mod(int64_t x, int64_t y)
{
	return x - floor((float)x / (float)y) * y;
}
