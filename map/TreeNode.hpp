/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeNode.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:34:42 by armaxima          #+#    #+#             */
/*   Updated: 2022/08/16 19:38:38 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREENODE_HPP
# define TREENODE_HPP

namespace ft
{
	template <class value_type>
	class TreeNode
	{
	public:
		typedef TreeNode<value_type>*			node_ptr;

		value_type						data;
		node_ptr						parent;
		node_ptr						left;
		node_ptr						right;
		bool							RightChild;


		TreeNode(const value_type &data = value_type()) :
			data(data), parent(nullptr), left(nullptr), right(nullptr), RightChild(false)
		{};
		TreeNode(const value_type &data, node_ptr parent, node_ptr left, node_ptr right, bool RightChild) :
			data(data), parent(parent), left(left), right(right), RightChild(RightChild)
		{};
		TreeNode(const TreeNode &other) :
			data(other.data), parent(other.parent), left(other.left), right(other.right), RightChild(other.RightChild)
		{};
		~TreeNode()
		{};
	};
}

#endif
