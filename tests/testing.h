#include "../ui/SdlUi.h"
#include <cassert>
#include <map>

#define TEST_ADD(name, func) tests.emplace(name, [](void) func)

std::map<const char*, void(*)(void)> tests;

void log(const char* msg);
void err(const char* msg);
void runTests(void) { for(auto test : tests) { printf("Testing %s...\n", test.first); fflush(stdout); test.second(); }}
