#include "unity_fixture.h"

void runAllTests(void)
{
  RUN_TEST_GROUP(FAKE_ACCESS);
}

static const char* command[] = {"", "-v", "-r", "1"};
#define LEN_COMMAND (sizeof(command) / sizeof(char*))

int main()
{
  return UnityMain(LEN_COMMAND, command, runAllTests);
}
