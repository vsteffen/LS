/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sortr_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:47:32 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/07 20:56:44 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		partition_sr(t_node_ptr head, t_node_ptr *front, t_node_ptr *back)
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

t_node_ptr	merge_list_sr(t_node_ptr a, t_node_ptr b)
{
	t_node_ptr merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((ft_strcmp(a->name, b->name) >= 0 && a->stat.st_size
				== b->stat.st_size) || a->stat.st_size < b->stat.st_size)
	{
		merged_list = a;
		merged_list->next = merge_list_sr(a->next, b);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_list_sr(a, b->next);
	}
	return (merged_list);
}

void		ft_merge_sortr_size(t_node_ptr *source)
{
	t_node_ptr		head;
	t_node_ptr		a;
	t_node_ptr		b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition_sr(head, &a, &b);
	ft_merge_sortr_size(&a);
	ft_merge_sortr_size(&b);
	*source = merge_list_sr(a, b);
}
