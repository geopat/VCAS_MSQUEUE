#ifndef globals_h
#define globals_h

#define FALSE 0
#define TRUE 1
#define BOT INT_MIN
#define TBD INT_MAX
#define CASPTR(A, B, C)     __sync_bool_compare_and_swap((long *)A, (long)B, (long)C)
#endif