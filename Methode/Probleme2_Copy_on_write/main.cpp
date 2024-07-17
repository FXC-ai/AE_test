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
		// Copy_on_write(const std::shared_ptr<T>& ref_ptr);

		const T& operator*() const;
		T& operator*();

		// const T* operator->() const;
		T* operator->();

		std::shared_ptr<T> get() const;

};

template <class T>
void Copy_on_write<T>::create_new_allocation()
{
	T* tmp = this->_ptr.get();
	if (!(tmp == 0 || this->_ptr.unique()))
	{
		this->_ptr = std::shared_ptr<int>(new T(*tmp));
	}
}

template <class T>
Copy_on_write<T>::Copy_on_write (T* ptr) : _ptr(ptr) {}

template <class T>
const T& Copy_on_write<T>::operator*() const
{
	return *(this->_ptr);
}

template <class T>
T& Copy_on_write<T>::operator*()
{
	this->create_new_allocation();
	return *(this->_ptr);
}

template <class T>
T* Copy_on_write<T>::operator->()
{
	create_new_allocation();
	return this->_ptr.operator->();
}

template <class T>
std::shared_ptr<T> Copy_on_write<T>::get () const
{
	return this->_ptr;
}


int main()
{

	// Demo 1 : Construction d'un objet const copy_on_write

	int *test = new int(4);

	const Copy_on_write<int> obj_cp_on_wr(test);

	// std::cout << *obj_cp_on_wr << std::endl;

	// Demo 2 : Construction d'un objet copy_on_write

	int *test1 = new int(42);

	Copy_on_write<int> obj_cp_on_wr1(test1);

	// std::cout << *obj_cp_on_wr1 << std::endl;

	// Demo 3 :

	int *test2 = new int(24);

	Copy_on_write<int> obj_cp_on_wr2(test2);
	
	Copy_on_write<int> obj_cp_on_wr3(obj_cp_on_wr2);


	std::cout << obj_cp_on_wr2.get() << std::endl;
	std::cout << obj_cp_on_wr3.get() << std::endl;

	*obj_cp_on_wr3 = 42;

	std::cout << obj_cp_on_wr2.get() << std::endl;
	std::cout << obj_cp_on_wr3.get() << std::endl;



	

	// std::shared_ptr<int> test(new int(42));

	// std::cout << test.unique() << std::endl;


	// std::shared_ptr<int> test1;

	// test1=test;

	// std::shared_ptr<int> test2;

	// test2=test;

	// std::cout << test << " " << *test << std::endl;
	// std::cout << "test1.get() = " << test1.get() << " " << *test1 << std::endl;
	// std::cout << test.use_count() << std::endl;
	// std::cout << test1.use_count() << std::endl;
	// std::cout << test1.unique() << std::endl;


	return 1;	
}
