#include <stdlib.h>
#include <string.h>
#include "random_fake_access.h"

static volatile uint8_t FAKE_PHYSICAL_MEM[TOTAL_SIZE];
static volatile uint32_t FAKE_PHYSICAL_PAGE_COUNT = 0;
fakeBst_t* g_bst_root = NULL;

static int fakeBstWrite32(fakeBst_t* fake_bst, uint32_t address, uint32_t wdata);
static int fakeBstRead32(fakeBst_t* fake_bst, uint32_t address, uint32_t* rdata);
static fakeBst_t* fakeBstInsert(fakeBst_t* fake_bst, uint32_t address);
static fakeBst_t* fakeBstSearch(fakeBst_t* fake_bst, uint32_t pagen);

static int fakeBstWrite32(fakeBst_t* fake_bst, uint32_t address, uint32_t wdata)
{
  fakeBst_t* node = fake_bst->search_(fake_bst, address / PAGE_NUM);
  if (NULL == node)
  {
    node = fakeBstInsert(fake_bst, address);
    node = fake_bst->search_(fake_bst, address / PAGE_NUM);
    node->fake_mem_offset = ++FAKE_PHYSICAL_PAGE_COUNT;
  }

  node->tlb->tag_ = address % PAGE_NUM;
  // printf("%d>>%8x %8x, %8x\n", node->fake_mem_offset, address, node->tlb->pagen_, node->tlb->tag_);
  // printf("ACCESS: %8x\n", node->fake_mem_offset * PAGE_NUM + node->tlb->tag_);

  if (0 == (node->tlb->tag_ % 4))
  {
    *((uint32_t*)&FAKE_PHYSICAL_MEM[node->fake_mem_offset * PAGE_NUM + node->tlb->tag_]) = wdata;
  }
  else
  {
    // call fakeBstWrite8
  }

  return 0;
}

static int fakeBstRead32(fakeBst_t* fake_bst, uint32_t address, uint32_t* rdata)
{
  fakeBst_t* node = fake_bst->search_(fake_bst, address / PAGE_NUM);
  if (NULL == node)
  {
    node = fakeBstInsert(fake_bst, address);
    node = fake_bst->search_(fake_bst, address / PAGE_NUM);
    node->fake_mem_offset = FAKE_PHYSICAL_PAGE_COUNT++;
  }
  node->tlb->tag_ = address % PAGE_NUM;
  // printf("%d>>%8x %8x, %8x\n", node->fake_mem_offset, address, node->tlb->pagen_, node->tlb->tag_);
  // printf("ACCESS: %8x\n", node->fake_mem_offset * PAGE_NUM + node->tlb->tag_);

  if (NULL == rdata)
  {
    return -1;
  }
  if (NULL == node)
  {
    *rdata = 0;
  }
  else if (0 == (node->tlb->tag_ % 4))
  {
    *rdata = *((uint32_t*)&FAKE_PHYSICAL_MEM[node->fake_mem_offset * PAGE_NUM + node->tlb->tag_]);
  }
  else
  {
  }

  return 0;
}

static fakeBst_t* fakeBstInsert(fakeBst_t* fake_bst, uint32_t address)
{
  uint32_t pagen = address / PAGE_NUM;
  if (NULL == fake_bst)
  {
    return addFakeBst(address);
  }
  else if (pagen > fake_bst->tlb->pagen_)
  {
    fakeBst_t* temp = fakeBstInsert(fake_bst->right_, address);
    if (temp != fake_bst->right_)
    {
      fake_bst->right_ = temp;
    }
  }
  else if (pagen < fake_bst->tlb->pagen_)
  {
    fakeBst_t* temp = fakeBstInsert(fake_bst->left_, address);
    if (temp != fake_bst->left_)
    {
      fake_bst->left_ = temp;
    }
  }
  else
  {
    return NULL;
  }

  return fake_bst;
}

static fakeBst_t* fakeBstSearch(fakeBst_t* fake_bst, uint32_t pagen)
{
  if ((fake_bst == NULL) || (fake_bst->tlb == NULL))
  {
    return NULL;
  }
  if (pagen == fake_bst->tlb->pagen_)
  {
    return fake_bst;
  }
  else if (pagen > fake_bst->tlb->pagen_)
  {
    return fakeBstSearch(fake_bst->right_, pagen);
  }
  else
  {
    return fakeBstSearch(fake_bst->left_, pagen);
  }

  return NULL;
}

fakeTlb_t* createTlb(uint32_t address)
{
  fakeTlb_t* fake_tlb = malloc(sizeof(fakeTlb_t));
  memset(fake_tlb, 0, sizeof(fakeTlb_t));

  fake_tlb->pagen_ = address / PAGE_NUM;
  fake_tlb->tag_ = address % PAGE_NUM;

  return fake_tlb;
}

fakeBst_t* addFakeBst(uint32_t address)
{
  fakeBst_t* fake_bst = malloc(sizeof(fakeBst_t));
  memset(fake_bst, 0, sizeof(fakeBst_t));
  fake_bst->insert_ = fakeBstInsert;
  fake_bst->write32_ = fakeBstWrite32;
  fake_bst->read32_ = fakeBstRead32;
  fake_bst->search_ = fakeBstSearch;

  fake_bst->tlb = createTlb(address);

  return fake_bst;
}

fakeBst_t* createFakeBst(void)
{
  if (g_bst_root == NULL)
    return addFakeBst(0);
  else
    return g_bst_root;
}

void resetFakeBst(fakeBst_t* fake_bst)
{
}

void resetFakePhysicalMemory(void)
{
  memset((void*)&FAKE_PHYSICAL_MEM[0], 0, sizeof(FAKE_PHYSICAL_MEM));
}
