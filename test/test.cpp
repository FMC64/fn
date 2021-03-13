
#include <iostream>
#include <string>
#include "../include/fn/monad.hpp"

int main(void)
{
	fn::maybe<int> t;

	std::cout << "OK" << std::endl;
	std::cout << (t >> [](int x){
		return fn::maybe<int>(x + 5);
	}).isJust() << std::endl;
	return 0;
}