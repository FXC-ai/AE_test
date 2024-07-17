#include "Copy_on_write.hpp"

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