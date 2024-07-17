#pragma once
#ifndef COPY_ON_WRITE_HPP
# define COPY_ON_WRITE_HPP



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

#endif

