/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:19:36 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/09 19:44:37 by armaxima         ###   ########.fr       */
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

	template <class T> struct is_integral : std::false_type { static const bool value = std::false_type::value;};
	template <> struct is_integral<bool> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<char> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<short int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<long int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<long long int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<unsigned char> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<unsigned short int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<unsigned int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<unsigned long int> : std::true_type { static const bool value = std::true_type::value; };
	template <> struct is_integral<unsigned long long int> : std::true_type { static const bool value = std::true_type::value; };

}

#endif
