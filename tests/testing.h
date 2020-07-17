#include "../ui/SdlUi.h"
#include <cassert>
#include <map>


static std::map<const char*, void(*)(void)> tests;

void TEST_ADD(const char* name, void(*test)(void)) {tests.emplace(name, test);}

void runTests(void) { for(auto test : tests) { printf("Testing %s...\n", test.first); fflush(stdout); test.second(); }}
