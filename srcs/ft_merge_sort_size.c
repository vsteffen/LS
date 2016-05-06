/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:38:22 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 17:39:23 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		partition_s(nodePtr head, nodePtr *front, nodePtr *back)
{
	nodePtr		fast;
	nodePtr		slow;

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

nodePtr		merge_list_s(nodePtr a, nodePtr b)
{
	nodePtr merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((ft_strcmp(a->name, b->name) <= 0 && a->stat.st_size
			== b->stat.st_size) || a->stat.st_size > b->stat.st_size)
	{
		merged_list = a;
		merged_list->next = merge_list_s(a->next, b);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_list_s(a, b->next);
	}
	return (merged_list);
}

void		ft_merge_sort_size(nodePtr *source)
{
	nodePtr		head;
	nodePtr		a;
	nodePtr		b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition_s(head, &a, &b);
	ft_merge_sort_size(&a);
	ft_merge_sort_size(&b);
	*source = merge_list_s(a, b);
}
