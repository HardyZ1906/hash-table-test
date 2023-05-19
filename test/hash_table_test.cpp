#include "../include/level_hashing.hpp"

#include <vector>
#include <cassert>
#include <libpmemobj.h>

// using Key = uint64_t;
// using Value = uint64_t;
// using HashTable = level::LevelHashTable<Key, Value>;

FILE *out;

void PMemHardwareTest();

int main() {
  // out = fopen("debug", "w");
  out = stdout;

  PMemHardwareTest();
}

void PMemHardwareTest() {
  struct PMemHardwareTestRoot {
    PMEMoid array;
  };
  const char *filename = "array";
  const int size = 65536;
  PMEMobjpool *pop;
  PMemHardwareTestRoot *root;
  uint64_t *array;
  double total_time{0}, time_spent_on_persist{0};
  double begin, persist_begin;
  
  fprintf(out, "[TEST HARDWARE]\n");
  if ((pop = pmemobj_create(filename, POBJ_LAYOUT_NAME(uint64_t), PMEMOBJ_POOL_SIZE, 0666)) != nullptr) {
    fprintf(out, "memory pool created\n");
    root = reinterpret_cast<PMemHardwareTestRoot *>(pmemobj_direct(pmemobj_root(pop, sizeof(PMemHardwareTestRoot))));
    pmemobj_zalloc(pop, &root->array, sizeof(uint64_t) * size, 0);
    array = reinterpret_cast<uint64_t *>(pmemobj_direct(root->array));
  } else {
    if ((pop = pmemobj_open(filename, POBJ_LAYOUT_NAME(uint64_t))) == nullptr) {
      fprintf(out, "fatal: could neither create or open memory pool\n");
      exit(-1);
    }
    fprintf(out, "memory pool opened\n");
    root = reinterpret_cast<PMemHardwareTestRoot *>(pmemobj_direct(pmemobj_root(pop, sizeof(PMemHardwareTestRoot))));
    array = reinterpret_cast<uint64_t *>(pmemobj_direct(root->array));
  }

  // array = reinterpret_cast<uint64_t *>(pmemobj_direct(pmemobj_root(pop, sizeof(uint64_t) * size)));

  begin = gettime();
  for (uint64_t i = 0; i < size; i++) {
    int idx = MurmurHash2(&i, sizeof(uint64_t), HASH_SEED) % size;
    array[idx] = i;
    persist_begin = gettime();
    pmemobj_persist(pop, &array[idx], sizeof(uint64_t));
    time_spent_on_persist += gettime() - persist_begin;

    if (i % 2048 == 2047) {
      fprintf(out, "here!\n");
    }
  }
  total_time += gettime() - begin;

  fprintf(out, "Total:%lf\nPersist:%lf\n", total_time, time_spent_on_persist);
}
