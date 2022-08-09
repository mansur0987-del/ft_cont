/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:28:48 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/09 19:04:19 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ITERATOR_HPP
# define RANDOM_ITERATOR_HPP

# include <memory>

namespace ft
{
	template <class vector_type>
	class random_iterator
	{
	protected:
		vector_type*					ptr_value;

	public:
		typedef vector_type				value_type;
		typedef std::ptrdiff_t			difference_type;

		random_iterator() : ptr_value(NULL)
		{};
		virtual ~random_iterator()
		{};
		random_iterator(value_type* value) : ptr_value(value)
		{};
		random_iterator(const random_iterator& src)
		{
			*this = src;
		};
		random_iterator& operator=(random_iterator const& op)
		{
			if (this == &op)
				return *this;
			this->ptr_value = op.ptr_value;
			return *this;
		};

		random_iterator<vector_type>& operator++()
		{
			++this->ptr_value;
			return *this;
		};

		random_iterator<vector_type>	operator++(int)
		{
			random_iterator<vector_type>	tmp(*this);
			++this->ptr_value;
			return (tmp);
		};

		random_iterator<vector_type>& operator--()
		{
			--this->ptr_value;
			return *this;
		};

		random_iterator<vector_type>	operator--(int)
		{
			random_iterator<vector_type>	tmp(*this);
			--this->ptr_value;
			return (tmp);
		};

		random_iterator<vector_type>	operator+(std::ptrdiff_t n) const
		{
			return random_iterator(this->ptr_value + n);
		};

		random_iterator<vector_type>	operator-(std::ptrdiff_t n) const
		{
			return random_iterator(this->ptr_value - n);
		};

		//difference_type	operator-(const random_iterator &it) const
		//{
		//	return this->ptr_value - it.ptr_value;
		//};

		//friend random_iterator<vector_type>	operator+(difference_type n, const random_iterator& it)
		//{
		//	return it.operator+(n);
		//};

		bool operator==(const random_iterator &rhs) const
		{
			return this->ptr_value == rhs.ptr_value;
		};
		bool operator!=(const random_iterator &rhs) const
		{
			return this->ptr_value != rhs.ptr_value;
		};
		bool operator<(const random_iterator &rhs) const
		{
			return this->ptr_value < rhs.ptr_value;
		};
		bool operator<=(const random_iterator &rhs) const
		{
			return this->ptr_value <= rhs.ptr_value;
		};
		bool operator>(const random_iterator &rhs) const
		{
			return this->ptr_value > rhs.ptr_value;
		};
		bool operator>=(const random_iterator &rhs) const
		{
			return this->ptr_value >= rhs.ptr_value;
		};
	};
}
#endif
