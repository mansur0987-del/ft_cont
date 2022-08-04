/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:34:10 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/04 19:13:42 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "vector_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;

		class 												iterator;
		class 												const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		value_type*				_data;
		allocator_type			_alloc;
		size_type				_size;
		size_type				_capacity;
	public:
		vector() : _size(0), _capacity(0), _alloc()
		{
			_data = _alloc.allocate(0);
		};

		explicit vector( const Allocator& alloc ) : _size(0), _capacity(0), _alloc(alloc)
		{
			_data = _alloc.allocate(0);
		};

		explicit vector( size_type count,
				const T& value,
				const Allocator& alloc = Allocator()) :
			_size(count), _capacity(count), _alloc(alloc)
		{
			_data = _alloc.allocate(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
		};

		template< class InputIt >
		vector( InputIt first,
				InputIt last,
				const Allocator& alloc = Allocator(),
				typename ft::enable_if<ft::is_integral<InputIt>::value, InputIt>::type = InputIt() ) :
				_alloc(alloc), _size(0), _capacity(0)
		{
			difference_type n = ft::distance(first, last);
			_data = _alloc.allocate(n);
			for (size_type i = 0; first != last; first++, i++)
				_alloc.construct(_data + i, *first);
		};

		vector( const vector& other ) : _size(other._size),
										_capacity(other._capacity),
										_alloc(other._alloc)
		{
			_data = _alloc.allocate(other._capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, other._data[i]);
		};

		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
		};

		vector &operator=( const vector& other )
		{
			if (this == &other)
				return (*this);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);

			_size = other._size;
			_capacity = other._capacity;
			_data = _alloc.allocate(other._capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, other._data[i]);

			return (*this);
		};

		void assign( size_type count, const T& value )
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			if (this->_capacity < count)
			{
				_alloc.deallocate(_data, _capacity);
				_data = _alloc.allocate(count);
				this->_capacity = count;
			}
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, value);
			this->_size = count;
		};

		template< class InputIt >
		void assign(	InputIt first,
						InputIt last,
						typename ft::enable_if<ft::is_integral<InputIt>::value, InputIt>::type = InputIt() )
		{
			difference_type n = ft::distance(first, last);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			if (this->_capacity < n)
			{
				_alloc.deallocate(_data, _capacity);
				_data = _alloc.allocate(n);
				this->_capacity = n;
			}
			for (size_type i = 0; first != last; first++, i++)
				_alloc.construct(_data + i, *first);
			this->_size = n;
		};

		allocator_type get_allocator() const
		{
			return this->_alloc;
		};

		reference at( size_type pos )
		{
			if (pos >= this->_size)
				throw std::out_of_range("vector");
			return this->_data[pos];
		};

		const_reference at( size_type pos ) const
		{
			if (pos >= this->_size)
				throw std::out_of_range("vector");
			return this->_data[pos];
		};

		reference operator[]( size_type pos )
		{
			return this->_data[pos];
		};

		const_reference operator[]( size_type pos ) const
		{
			return this->_data[pos];
		};

		reference front()
		{
			return this->_data[0];
		};

		const_reference front() const
		{
			return this->_data[0];
		};

		reference back()
		{
			return this->_data[this->_size - 1];
		};

		const_reference back() const
		{
			return this->_data[this->_size - 1];
		};

		T* data()
		{
			return this->_data;
		};

		const T* data() const
		{
			return this->_data;
		};

		iterator begin()
		{
			return this->_data;
		};

		const_iterator begin() const
		{
			return this->_data;
		};

		iterator end()
		{
			return this->_data + this->_size;
		};

		const_iterator end() const
		{
			return this->_data + this->_size;
		};

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->_data + this->_size);
		};

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->_data + this->_size);
		};

		reverse_iterator rend()
		{
			return reverse_iterator(this->_data);
		};

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->_data);
		};

		bool empty() const
		{
			if (this->_size == 0)
				return true;
			return false;
		};

		size_type size() const
		{
			return this->_size;
		};

		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max();
		};

		void reserve( size_type new_cap )
		{
			if (new_cap > max_size())
				throw std::length_error("vector");
			if (new_cap <= this->_capacity)
				return;

			value_type* tmp = _alloc.allocate(new_cap);
			for (size_type i = 0; i < this->_size; i++)
				_alloc.construct(tmp + i, this->_data[i]);

			for (size_type i = 0; i < this->_size; i++)
				_alloc.destroy(this->_data + i);
			_alloc.deallocate(this->_data, this->_capacity);

			this->_capacity = new_cap;
			this->_data = tmp;
		};

		size_type capacity() const
		{
			return this->_capacity;
		};

		void clear()
		{
			for (size_type i = 0; i < this->_size; i++)
				_alloc.destroy(this->_data + i);
			this->_size = 0;
		};

		iterator insert( iterator pos, const T& value )
		{

		};
		iterator insert( const_iterator pos, T&& value );
		void insert( iterator pos, size_type count, const T& value );
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last );
	};
}


#endif
