#include <stdint.h>
#include "binary_search.h"

inline int64_t binary_search(const int64_t search, const uint64_t size, const int64_t *values)
{
    int64_t lower, upper, mid;

    lower = 0;
    upper = size;

    while (lower < upper)
    {
        mid = (lower + upper) / 2;

        if (search == values[mid])
        {
            return mid;
        }
        else if (search < values[mid])
        {
            upper = mid;
        }
        else
        {
            lower = mid + 1;
        }
    }

    return -1;
}