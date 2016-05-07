/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 19:13:55 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/07 20:15:18 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			partition(node_ptr head, node_ptr *front, node_ptr *back)
{
	node_ptr		fast;
	node_ptr		slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

node_ptr		merge_list(node_ptr a, node_ptr b)
{
	node_ptr merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) <= 0)
	{
		merged_list = a;
		merged_list->next = merge_list(a->next, b);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_list(a, b->next);
	}
	return (merged_list);
}

void			ft_merge_sort_list(node_ptr *source)
{
	node_ptr		head;
	node_ptr		a;
	node_ptr		b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	ft_merge_sort_list(&a);
	ft_merge_sort_list(&b);
	*source = merge_list(a, b);
}
