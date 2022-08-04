/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:19:36 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/04 16:20:38 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "vector_iterator.hpp"

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

	//template <class T> struct is_integral { static const bool value = false;};
	//template <> struct is_integral<bool> { static const bool value = true; };
	//template <> struct is_integral<char> { static const bool value = true; };
	//template <> struct is_integral<short int> { static const bool value = true; };
	//template <> struct is_integral<int> { static const bool value = true; };
	//template <> struct is_integral<long int> { static const bool value = true; };
	//template <> struct is_integral<long long int> { static const bool value = true; };
	//template <> struct is_integral<unsigned char> { static const bool value = true; };
	//template <> struct is_integral<unsigned short int> { static const bool value = true; };
	//template <> struct is_integral<unsigned int> { static const bool value = true; };
	//template <> struct is_integral<unsigned long int> { static const bool value = true; };
	//template <> struct is_integral<unsigned long long int> { static const bool value = true; };

	template <class T>
	struct is_integral {
	private:
		template <class C>
		static typename C::iterator_category f(int a) {return C::iterator_category();};

		template <class C>
		static double	f(...) {return 0;};
	public:
		static const bool value = sizeof(f<T>(1)) != sizeof(double);
	};

	template <class T>
	struct is_integral<T *> {
		static const bool value = true;
	};

	template<class Iter>
	typename ft::iterator_traits<Iter>::difference_type
		__do_distance(Iter first, Iter last, ft::input_iterator_tag)
	{
		typename ft::iterator_traits<Iter>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	};

	template<class Iter>
	typename ft::iterator_traits<Iter>::difference_type
		__do_distance(Iter first, Iter last, ft::random_access_iterator_tag)
	{
		return last - first;
	};

	template<class Iter>
	typename ft::iterator_traits<Iter>::difference_type distance(Iter first, Iter last)
	{
		return ft::__do_distance(first, last, typename ft::iterator_traits<Iter>::iterator_category());
	};
}

#endif
