
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"

int main(void)
{
	std::cout << "OK" << std::endl;
	auto tr = [](int x) -> fn::Maybe<int> {
		if (x >= 0)
			return x + 5;
		else
			return fn::Nothing_v;
	};
	std::cout << (fn::Nothing<int> >> tr).isJust() << std::endl;
	std::cout << (fn::Just(4) >> tr).isJust() << std::endl;
	std::cout << (fn::Just(-1) >> tr).isJust() << std::endl;
	return 0;
}