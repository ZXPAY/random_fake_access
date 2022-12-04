#include "unity.h"
#include "unity_fixture.h"
#include "fff.h"
#include "random_fake_access.h"

TEST_GROUP(RANDOM_FAKE_ACCESS);

TEST_SETUP(RANDOM_FAKE_ACCESS)
{
}

TEST_TEAR_DOWN(RANDOM_FAKE_ACCESS)
{
}

TEST(RANDOM_FAKE_ACCESS, test1)
{
  fakeBst_t* bst = createFakeBst();

  printf("\n");
  for (int i = 0; i < 32; i += 4)
  {
    uint32_t wdata = (uint32_t)rand();
    uint32_t rdata = 0;
    int ret;
    ret = bst->write32_(bst, i, wdata);
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = bst->read32_(bst, i, &rdata);
    TEST_ASSERT_EQUAL_INT(0, ret);

    printf("%2x, %8x, %8x\n", i, wdata, rdata);
    TEST_ASSERT_EQUAL_HEX32(wdata, rdata);
  }
}

TEST(RANDOM_FAKE_ACCESS, test2)
{
  fakeBst_t* bst = createFakeBst();
  printf("\n");
  for (int i = 0; i < 32; i += 4)
  {
    uint32_t rdata = 0;
    int ret = bst->read32_(bst, i, &rdata);
    TEST_ASSERT_EQUAL_INT(0, ret);

    printf("%2x, %8x\n", i, rdata);
  }

}
