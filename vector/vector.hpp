/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:34:10 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/17 16:33:07 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "vector_iterator.hpp"
# include "../utils/utils.hpp"

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

		typedef ft::iterator<value_type>					iterator;
		typedef ft::const_iterator<value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		value_type*				_data;
		allocator_type			_alloc;
		size_type				_size;
		size_type				_capacity;
	public:
		vector() : _data(nullptr), _alloc(), _size(0), _capacity(0)
		{
		};

		explicit vector( const Allocator& alloc ) : _data(nullptr), _alloc(alloc), _size(0), _capacity(0)
		{
		};

		explicit vector( size_type count,
				const T& value,
				const Allocator& alloc = Allocator()) :
			_alloc(alloc), _size(count), _capacity(count)
		{
			_data = _alloc.allocate(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
		};

		template< class InputIt >
		vector( InputIt first,
				InputIt last,
				const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt() ) :
				_data(NULL), _alloc(alloc), _size(0), _capacity(0)
		{
			size_type n = last - first;
			this->_data = _alloc.allocate(n);
			this->_capacity = n;
			this->_size = n;
			for (size_type i = 0; i != n; i++)
			{
				_alloc.construct(this->_data + i, *first);
				first++;
			}
		};

		vector( const vector& other ) : _alloc(other._alloc),
										_size(other._size),
										_capacity(other._capacity)
		{
			_data = _alloc.allocate(other._capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, other._data[i]);
		};

		virtual ~vector()
		{
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
			this->_size = count;
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, value);
		};

		template< class InputIt >
		void assign(	InputIt first,
						InputIt last,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt() )
		{
			size_type n = last - first;
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
			return iterator(this->_data);
		};

		const_iterator begin() const
		{
			return const_iterator(this->_data);
		};

		iterator end()
		{
			return iterator(this->_data + this->_size);
		};

		const_iterator end() const
		{
			return const_iterator(this->_data + this->_size);
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
			return this->_alloc.max_size();
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

		void push_back( const T& value )
		{
			if (this->_capacity == 0)
			{
				this->_alloc.deallocate(_data, _capacity);
				this->_capacity = 1;
				this->_data = this->_alloc.allocate(this->_capacity);
			}
			else if (this->_capacity <= this->_size)
			{
				this->_capacity *= 2;
				value_type* tmp = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, this->_data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				this->_data = tmp;
			}
			_alloc.construct(_data + this->_size, value);
			this->_size++;
		}

		iterator insert( iterator pos, const T& value )
		{
			if (this->_size == this->_capacity)
				this->_capacity *= 2;
			value_type* tmp = this->_alloc.allocate(this->_capacity);
			size_type n = pos - begin();

			size_type i = 0;
			for (; i < n; i++)
				this->_alloc.construct(tmp + i, this->_data[i]);
			this->_alloc.construct(tmp + i++, value);
			for (; i - 1 < this->_size; i++)
				this->_alloc.construct(tmp + i, this->_data[i - 1]);

			this->~vector();

			this->_size++;
			this->_data = tmp;
			return iterator((&this->_data[n]));
		}

		void insert( iterator pos, size_type count, const T& value )
		{
			size_type n = pos - begin();
			if (this->_size == 0)
				this->_capacity = count;
			else if (this->_size + count > this->_capacity)
				this->_capacity *= 2;
			value_type* tmp = this->_alloc.allocate(this->_capacity);

			size_type i = 0;
			for (; i < n; i++)
				this->_alloc.construct(tmp + i, this->_data[i]);
			size_type q = i;
			for (size_type j = 0; j < count; j++)
				this->_alloc.construct(tmp + i++, value);
			for (; q < size(); q++)
				this->_alloc.construct(tmp + i++, this->_data[q]);

			this->~vector();

			this->_size += count;
			this->_data = tmp;
		}

		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last ,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt() )
		{
			size_type pos_n = pos - begin();
			size_type count = last - first;
			if (this->_size == 0)
				this->_capacity = count;
			else if (this->_size + count > this->_capacity)
				this->_capacity *= 2;
			value_type* tmp = this->_alloc.allocate(this->_capacity);

			size_type i = 0;
			for (; i < pos_n; i++)
				this->_alloc.construct(tmp + i, this->_data[i]);
			size_type q = i;
			for(; first != last; first++)
				this->_alloc.construct(tmp + i++, *first);
			for (; q < size(); q++)
				this->_alloc.construct(tmp + i++, this->_data[q]);

			this->~vector();

			this->_size += count;
			this->_data = tmp;
		}

		iterator erase( iterator pos )
		{
			iterator tmp = pos;
			iterator next = pos + 1;

			while (next != end())
			{
				*pos = *next;
				next++;
				pos++;
			}

			this->_alloc.destroy(&this->_data[--this->_size]);
			return (tmp);
		}

		iterator erase( iterator first, iterator last )
		{
			iterator tmp = first;
			size_type len = last - first;

			while (last != end())
			{
				*first = *last;
				first++;
				last++;
			}

			for (; len > 0; len--)
				this->_alloc.destroy(&this->_data[--this->_size]);
			return (tmp);
		}

		void pop_back()
		{
			this->_alloc.destroy(&this->_data[--this->_size]);
		}

		void resize( size_type count, T value = T() )
		{
			if (this->_capacity < count)
			{
				this->_capacity = count;
				value_type* tmp = this->_alloc.allocate(this->_capacity);
				iterator first = begin();
				for (size_type i = 0; first != end(); first++, i++)
					_alloc.construct(tmp + i, *first);
				this->~vector();
				this->_data = tmp;
			}
			if (this->_size < count)
			{
				for (size_type i = this->_size; i != count; i++)
					_alloc.construct(this->_data + i, value);
			}
			this->_size = count;
		}

		template <class TMP>
		void	swap(TMP &a, TMP &b)
		{
			TMP c = a;
			a = b;
			b = c;
		}

		void swap( vector& other )
		{
			swap(this->_alloc, other._alloc);
			swap(this->_data, other._data);
			swap(this->_size, other._size);
			swap(this->_capacity, other._capacity);
		}

	};

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs,
			ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	};

	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::check(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	};

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return(!(rhs < lhs));
	};

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return(rhs < lhs);
	};

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return(!(lhs < rhs));
	}
}


#endif
