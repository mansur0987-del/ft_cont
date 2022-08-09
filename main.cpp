#include "vector.hpp"
#include <vector>
#include <iostream>


#ifndef NM
# define V "FT"
# define NM ft
#else
# define V "STD"
#endif

template <class T>
void	print_vector(NM::vector<T> v)
{
	typename NM::vector<T>::iterator	it = v.begin();
	typename NM::vector<T>::iterator	ite = v.end();

	typename NM::vector<T>::const_iterator	cit = v.begin();
	typename NM::vector<T>::const_iterator	cite = v.end();

	typename NM::vector<T>::reverse_iterator	rev = v.rbegin();
	typename NM::vector<T>::reverse_iterator	reve = v.rend();

	std::cout << "Vector Iterator date: ";
	for (; it != ite; ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	std::cout << "Vector Const Iterator date: ";
	for (; cit != cite; ++cit)
		std::cout << *cit << " ";
	std::cout << std::endl << std::endl;

	std::cout << "Vector Reverse Iterator date: " ;
	for (; rev != reve; ++rev)
		std::cout << *rev << " ";
	std::cout << std::endl << std::endl;
}

template <class T>
void	print_vector_const(const NM::vector<T> v)
{
	typename NM::vector<T>::const_iterator	cit = v.begin();
	typename NM::vector<T>::const_iterator	cite = v.end();

	std::cout << "Vector Const Iterator date: ";
	for (; cit != cite; ++cit)
		std::cout << *cit << " ";
	std::cout << std::endl << std::endl;
}

template <class T>
void	print_params(NM::vector<T> &v)
{
	std::cout << "Vector empty: ";
	std::cout << v.empty() << std::endl;
	std::cout << "Vector size: ";
	std::cout << v.size() << std::endl;
	std::cout << "Vector max size: ";
	std::cout << v.max_size() << std::endl;
	std::cout << "Vector capacity: ";
	std::cout << v.capacity() << std::endl << std::endl  << std::endl;
}

template <class T>
void	print_params_const(const NM::vector<T> &v)
{
	std::cout << "Vector empty: ";
	std::cout << v.empty() << std::endl;
	std::cout << "Vector size: ";
	std::cout << v.size() << std::endl;
	std::cout << "Vector max size: ";
	std::cout << v.max_size() << std::endl;
	std::cout << "Vector capacity: ";
	std::cout << v.capacity() << std::endl << std::endl  << std::endl;
}

int	main()
{
	std::cout << "vector from " << V << std::endl;
	std::cout << "v: " << std::endl;
	NM::vector<int>	v;
	print_vector(v);
	print_params(v);

	std::cout << "v42: " << std::endl;
	NM::vector<int> v42(5, 42);
	print_vector(v42);
	print_params(v42);

	std::cout << "vchar: " << std::endl;
	NM::vector<char> vchar(5, 'a');
	print_vector(vchar);
	print_params(vchar);

	std::cout << "v_copy: " << std::endl;
	NM::vector<int> v_copy(v42);
	print_vector(v_copy);
	print_params(v_copy);

	std::cout << "v_const: " << std::endl;
	NM::vector<int>	const v_const(3, 7);
	print_vector_const(v_const);
	print_params_const(v_const);

	std::cout << "v_range: " << std::endl;
	NM::vector<int>	v_range(v42.begin() + 2, v42.end() - 2);
	print_vector(v_range);
	print_params(v_range);

	std::cout << "assign v: " << std::endl;
	v.assign(7, 50);
	print_vector(v);
	print_params(v);

	std::cout << "push_back v: " << std::endl;
	v.push_back(1);
	print_vector(v);
	print_params(v);

	std::cout << "front v: " << v.front() << std::endl;
	std::cout << "back v: " << v.back() << std::endl;
	std::cout << "at = 0 v: " << v.at(0) << std::endl;
	std::cout << "at = 1 v: " << v.at(1) << std::endl;
	std::cout << "at = 7 v: " << v.at(7) << std::endl << std::endl;

	std::cout << "assign range v: " << std::endl;
	v.assign(v42.begin() + 1, v42.end() - 1);
	print_vector(v);
	print_params(v);

	std::cout << "insert v42: " << std::endl;
	v42.insert(v42.begin() + 1, 99);
	print_vector(v42);
	print_params(v42);

	std::cout << "insert v42 range: " << std::endl;
	v42.insert(v42.begin() + 3, (size_t) 5, 77);
	print_vector(v42);
	print_params(v42);

	std::cout << "clear v42: " << std::endl;
	v42.clear();
	print_vector(v42);
	print_params(v42);



	return 0;
}
