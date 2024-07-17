#ifndef COPY_ON_WRITE_HPP
# define COPY_ON_WRITE_HPP


template <clas T>
class Copy_on_write
{

	public :
		std::shared_ptr<T> ptr_read_only;

		Copy_on_write(T* t)

	private :
		std::shared_ptr<T> ptr_copy;





}

#endif

