/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:11:39 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/15 19:19:52 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "../utils/utils.hpp"

namespace ft
{
	template < class pair_type, class node_ptr >
	class map_iterator
	{
	public:
		typedef typename std::ptrdiff_t										difference_type;
		typedef pair_type													value_type;
		typedef pair_type*													pointer;
		typedef pair_type&													reference;
		typedef ft::bidirectional_iterator_tag								iterator_category;

		node_ptr															ptr_to_node;
		node_ptr															end;

		map_iterator() : ptr_to_node(nullptr), end(FindEnd(ptr_to_node))
		{};
		map_iterator(const node_ptr &other_node_ptr) : ptr_to_node(other_node_ptr), end(FindEnd(other_node_ptr))
		{};
		map_iterator(const map_iterator& other) : ptr_to_node(other.ptr_to_node), end(other.end)
		{};
		~map_iterator()
		{};
		map_iterator &operator=(const map_iterator& other)
		{
			if (this == &other)
				return (*this);
			this->ptr_to_node = other.ptr_to_node;
			this->end = other.end;
			return (*this);
		};

		reference operator*()
		{
			return (this->ptr_to_node->data);
		};

		pointer operator->()
		{
			return (&(operator*()));
		};

		node_ptr FindEnd(node_ptr other)
		{
			if (other != nullptr)
			{
				while (other->parent != nullptr)
					other = other->parent;
				while (other->right != nullptr)
					other = other->right;
			}
			return (other);
		};

		bool	operator==(map_iterator<pair_type, node_ptr> other) const
		{
			return (this->ptr_to_node == other.ptr_to_node);
		};

		bool	operator!=(map_iterator<pair_type, node_ptr> other) const
		{
			return (this->ptr_to_node != other.ptr_to_node);
		};

		map_iterator	&operator++()
		{
			if (this->ptr_to_node == this->end)
				this->ptr_to_node = nullptr;
			else if (this->ptr_to_node->right != nullptr)
			{
				this->ptr_to_node = this->ptr_to_node->right;
				while (this->ptr_to_node->left != nullptr)
					this->ptr_to_node = this->ptr_to_node->left;
			}
			else
			{
				while (this->ptr_to_node->RightChild)
					this->ptr_to_node = this->ptr_to_node->parent;
				this->ptr_to_node = this->ptr_to_node->parent;
			}
			return (*this);
		};

		map_iterator	operator++(int)
		{
			map_iterator tmp(*this);

			this->operator++();
			return (tmp);
		};

		map_iterator	&operator--()
		{
			if (this->ptr_to_node == nullptr)
				return *this;
			if (this->ptr_to_node->left != nullptr)
			{
				this->ptr_to_node = this->ptr_to_node->left;
				while (this->ptr_to_node->right != nullptr)
					this->ptr_to_node = this->ptr_to_node->right;
			}
			else
			{
				if (this->ptr_to_node->RightChild)
					this->ptr_to_node = this->ptr_to_node->parent;
			}
			return (*this);
		};

		map_iterator	operator--(int)
		{
			map_iterator tmp(*this);

			this->operator--();
			return (tmp);
		};
	};
}

#endif
