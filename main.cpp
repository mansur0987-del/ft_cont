#include <string>
#include <deque>
#include <iostream>
#include <stdlib.h>

#ifndef NM
	#define V "FT"
	#define NM ft
	#include "./vector/vector.hpp"
	#include "./stack/stack.hpp"
	#include "./map/map.hpp"
	#include "./map/pair.hpp"
	#include "./map/TreeNode.hpp"
#else
	#define V "STD"
	#include <map>
	#include <stack>
	#include <vector>
#endif

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public NM::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename NM::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

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

void check_vector(void)
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

	std::cout << "insert v42 range +: " << std::endl;
	NM::vector<int> v2(7, 44);
	v42.insert(v42.begin() + 3, v2.begin() + 1, v2.end() - 1);
	print_vector(v42);
	print_params(v42);

	std::cout << "erase v42:" << std::endl;
	v42.erase(v42.begin() + 2);
	print_vector(v42);
	print_params(v42);

	std::cout << "erase v42 range:" << std::endl;
	v42.erase(v42.begin() + 2, v42.end() - 5);
	print_vector(v42);
	print_params(v42);

	std::cout << "pop_back v42:" << std::endl;
	v42.pop_back();
	print_vector(v42);
	print_params(v42);

	std::cout << "swap v42:" << std::endl;
	v42.swap(v2);
	print_vector(v42);
	print_params(v42);

	std::cout << "swap v42:" << std::endl;
	NM::swap(v2, v42);
	print_vector(v42);
	print_params(v42);

	std::cout << "resize_0 v42:" << std::endl;
	v42.resize(3, 111);
	print_vector(v42);
	print_params(v42);

	std::cout << "resize_1 v42:" << std::endl;
	v42.resize(10, 111);
	print_vector(v42);
	print_params(v42);

	std::cout << "clear v42: " << std::endl;
	v42.clear();
	print_vector(v42);
	print_params(v42);


	NM::vector<int> a(4, 5);
	print_vector(a);
	print_params(a);
	NM::vector<int> b(4, 5);
	print_vector(b);
	print_params(b);
	NM::vector<int> c(3, 5);
	print_vector(c);
	print_params(c);
	NM::vector<int> d(4, 10);
	print_vector(d);
	print_params(d);

	if (a == b)
		std::cout << "a == b" << std::endl;
	if (a == c)
		std::cout << "a == c" << std::endl;
	if (a == d)
		std::cout << "a == d" << std::endl;

	if (a != b)
		std::cout << "a != b" << std::endl;
	if (a != c)
		std::cout << "a != c" << std::endl;
	if (a != d)
		std::cout << "a != d" << std::endl;

	if (a < b)
		std::cout << "a < b" << std::endl;
	if (a < c)
		std::cout << "a < c" << std::endl;
	if (a < d)
		std::cout << "a < d" << std::endl;

	if (a <= b)
		std::cout << "a <= b" << std::endl;
	if (a <= c)
		std::cout << "a <= c" << std::endl;
	if (a <= d)
		std::cout << "a <= d" << std::endl;

	if (a > b)
		std::cout << "a > b" << std::endl;
	if (a > c)
		std::cout << "a > c" << std::endl;
	if (a > d)
		std::cout << "a > d" << std::endl;

	if (a >= b)
		std::cout << "a >= b" << std::endl;
	if (a >= c)
		std::cout << "a >= c" << std::endl;
	if (a >= d)
		std::cout << "a >= d" << std::endl;
}

void check_stack(void)
{
	std::cout << "Stack from " << V << std::endl;
	std::cout << "s: " << std::endl;
	NM::stack<int>	s;

	std::cout << "Stack empty: ";
	std::cout << s.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s.size() << std::endl << std::endl;

	s.push(10);
	std::cout << "push in stack s 10" << std::endl;
	std::cout << "Stack empty: ";
	std::cout << s.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s.size() << std::endl;
	std::cout << "Stack top: ";
	std::cout << s.top() << std::endl << std::endl;

	s.push(20);
	std::cout << "push in stack s 20" << std::endl;
	std::cout << "Stack empty: ";
	std::cout << s.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s.size() << std::endl;
	std::cout << "Stack top: ";
	std::cout << s.top() << std::endl << std::endl;

	NM::stack<int>	s1(s);
	std::cout << "s1 with copy constructor" << std::endl;
	std::cout << "Stack empty: ";
	std::cout << s1.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s1.size() << std::endl;
	std::cout << "Stack top: ";
	std::cout << s1.top() << std::endl << std::endl;

	NM::stack<int>	s2 = s;
	std::cout << "s2 with assigns" << std::endl;
	std::cout << "Stack empty: ";
	std::cout << s2.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s2.size() << std::endl;
	std::cout << "Stack top: ";
	std::cout << s2.top() << std::endl << std::endl;

	s2.pop();
	std::cout << "s2 pop" << std::endl;
	std::cout << "Stack empty: ";
	std::cout << s2.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s2.size() << std::endl;
	std::cout << "Stack top: ";
	std::cout << s2.top() << std::endl << std::endl;

	s2.pop();
	std::cout << "s2 pop" << std::endl;
	std::cout << "Stack empty: ";
	std::cout << s2.empty() << std::endl;
	std::cout << "Stack size: ";
	std::cout << s2.size() << std::endl;

}

void print_parametr_map(NM::map <int, int> &a)
{
	std::cout << "empty = " << a.empty() << std::endl;
	std::cout << "size = " << a.size() << std::endl;
	std::cout << "max_size = " << a.max_size() << std::endl;
	std::cout << std::endl;
}

void print_map(NM::map<int, int> &a)
{
	NM::map<int, int>::iterator it_a_begin = a.begin();
	NM::map<int, int>::iterator it_a_end = a.end();

	std::cout << "key   value" << std::endl;
	for (; it_a_begin != it_a_end; it_a_begin++)
	{
		std::cout << (*it_a_begin).first << "   =   " << (*it_a_begin).second << std::endl;
	}
}

void	check_map(void)
{
	std::cout << "map from " << V << std::endl;
	std::cout << "v: " << std::endl;
	typedef NM::pair <int,int>  value_type;
	value_type					p00;
	value_type					p01;
	value_type					p02;
	value_type					p03;
	value_type					p04;
	value_type					p05;
	value_type					p06;
	p00 = NM::make_pair(5, 55);
	p01 = NM::make_pair(10, 1010);
	p02 = NM::make_pair(2, 22);
	p03 = NM::make_pair(3, 33);
	p04 = NM::make_pair(7, 77);
	p05 = NM::make_pair(1, 11);
	p06 = NM::make_pair(-1, -11);

	NM::map<int, int>::iterator it_a_begin;
	NM::map<int, int>::iterator it_a_end;

	NM::map <int, int> a;
	print_parametr_map (a);

	a.insert(p00); // 5, 55
	a.insert(p01); // 10, 1010
	a.insert(p02); // 2, 22
	a.insert(p03); // 3, 33
	a.insert(p04); // 7, 77
	a.insert(p05); // 1, 11

	print_map(a);
	print_parametr_map (a);

	std::cout << "constr copy " << std::endl;
	NM::map <int, int> b(a);
	print_map(b);
	print_parametr_map (b);

	std::cout << "constr copy range " << std::endl;
	NM::map <int, int> c(a.begin(), a.end());
	print_map(c);
	print_parametr_map (c);

	std::cout << "at 3" << std::endl;
	std::cout << a.at(3) << std::endl << std::endl;

	std::cout << "[3]" << std::endl;
	std::cout << a[3] << std::endl << std::endl;

	std::cout << "insert key = -1, value = -11" << std::endl;
	c.insert(++(c.begin()), p06); // -1, -11
	print_map(c);
	print_parametr_map (c);

	std::cout << "after del key = 3" << std::endl;
	a.erase(3);
	print_map(a);
	print_parametr_map (a);

	std::cout << "after del iterator begin" << std::endl;
	a.erase(a.begin());
	print_map(a);
	print_parametr_map (a);

	std::cout << "after del iterator range begin + 1 and end" << std::endl;
	it_a_begin = ++a.begin();
	it_a_end = a.end();
	a.erase(it_a_begin, it_a_end);
	print_map(a);
	print_parametr_map (a);

	std::cout << "befor swap" << std::endl;
	std::cout << "      a     " << std::endl;
	std::cout << "____________" << std::endl;
	print_map(a);
	print_parametr_map (a);
	std::cout << "      c     " << std::endl;
	std::cout << "____________" << std::endl;
	print_map(c);
	print_parametr_map (c);
	a.swap(c);
	std::cout << "after swap" << std::endl;
	std::cout << "      a     " << std::endl;
	std::cout << "____________" << std::endl;
	print_map(a);
	print_parametr_map (a);
	std::cout << "      c     " << std::endl;
	std::cout << "____________" << std::endl;
	print_map(c);
	print_parametr_map (c);

	std::cout << "how in conteiner key = 2? " << a.count(2) << std::endl;
	std::cout << "how in conteiner key = -1? " << a.count(-1) << std::endl;
	std::cout << "how in conteiner key = -10? " << a.count(-10) << std::endl << std::endl;

	std::cout << "a == a\t" << (a == a) << std::endl;
	std::cout << "a != a\t" << (a != a) << std::endl;
	std::cout << "a == c\t" << (a == c) << std::endl;
	std::cout << "a != c\t" << (a != c) << std::endl;
	std::cout << "a < a \t" << (a < a) << std::endl;
	std::cout << "a <= a\t" << (a <= a) << std::endl;
	std::cout << "a < c \t" << (a < c) << std::endl;
	std::cout << "a <= c\t" << (a <= c) << std::endl;
	std::cout << "a > a \t" << (a > a) << std::endl;
	std::cout << "a >= a\t" << (a >= a) << std::endl;
	std::cout << "a > c \t" << (a > c) << std::endl;
	std::cout << "a >= c\t" << (a >= c) << std::endl;


	std::cout << "after clear iterator begin" << std::endl;
	a.clear();
	print_parametr_map (a);
}

int check_intra(int argc, char** argv) {
	std::cout << "check intra checker for " << V << std::endl;
	//if (argc != 2)
	//{
	//	std::cerr << "Usage: ./test seed" << std::endl;
	//	std::cerr << "Provide a seed please" << std::endl;
	//	std::cerr << "Count value:" << COUNT << std::endl;
	//	return 1;
	//}
	//const int seed = atoi(argv[1]);
	(void) argc;
	(void) argv;
	srand(1);

	NM::vector<std::string> vector_str;
	NM::vector<int> vector_int;
	NM::stack<int> stack_int;
	NM::vector<Buffer> vector_buffer;
	NM::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	NM::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	NM::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(NM::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		NM::map<int, int> copy = map_int;
	}

	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}

int	main(int argc, char** argv)
{
	check_intra(argc, argv);
	check_vector();
	check_stack();
	check_map();

	return 0;
}


