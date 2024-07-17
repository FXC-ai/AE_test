#include "Copy_on_write.hpp"
#include "Copy_on_write.tpp"

int main()
{

	// Demo 1 : Construction d'un objet const copy_on_write

	int *test = new int(4);

	const Copy_on_write<int> obj_cp_on_wr(test);

	std::cout << *obj_cp_on_wr << std::endl;

	// Demo 2 : Construction d'un objet copy_on_write

	int *test1 = new int(42);

	Copy_on_write<int> obj_cp_on_wr1(test1);

	std::cout << *obj_cp_on_wr1 << std::endl;

	// Demo 3 :

	int *test2 = new int(24);

	Copy_on_write<int> obj_cp_on_wr2(test2);
	
	Copy_on_write<int> obj_cp_on_wr3(obj_cp_on_wr2);


	std::cout << obj_cp_on_wr2.get() << std::endl;
	std::cout << obj_cp_on_wr3.get() << std::endl;

	*obj_cp_on_wr3 = 42;

	std::cout << obj_cp_on_wr2.get() << std::endl;
	std::cout << obj_cp_on_wr3.get() << std::endl;


	return 1;	
}
