#include <iostream>

template <size_t N>
struct Factorial {
	static constexpr size_t value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
	static constexpr size_t value = 1;
};

int 
main(void)
{
	std::cout << Factorial<7>::value << std::endl;
	
	return 0;
}
