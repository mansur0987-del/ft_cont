/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:34:06 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/11 15:10:55 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <memory>
# include "random_iterator.hpp"

namespace ft
{
	template <typename T>
	class iterator : public ft::random_iterator<T>
	{
	public:
		typedef std::ptrdiff_t					difference_type;
	protected:
		typedef random_iterator<T>	iter;
	public:

		iterator() : random_iterator<T>()
		{};
		iterator(T* src) : random_iterator<T>(src)
		{};
		iterator(const iterator &src) : random_iterator<T>(src)
		{};
		iterator(const random_iterator<T> &src) : random_iterator<T>(src)
		{};
		typedef T&					reference;
		typedef T*					pointer;
		reference	operator*() const
		{
			return *this->ptr_value;
		}
		pointer	operator->() const
		{
			return this->ptr_value;
		}
		iterator&	operator+=(difference_type n)
		{
			this->ptr_value += n;
			return *this;
		}
		iterator&	operator-=(difference_type n)
		{
			this->ptr_value -= n;
			return *this;
		}
		reference	operator[](difference_type n) const
		{
			return this->_value[n];
		}

		iterator&	operator++()
		{
			iter::operator++();
			return *this;
		}
		iterator	operator++(int)
		{
			return iter::operator++(0);
		}

		iterator&	operator--()
		{
			iter::operator--();
			return *this;
		}
		iterator	operator--(int)
		{
			return iter::operator--(0);
		}

		iterator	operator+(difference_type n) const
		{
			return iter::operator+(n);
		}

		iterator	operator-(difference_type n) const
		{
			return iter::operator-(n);
		}

		difference_type	operator-(const random_iterator<T> &n) const
		{
			return iter::operator-(n);
		}
	};

	template <class T>
	class const_iterator : public random_iterator<T>
	{
	public:
		typedef std::ptrdiff_t					difference_type;
	protected:
		typedef random_iterator<T>	iter;
	public:

		const_iterator() : random_iterator<T>()
		{};
		const_iterator(T* src) : random_iterator<T>(src)
		{};
		const_iterator(const const_iterator &src) : random_iterator<T>(src)
		{};
		const_iterator(const random_iterator<T> &src) : random_iterator<T>(src)
		{};
		typedef const T&					reference;
		typedef const T*					pointer;
		reference	operator*() const
		{
			return *this->ptr_value;
		}
		pointer	operator->() const
		{
			return this->ptr_value;
		}
		const_iterator&	operator+=(difference_type n)
		{
			this->ptr_value += n;
			return *this;
		}
		const_iterator&	operator-=(difference_type n)
		{
			this->ptr_value -= n;
			return *this;
		}
		reference	operator[](difference_type n) const
		{
			return this->_value[n];
		}

		const_iterator&	operator++()
		{
			iter::operator++();
			return *this;
		}
		const_iterator	operator++(int)
		{
			return iter::operator++(0);
		}

		const_iterator&	operator--()
		{
			iter::operator--();
			return *this;
		}
		const_iterator	operator--(int)
		{
			return iter::operator--(0);
		}

		const_iterator	operator+(difference_type n) const
		{
			return iter::operator+(n);
		}

		const_iterator	operator-(difference_type n) const
		{
			return iter::operator-(n);
		}

		difference_type	operator-(const random_iterator<T> &n) const
		{
			return iter::operator-(n);
		}
	};
}

#endif
