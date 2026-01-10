#include <iostream>
#include <utility>
#include <format>
#include <cmath>


using Zeros = std::pair<double, double>;
using Solution = std::pair<bool, Zeros>;

Solution
solveQuadratic(double a, double b, double c)
{
	Solution result = { false, {0.0, 0.0} };
	double delta = b * b - 4 * a * c;
	if (delta < 0) {
		return result;
	}

	result.first = true;
	result.second.first = (-b - sqrt(delta)) / (2 * a);
	result.second.second = (-b + sqrt(delta)) / (2 * a);

	return result;
}

int 
main() 
{
	double a, b, c;
	std::cout << "Enter a b c: ";
	std::cin >> a >> b >> c;

	auto ans = solveQuadratic(a, b, c);

	if (ans.first) {
		auto first = ans.second.first;
		auto second = ans.second.second;
		if (first == second) {
			std::cout << std::format("There is one solution: {}\n", first);
		} else {
			std::cout << std::format("There are two different solutions: {} and {}\n", first, second);
		}
	} else {
		std::cout << std::format("There is no solution for {}x^2 + {}x + {}", a, b, c)
			<< std::endl;
	}
}
