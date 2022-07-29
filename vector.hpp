#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
	public:
		typedef T						value_type;
		typedef Alloc					allocator_type;
		typedef size_t					size_type;

	private:
		value_type*				_data;
		allocator_type			_alloc;
		size_type				_size;
		size_type				_capacity;
	public:

	};
}


#endif
