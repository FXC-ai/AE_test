#include <iostream>
#include <string>

template <class T>
class Copy_on_write
{

	private :
		std::shared_ptr<T> _ptr;
		void create_new_allocation();

	public :
		Copy_on_write(T* ptr);
		Copy_on_write(const std::shared_ptr<T>& ref_ptr);

		const T& operator*() const;
		T& operator*();

		const T* operator->() const;
		T* operator->();

};

template <class T>
Copy_on_write<T>::Copy_on_write (T* ptr) : _ptr(ptr) {}

template <class T>
const T& Copy_on_write<T>::operator*() const
{
	return *(this->_ptr);

}

int main()
{

	int *test = new int(4);

	Copy_on_write<int> obj_cp_on_wr(test);

	std::cout << *obj_cp_on_wr << std::endl;


	// std::shared_ptr<int> test(new int(42));

	// std::cout << test << " " << *test << std::endl;
	// std::cout << test.unique() << std::endl;


	// std::shared_ptr<int> test1;

	// test1=test;

	// std::shared_ptr<int> test2;

	// test2=test;

	// std::cout << test << " " << *test << std::endl;
	// std::cout << test1.get() << " " << *test1 << std::endl;
	// std::cout << test.use_count() << std::endl;
	// std::cout << test1.use_count() << std::endl;
	// std::cout << test1.unique() << std::endl;


	return 1;	
}
