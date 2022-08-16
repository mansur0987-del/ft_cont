/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:40:53 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/16 19:37:56 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "../utils/utils.hpp"
# include "pair.hpp"
# include "TreeNode.hpp"
# include "map_iterator.hpp"
# include <functional>

namespace ft
{
	template<
			class Key,
			class T,
			class Compare = ft::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> >
	> class map
	{
	private:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef ft::TreeNode<value_type>					node_type;
		typedef Allocator									allocator_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		protected:
			Compare									comp;
			value_compare( Compare c ) : comp(c)
			{};
		public:
			bool operator()( const value_type& lhs, const value_type& rhs ) const
			{
				return (comp(lhs.first, rhs.first));
			};
		};

	public:
		typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef ft::map_iterator <value_type, node_type *>			iterator;
		typedef ft::map_iterator <const value_type, node_type *>		const_iterator;
		typedef ft::reverse_iterator <iterator>						reverse_iterator;
		typedef ft::reverse_iterator <const_iterator>				const_reverse_iterator;

	public:
		node_allocator	_alloc;
		key_compare		_comp;
		size_type		_size;
		node_type*		_root;

	public:
		map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _size(0), _root(nullptr)
		{};

		template< class InputIt >
		map( typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last,
			const Compare& comp = key_compare(),
			const Allocator& alloc = allocator_type()) :
				_alloc(alloc), _comp(comp), _size(0), _root(nullptr)
		{
			this->insert(first, last);
		}

		map( const map& other ) : _alloc(other._alloc), _comp(other._comp), _size(0), _root(nullptr)
		{
			*this = other;
		};

		~map()
		{
			if (_size == 0)
				return ;
			ClearTree(_root);
			this->_size = 0;
		}

		map& operator=( const map& other )
		{
			if (this == &other)
				return (*this);
			this->ClearTree(_root);
			this->insert(other.begin(), other.end());
			return *this;
		};

		allocator_type get_allocator() const
		{
			return (this->_alloc);
		};

		iterator begin()
		{
			if (_root == nullptr)
				return end();
			node_type *tmp = _root;
			while (tmp->left != nullptr)
				tmp = tmp->left;
			return iterator(tmp);
		};

		const_iterator begin() const
		{
			if (_root == nullptr)
				return end();
			node_type *tmp = _root;
			while (tmp->left != nullptr)
				tmp = tmp->left;
			return const_iterator(tmp);
		};

		reverse_iterator rbegin()
		{
			return(reverse_iterator(end()));
		};

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		};

		iterator end()
		{
			if (_root == nullptr)
				return _root;
			node_type *tmp = _root;
			while (tmp->right != nullptr)
				tmp = tmp->right;
			return iterator(tmp->right);
		};

		const_iterator end() const
		{
			if (_root == nullptr)
				return _root;
			node_type *tmp = _root;
			while (tmp->right != nullptr)
				tmp = tmp->right;
			return const_iterator(tmp->right);
		};

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		};

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		};

		bool empty() const
		{
			return (_size == 0);
		};

		size_type size() const
		{
			return(_size);
		};

		size_type max_size() const
		{
			return (_alloc.max_size());
		};

		void clear()
		{
			if (_size == 0)
				return ;

			ClearTree(_root);
			_size = 0;
		}

		ft::pair<iterator, bool> insert( const value_type& value )
		{
			size_type begin = this->_size;

			node_type *tmp = InsertNode(value, this->_root, nullptr, false);

			if (this->_root == nullptr)
				this->_root = tmp;

			return (ft::pair<iterator, bool>(tmp, begin != _size));

		};

		iterator insert( iterator hint, const value_type& value )
		{
			(void)hint;
			node_type *tmp = InsertNode(value, this->_root, nullptr, false);

			if (this->_root == nullptr)
				this->_root = tmp;

			return (iterator(tmp));
		};

		template< class InputIt >
		void insert(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
		{
			InputIt tmp = first;
			for (; tmp != last; tmp++)
			{
				insert((*tmp));
			}
		};

		void erase( iterator pos )
		{
			erase(pos->first);
		};

		void erase( iterator first, iterator last )
		{
			map<key_type, mapped_type>	tmp(first, last);

			iterator 					it = tmp.begin();
			iterator 					ite = tmp.end();

			for (; it != ite; it++)
			{
				erase(it->first);
			}
		};

		size_type erase( const Key& key )
		{
			size_type tmp = _size;

			DeleteNode(_root, key);

			return (tmp - _size);
		};

		void swap( map& other )
		{
			node_allocator	tmp_alloc = this->_alloc;
			key_compare		tmp_comp = this->_comp;
			size_type		tmp_size = this->_size;
			node_type*		tmp_root = this->_root;

			this->_alloc = other._alloc;
			this->_comp = other._comp;
			this->_size = other._size;
			this->_root = other._root;

			other._alloc = tmp_alloc;
			other._comp = tmp_comp;
			other._size = tmp_size;
			other._root = tmp_root;
		}

		size_type count( const Key& key ) const
		{
			if (this->find(key) == this->end())
				return (0);
			return (1);
		};

		iterator find( const Key& key )
		{
			iterator	it = this->begin();
			iterator	ite = this->end();

			for (; it != ite; it++)
			{
				if (!(this->_comp(it->first, key)) && !(this->_comp(key, it->first)))
					break ;
			}
			return it;
		}

		const_iterator find( const Key& key ) const
		{
			const_iterator it = this->begin();
			const_iterator ite = this->end();

			for (; it != ite; it++)
				{
					if (!(this->_comp(it->first, key)) && !(this->_comp(key, it->first)))
						break ;
				}
			return it;
		}

		ft::pair<iterator,iterator> equal_range( const Key& key )
		{
			return (ft::pair<iterator,iterator> (this->lower_bound(key), this->upper_bound(key)));
		}

		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			return (ft::pair<iterator,iterator> (this->lower_bound(key), this->upper_bound(key)));
		}

		iterator upper_bound( const Key& key )
		{
			iterator	it = this->begin();
			iterator	ite = this->end();

			for (; it != ite; it++)
			{
				if (!(this->_comp(it->first, key)))
					return (it);
			}
			return (ite);
		}

		const_iterator upper_bound( const Key& key ) const
		{
			const_iterator	it = this->begin();
			const_iterator	ite = this->end();

			for (; it != ite; it++)
			{
				if (!(this->_comp(it->first, key)))
					return (it);
			}
			return (ite);
		}

		iterator lower_bound( const Key& key )
		{
			iterator	it = this->begin();
			iterator	ite = this->end();

			for (; it != ite; it++)
			{
				if (this->_comp(key, it->first))
					return (it);
			}
			return (ite);
		}

		const_iterator lower_bound( const Key& key ) const
		{
			const_iterator	it = this->begin();
			const_iterator	ite = this->end();

			for (; it != ite; it++)
			{
				if (this->_comp(key, it->first))
					return (it);
			}
			return (ite);
		}

		key_compare key_comp() const
		{
			return (this->_comp);
		}

		value_compare value_comp() const
		{
			return (this->value_comp(key_compare()));
		}

		void	DeleteNode(node_type *node, const Key& key)
		{

			if (node == nullptr)
				return ;
			if (_comp(key, node->data.first))
				DeleteNode(node->left, key);
			else if (_comp(node->data.first, key))
				DeleteNode(node->right, key);
			else
			{
				node_type *parent = node->parent;
				if (_size == 1)
				{
					_root = nullptr;
				}
				else if (parent == nullptr)
				{
					if (node->left == nullptr)
					{
						node->right->parent = parent;
						node->right->RightChild = false;
						_root = node->right;
					}
					else
					{
						node->left->parent = parent;
						if (node->right != nullptr)
						{
							node_type *last_left = FindValueLeft(node->right);
							if (node->left->right != nullptr)
							{
								node->left->right->parent = last_left;
								node->left->right->RightChild = false;
							}
							last_left->left = node->left->right;
							node->right->parent = node->left;
						}
						node->left->right = node->right;
						_root = node->left;
					}
				}
				else if (node->right == nullptr && node->left == nullptr)
				{
					if (node->RightChild)
						parent->right = nullptr;
					else
						parent->left = nullptr;
				}
				else if (node->RightChild)
				{
					if (node->right == nullptr)
					{
						parent->right = node->left;
						node->left->parent = parent;
						node->left->RightChild = true;
					}
					else
					{
						parent->right = node->right;
						node->right->parent = parent;
						if (node->left != nullptr)
						{
							node_type *last_left = FindValueLeft(node->right);
							node->left->parent = last_left;
							last_left->left = node->left;
						}
					}
				}
				else
				{
					if (node->left == nullptr)
					{
						parent->left = node->right;
						node->right->parent = parent;
						node->right->RightChild = false;
					}
					else
					{
						parent->left = node->left;
						node->left->parent = parent;
						if (node->right != nullptr)
						{
							node_type *last_right = FindValueRight(node->left);
							node->right->parent = last_right;
							last_right->right = node->right;
						}
					}
				}
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
				node = nullptr;
				_size--;
			}
		};

		node_type	*FindValueLeft(node_type *node)
		{
			if (node->left != nullptr)
				node = FindValueLeft(node->left);
			return (node);
		};

		node_type	*FindValueRight(node_type *node)
		{
			if (node->right != nullptr)
				node = FindValueRight(node->right);
			return (node);
		};

		node_type*	InsertNode(const value_type& value, node_type *node, node_type *parent, bool RightChild)
		{
			if (node == nullptr)
			{
				node = AddNode(value, parent, RightChild);
				_size++;

				if (parent != nullptr)
				{
					if (RightChild)
						parent->right = node;
					else
						parent->left = node;
				}
				return (node);
			}
			if (_comp(value.first, node->data.first))
			{
				node = InsertNode(value, node->left, node, false);
				return (node);
			}
			else if (_comp(node->data.first, value.first))
			{
				node = InsertNode(value, node->right, node, true);
				return (node);
			}
			return(node);
		};

		node_type*	AddNode(const value_type& value, node_type *parent, bool RightChild)
		{
			node_type* tmp = _alloc.allocate(1);

			_alloc.construct(tmp, node_type(value, parent, nullptr, nullptr, RightChild));
			return (tmp);
		};

		void	ClearTree(node_type *node)
		{
			if (node == nullptr)
				return ;
			if (node->left != nullptr)
				ClearTree(node->left);
			if (node->right != nullptr)
				ClearTree(node->right);
			this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);
			node = nullptr;
		};
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::check(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return(!(rhs < lhs));
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return(rhs < lhs);
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return(!(lhs < rhs));
	};

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

}

#endif
