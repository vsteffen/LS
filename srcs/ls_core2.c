/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 19:22:02 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 15:39:27 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			type_file(t_list_ls *list)
{
	int				ret;

	if ((ret = lstat(list->path, &(list->stat))) == -1)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(list->name);
		ft_putstr(": Permission denied\n");
		return (-1);
	}
	if (S_ISREG(list->stat.st_mode))
		return ('-');
	else if (S_ISDIR(list->stat.st_mode))
		return ('d');
	else if (S_ISCHR(list->stat.st_mode))
		return ('c');
	else if (S_ISBLK(list->stat.st_mode))
		return ('b');
	else if (S_ISFIFO(list->stat.st_mode))
		return ('f');
	else if (S_ISLNK(list->stat.st_mode))
		return ('l');
	else if (S_ISSOCK(list->stat.st_mode))
		return ('s');
	else
		return ('-');
}

t_list_ls	*lst_new(char *d_name, char *path, t_d *d)
{
	t_list_ls		*list;
	int				type;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		ft_exit_prog("Failed to initialize the linked list.\n", FG_RED, 0);
	list->name = d_name;
	list->len_name = ft_strlen(d_name);
	if (list->len_name > d->len_max)
		d->len_max = list->len_name;
	list->path = ft_pathjoin(path, d_name);
	type = type_file(list);
	if (type == -1)
		return (NULL);
	list->c_type = type;
	d->total = d->total + list->stat.st_blocks;
	list->next = NULL;
	return (list);
}

t_list_ls	*add_elem_4(t_list_ls *list, t_d *d, char *d_name, char *path)
{
	if (!list)
	{
		list = lst_new(ft_strdup(d_name), path, d);
		return (list);
	}
	list->next = lst_new(ft_strdup(d_name), path, d);
	return (list->next);
}

int			read_hidden(char *d_name, int status)
{
	if (status == 0)
	{
		if (d_name[0] == '.')
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

void		choose_sort(t_list_ls **lst_deb, t_d *d)
{
	if (d->tab_option[5] == 0)
	{
		if (d->tab_option[7] == 0)
		{
			ft_merge_sort_list(lst_deb);
			return ;
		}
		else
		{
			ft_merge_sort_time(lst_deb);
			return ;
		}
	}
	else
	{
		if (d->tab_option[7] == 0)
		{
			ft_merge_sortr_list(lst_deb);
			return ;
		}
		else
			ft_merge_sortr_time(lst_deb);
	}
}
