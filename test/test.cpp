
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"
#include "../include/fn/fn.hpp"

using namespace fn;

int test(size_t av, float bv, const std::string &str)
{
	auto a = fn::cog::decompose([](size_t a, float b, const std::string &s) { return a + static_cast<size_t>(b) + static_cast<size_t>(s.size()); });
	auto b = a(av);
	return b(bv)(str);
}

int main(void)
{
	std::cout << fn::cog::decompose(3) << std::endl;
	return 0;
}