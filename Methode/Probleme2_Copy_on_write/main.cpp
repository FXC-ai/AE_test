#include <iostream>
#include <string>

template <class T>
class Copy_on_write
{

	private :
		std::shared_ptr<T> ptr;

	public :
		Copy_on_write(T* t);
		Copy_on_write(const std::shared_ptr& ref_ptr);

		const T& operator*() const;
		T& operator*();

		const T* operator->() const;
		T* operator->();

};

int main()
{

	std::shared_ptr<int> test(new int(42));

	// std::cout << test << " " << *test << std::endl;


	std::shared_ptr<int> test1;

	test1=test;

	std::cout << test << " " << *test << std::endl;
	std::cout << test1.get() << " " << *test1 << std::endl;
	std::cout << test.use_count() << std::endl;
	std::cout << test1.use_count() << std::endl;
	std::cout << test1.unique() << std::endl;


	// test = new int(42);

	// std::string x("Hello");

	// std::string &y = x;

	// std::cout << &x << " " << &y << std::endl;

	// y = "sspoipoi";

	// std::cout << x << " " << y << std::endl;


	return 1;	
}

// y += ", World!";