#include <iostream>

void format(const std::string& fmt) 
{
	std::cout << fmt << std::endl;
}

template <typename T, typename... Args>
void format(const std::string& fmt, T value, Args... args)
{
	auto pos = fmt.find("{}");
	if (pos == std::string::npos) 
		throw std::runtime_error("Extra arg");
	std::cout << fmt.substr(0, pos);
	std::cout << value;
	format(fmt.substr(pos+2), args...);
}

int
main() 
{
	format("Lecture {}: {} (Week {})", 9, "Templates", 5);
}
