
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"
#include "../include/fn/fn.hpp"

using namespace fn;

int main(void)
{
	std::cout << "OK" << std::endl;

	/*std::cout << std::endl;
	{
		auto tr = [](int x) -> fn::Maybe<int> {
			if (x >= 0)
				return x + 5;
			else
				return Nothing;
		};
		std::cout << isJust(Nothing >> tr) << std::endl;
		std::cout << isJust(Just(4) >> tr) << std::endl;
		std::cout << isJust(Just(-1) >> tr) << std::endl;
	}

	std::cout << std::endl;
	{
		auto tr = [](int x) {
			return x + 5;
		};
		std::cout << isJust(fmap(tr, Nothing)) << std::endl;
		std::cout << isJust(fmap(tr, Just(4))) << std::endl;
		std::cout << isJust(fmap(tr, Just(-1))) << std::endl;
	}

	std::cout << std::endl;*/

	auto a = fn::cog::decompose([](int a, float b) { return a + b + 2; });
	auto b = a(1);
	std::cout << b(2.5) << std::endl;
	std::cout << fn::cog::decompose(3) << std::endl;
	return 0;
}