
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"
#include "../include/fn/fn.hpp"

using namespace fn;

int main(void)
{
	auto r = fmap(l_(int x, int y, int z)(x + y + 2 * z), Just(1)) * Just(2) * Just(11);
	if (isJust(r)) {
		std::cout << fromJust(r) << std::endl;
	} else  {
		std::cout << "Nothing" << std::endl;
	}
	return 0;
}