#include "unity.h"
#include "unity_fixture.h"
#include "fff.h"
#include "fake_access.h"

TEST_GROUP(FAKE_ACCESS);

TEST_SETUP(FAKE_ACCESS)
{
}

TEST_TEAR_DOWN(FAKE_ACCESS)
{
}

TEST(FAKE_ACCESS, test1)
{
  TEST_ASSERT_EQUAL_INT(0, 0);
}

TEST(FAKE_ACCESS, test2)
{
  TEST_ASSERT_EQUAL_INT(0, 1);
}
