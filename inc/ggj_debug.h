#ifndef GGJ_2023_GGJ_DEBUG_H
#define GGJ_2023_GGJ_DEBUG_H

// comment this to disable print debugging
// #define GGJ_DEBUGGING

#if defined(GGJ_DEBUGGING)

#define GGJ_PRINTF(fmt, ...) kprintf(fmt, ##__VA_ARGS__)

#else 

#define GGJ_PRINTF(fmt, ...)

#endif

#endif // GGJ_2023_GGJ_DEBUG_H