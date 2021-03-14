
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"

using namespace fn;

int main(void)
{
	std::cout << "OK" << std::endl;

	std::cout << std::endl;
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
		std::cout << isJust(fmap(Nothing, tr)) << std::endl;
		std::cout << isJust(fmap(Just(4), tr)) << std::endl;
		std::cout << isJust(fmap(Just(-1), tr)) << std::endl;
	}
	return 0;
}