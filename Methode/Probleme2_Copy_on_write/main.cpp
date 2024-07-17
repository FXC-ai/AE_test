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
		T& get() const;
		void set(T value);
		
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
T& Copy_on_write<T>::get () const
{
	return *(this->_ptr);
}

template <class T>
void Copy_on_write<T>::set(T value)
{
	this->create_new_allocation();
	*(this->_ptr) = value;
}

int main()
{

	int *test0 = new int(24);

	Copy_on_write<int> obj_cp_on_wr0(test0);
	
	Copy_on_write<int> obj_cp_on_wr1(obj_cp_on_wr0);

	std::cout << "Avant set()" << std::endl;
	std::cout << obj_cp_on_wr0.get() << " " << &obj_cp_on_wr0.get() << std::endl;
	std::cout << obj_cp_on_wr1.get() << " " << &obj_cp_on_wr1.get() << std::endl;

	obj_cp_on_wr1.set(42);

	std::cout << "Apres set()" << std::endl;
	std::cout << obj_cp_on_wr0.get() << " " << &obj_cp_on_wr0.get() << std::endl;
	std::cout << obj_cp_on_wr1.get() << " " << &obj_cp_on_wr1.get() << std::endl;

	return 1;	
}

