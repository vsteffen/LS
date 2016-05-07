/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sortr_time_u.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:25:08 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/07 20:57:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		partition_ur(t_node_ptr head, t_node_ptr *front, t_node_ptr *back)
{
	t_node_ptr		fast;
	t_node_ptr		slow;

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

t_node_ptr	merge_list_ur(t_node_ptr a, t_node_ptr b)
{
	t_node_ptr merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((ft_strcmp(a->name, b->name) >= 0 && a->stat.st_atime
				== b->stat.st_atime) || a->stat.st_atime < b->stat.st_atime)
	{
		merged_list = a;
		merged_list->next = merge_list_ur(a->next, b);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_list_ur(a, b->next);
	}
	return (merged_list);
}

void		ft_merge_sortr_time_u(t_node_ptr *source)
{
	t_node_ptr		head;
	t_node_ptr		a;
	t_node_ptr		b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition_ur(head, &a, &b);
	ft_merge_sortr_time_u(&a);
	ft_merge_sortr_time_u(&b);
	*source = merge_list_ur(a, b);
}
