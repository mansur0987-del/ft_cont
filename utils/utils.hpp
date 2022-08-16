/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:19:36 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/13 19:47:44 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "../vector/vector_iterator.hpp"

namespace ft
{
	template< bool B, class T = void >
	struct enable_if
	{};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T> struct is_integral 					{ static const bool value = false;};
	template <> struct is_integral<bool> 					{ static const bool value = true; };
	template <> struct is_integral<char> 					{ static const bool value = true; };
	template <> struct is_integral<short int> 				{ static const bool value = true; };
	template <> struct is_integral<int> 					{ static const bool value = true; };
	template <> struct is_integral<long int> 				{ static const bool value = true; };
	template <> struct is_integral<long long int> 			{ static const bool value = true; };
	template <> struct is_integral<unsigned char> 			{ static const bool value = true; };
	template <> struct is_integral<unsigned short int> 		{ static const bool value = true; };
	template <> struct is_integral<unsigned int> 			{ static const bool value = true; };
	template <> struct is_integral<unsigned long int> 		{ static const bool value = true; };
	template <> struct is_integral<unsigned long long int> 	{ static const bool value = true; };

	template<class Iter>
	bool check(Iter first1, Iter end1, Iter first2)
	{
		while (first1 != end1)
		{
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	};

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2 )
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	};

	template< class T >
	struct less
	{
		bool operator()( const T& lhs, const T& rhs ) const
		{
			return (lhs < rhs);
		};
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

		template <class Iter>
		difference_type	operator-(const reverse_iterator<Iter> &other)
		{
			return other.get_base().operator-(this->base_iterator);
		};

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
	};
}

#endif
