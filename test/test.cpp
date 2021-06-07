
#include <iostream>
#include <string>
#include "../include/fn/maybe.hpp"
#include "../include/fn/fn.hpp"

using namespace fn;

int main(void)
{
	auto r = l_(x, y, z)(x + y + 2 * z) % Just(1) * Just(2) * Just(11) >> l_(x)(x > 10 ? Just(x * 3) : Nothing);
	if (isJust(r)) {
		std::cout << fromJust(r) << std::endl;
	} else  {
		std::cout << "Nothing" << std::endl;
	}
	std::cout << l_()(4) << std::endl;
	//auto p4 = l_(x)(x + 4);
	//auto p4s = lcs_([], +4);
	auto p4s = ls_(+4);
	std::cout << p4s(3) << std::endl;
	std::cout << fromJust(Just(ls_(+3)) * Just(9)) << std::endl;
	std::cout << fromJust(pure(ls_(+3)) * Just(9)) << std::endl;
	std::cout << (ls_(+1) % pure(1)).get() << std::endl;
	std::cout << fromJust(pure(lps_(+)) * Just(3) * Just(5)) << std::endl;
	std::cout << fromJust(lps_(+) % Just(std::string("johntra")) * Just(std::string("volta"))) << std::endl;
	Maybe<int>(pure(3));
	std::cout << (pure(1) >> l_(x)(pure(x))).get() << std::endl;
	return 0;
}