#ifndef RANDOM_FAKE_ACCESS_H_
#define RANDOM_FAKE_ACCESS_H_

#include <stdint.h>
#include "fake_access_config.h"

typedef struct _fakeTlb_t
{
  uint32_t pagen_ : 18;
  uint32_t tag_ : 10;
  uint32_t ref_ : 1;
  uint32_t valid_ : 1;
  uint32_t dirty_ : 1;
} fakeTlb_t;

typedef struct _fakeBst_t fakeBst_t;
typedef struct _fakeBst_t
{
  fakeBst_t* left_;
  fakeBst_t* right_;
  int (*write32_)(fakeBst_t* fake_bst, uint32_t address, uint32_t wdata);
  int (*read32_)(fakeBst_t* fake_bst, uint32_t address, uint32_t* rdata);
  fakeBst_t* (*insert_)(fakeBst_t* fake_bst, uint32_t address);
  fakeBst_t* (*search_)(fakeBst_t* fake_bst, uint32_t pagen);
  fakeTlb_t* tlb;
  uint32_t fake_mem_offset;
} fakeBst_t;

fakeTlb_t* createTlb(uint32_t address);
fakeBst_t* addFakeBst(uint32_t address);
fakeBst_t* createFakeBst(void);
void resetFakeBst(fakeBst_t* fake_bst);
void resetPhysicalMemory(void);

#endif /* RANDOM_FAKE_ACCESS_H_ */
