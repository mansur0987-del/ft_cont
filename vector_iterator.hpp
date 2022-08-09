/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:34:06 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/09 19:05:27 by armaxima         ###   ########.fr       */
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
		//friend iterator	operator+(difference_type n, const iterator &it)
		//{
		//	return it.operator+(n);
		//}
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

		//difference_type	operator-(const random_iterator<T> &n) const
		//{
		//	return iter::operator-(n);
		//}
		//friend iterator	operator+(difference_type n, const iterator &it)
		//{
		//	return it.operator+(n);
		//}
	};

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template< class Iter >
	struct iterator_traits
	{
		typedef Iter	iterator_type;
		typedef typename Iter::difference_type			difference_type;
		typedef typename Iter::value_type				value_type;
		typedef typename Iter::pointer					pointer;
		typedef typename Iter::reference				reference;
		typedef typename ft::random_access_iterator_tag	iterator_category;
	};

	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class iterator_type>
	class reverse_iterator
	{
	protected:
		iterator_type														base_iterator;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;

	public:
		reverse_iterator() : base_iterator()
		{};
		reverse_iterator(iterator_type base) : base_iterator(base)
		{};
		iterator_type get_base() const
		{
			return this->base_iterator;
		};
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &src) : base_iterator(src.get_base())
		{};
		template <class Iter>
		reverse_iterator<iterator_type>& operator=(const reverse_iterator<Iter>& other)
		{
			if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&other))
				return *this;
			this->base_iterator = other.get_base();
			return *this;
		};
		~reverse_iterator()
		{};

		reference operator*() const
		{
			iterator_type tmp = base_iterator;
			return (*(--tmp));
		}
		pointer	operator->(void) const
		{
			return &this->operator*();
		};

		reverse_iterator& operator++()
		{
			--this->base_iterator;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		reverse_iterator& operator--()
		{
			++this->base_iterator;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		//template <class Iter>
		//difference_type	operator-(const reverse_iterator<Iter> &other)
		//{
		//	return other.get_base().operator-(this->base_iterator);
		//};

		reverse_iterator	operator+(difference_type n) const
		{
			return reverse_iterator(this->base_iterator.operator-(n));
		};

		reverse_iterator&	operator+=(difference_type n)
		{
			this->base_iterator.operator-=(n);
			return *this;
		};

		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator(this->base_iterator.operator+(n));
		};

		reverse_iterator&	operator-=(difference_type n)
		{
			this->base_iterator.operator+=(n);
			return *this;
		};

		reference	operator[](difference_type n) const
		{
			return *this->operator+(n);
		};

		//friend reverse_iterator	operator+(difference_type n, const reverse_iterator &it) {
		//	return it.operator+(n);
		//};

		template <class Iter>
		bool operator==(const reverse_iterator<Iter> &other) const {
			return this->base_iterator.operator==(other.get_base());
		};

		template <class Iter>
		bool operator!=(const reverse_iterator<Iter> &other) const {
			return this->base_iterator.operator!=(other.get_base());
		};

		template <class Iter>
		bool operator<(const reverse_iterator<Iter> &other)
			const { return this->base_iterator.operator> (other.get_base());
		};

		template <class Iter>
		bool operator<=(const reverse_iterator<Iter> &other) const {
			return this->base_iterator.operator>=(other.get_base());
		};

		template <class Iter>
		bool	operator>(const reverse_iterator<Iter> &other) const {
			return this->base_iterator.operator< (other.get_base());
		};

		template <class Iter>
		bool	operator>=(const reverse_iterator<Iter> &other) const {
			return this->base_iterator.operator<=(other.get_base());
		};

		template <bool, class IsTrue = void>
		struct enable_if;

		template <class IsTrue>
		struct enable_if<true, IsTrue> {
			typedef IsTrue type;
		};
	};

	//template<
	//class Category,
	//class T,
	//class Distance = std::ptrdiff_t,
	//class Pointer = T*,
	//class Reference = T&
	//> struct iterator
	//{
	//	typedef Category		iterator_category;
	//	typedef T				value_type;
	//	typedef Distance		difference_type;
	//	typedef Pointer			pointer;
	//	typedef Reference		reference;
	//};
}

#endif
