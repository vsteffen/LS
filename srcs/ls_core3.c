/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 19:23:46 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/07 19:26:40 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		choose_sort2(t_list_ls **lst_deb, t_d *d)
{
	if (d->tab_option[5] == 0)
	{
		if (d->tab_option[8] == 1)
		{
			ft_merge_sort_time_u(lst_deb);
			return ;
		}
		else
		{
			ft_merge_sort_size(lst_deb);
			return ;
		}
	}
	else
	{
		if (d->tab_option[8] == 1)
		{
			ft_merge_sortr_time_u(lst_deb);
			return ;
		}
		else
			ft_merge_sortr_size(lst_deb);
	}
}

void		*list_dir2(t_d *d, char *path)
{
	ft_putstr("ls:");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putchar('\n');
	d->denied = 1;
	return (NULL);
}

void		*list_dir3(t_d *d)
{
	d->denied = 1;
	return (NULL);
}

void		list_dir4(DIR **dir_s, struct dirent **dir_file, int *no_null)
{
	*dir_s = NULL;
	*dir_file = NULL;
	*no_null = 0;
}

void		choose_sort_master(t_list_ls **lst_deb, t_d *d)
{
	if (d->tab_option[8] == 0 && d->tab_option[9] == 0)
		choose_sort(lst_deb, d);
	else
		choose_sort2(lst_deb, d);
}
