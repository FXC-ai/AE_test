#ifndef COPY_ON_WRITE_HPP
# define COPY_ON_WRITE_HPP

class Copy_on_write
{

	private :
		std::string datas;

	public :
		Copy_on_write();
		Copy_on_write& operator=(Copy_on_write const &rhs);
		Copy_on_write(Copy_on_write const &src);
		~Copy_on_write();

		std::string getDatas() const;
		void setDatas(std::string datas);

}

#endif