#pragma once

#include <stdint.h>
#include <stddef.h>

#define CACHELINE_SIZE (64)
#define CLROUNDUP(p) (((uint64_t)(p) + CACHELINE_SIZE - 1) & ~(CACHELINE_SIZE - 1))
#define CLROUNDDOWN(p) (((uint64_t)(p)) & ~(CACHELINE_SIZE - 1))

#define HASH_SEED (302860120)

// #define PMEMOBJ_POOL_SIZE (8 * 1024 * 1024 * 1024)  // default memory pool size is 8GB

#define PMEMOBJ_POOL_SIZE (128 * 1024 * 1024)  // 128-MB memory pool, for debugging purposes only

auto malloc64(void **ptr, size_t size) -> int;

void fatal(const char *msg);

auto gettime() -> double;