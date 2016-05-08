/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:23:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/08 17:03:05 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_core3(t_d *d, t_list_ls *lst_deb)
{
	d->denied = 0;
	free_element(lst_deb);
	return ;
}

void		ls_core(t_d *d, char *path)
{
	t_list_ls	*list;
	t_list_ls	*lst_deb;
	char		*test;

	list = NULL;
	ls_core2(d);
	lst_deb = list_dir(list, d, path, NULL);
	if (d->denied == 0)
		display_choose(lst_deb, d, path);
	else
		return (ls_core3(d, lst_deb));
	d->nb_display = 1;
	list = lst_deb;
	while (list != NULL && d->tab_option[2] == 1)
	{
		if (list->c_type == 'd' && ft_strcmp("..", list->name) != 0
				&& ft_strcmp(".", list->name) != 0)
		{
			test = ft_strdup(list->path);
			ls_core(d, test);
			free(test);
		}
		list = list->next;
	}
	free_element(lst_deb);
}
