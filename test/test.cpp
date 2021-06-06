
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"
#include "../include/fn/fn.hpp"

using namespace fn;

static inline int test(size_t av, float bv, const std::string &str)
{
	auto a = l_(size_t a, float b, const std::string &s)(a + b + s.size());
	auto b = a(av);
	return b(bv)(str);
}

int main(void)
{
	Just(1);
	std::cout << fn::cog::decompose(test)(1)(2)("str") << std::endl;
	return 0;
}