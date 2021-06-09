#include <stdint.h>
#include "utils.h"

inline int64_t mod(int64_t x, int64_t y)
{
	return x - (x / y) * y;
}
