#include <iostream>
#include <string>


int main()
{
	std::string x("Hello");

	std::string &y = x;

	std::cout << &x << " " << &y << std::endl;

	y = "sspoipoi";

	std::cout << x << " " << y << std::endl;


	return 1;	
}

// y += ", World!";