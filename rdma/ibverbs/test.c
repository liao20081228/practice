

#define PRINTF(a, b, c) _PRINTF(b##%##c  ,a->b )

PRINTF(it,dev,s);
