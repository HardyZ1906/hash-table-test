#include "../include/util.h"
#include "../include/MurmurHash2.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

// #define __DEBUG_ONLY__
#ifdef __DEBUG_ONLY__
# define DEBUG_ONLY(foo) foo
#else
# define DEBUG_ONLY(foo)
#endif

auto malloc64(void **ptr, size_t size) -> int {
  size = CLROUNDUP(size);
  DEBUG_ONLY( printf("malloc: %d bytes\n", size); )
  int ret = posix_memalign(ptr, CACHELINE_SIZE, size);
  return ret;
}

void fatal(const char *msg) {
  printf("fatal error: %s\n", msg);
  exit(-1);
}

auto gettime() -> double {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
}