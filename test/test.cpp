
#include <iostream>
#include <string>
#include "../include/fn/monad.hpp"

int main(void)
{
	std::cout << "OK" << std::endl;
	auto tr = [](int x){
		if (x < 0)
			return fn::maybe<int>();
		else
			return fn::maybe<int>(x + 5);
	};
	std::cout << (fn::maybe<int>() >> tr).is_just() << std::endl;
	std::cout << (fn::maybe<int>(4) >> tr).is_just() << std::endl;
	std::cout << (fn::maybe<int>(-1) >> tr).is_just() << std::endl;
	return 0;
}