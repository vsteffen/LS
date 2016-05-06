/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort_time_u.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:22:05 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 17:52:48 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		partition_u(nodePtr head, nodePtr *front, nodePtr *back)
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

nodePtr		merge_list_u(nodePtr a, nodePtr b)
{
	nodePtr merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((ft_strcmp(a->name, b->name) <= 0 && a->stat.st_atime
== b->stat.st_atime) || a->stat.st_atime > b->stat.st_atime)
	{
		merged_list = a;
		merged_list->next = merge_list_u(a->next, b);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_list_u(a, b->next);
	}
	return (merged_list);
}

void		ft_merge_sort_time_u(nodePtr *source)
{
	nodePtr		head;
	nodePtr		a;
	nodePtr		b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition_u(head, &a, &b);
	ft_merge_sort_time_u(&a);
	ft_merge_sort_time_u(&b);
	*source = merge_list_u(a, b);
}
