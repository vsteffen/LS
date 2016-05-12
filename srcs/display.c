/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 15:38:41 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_choose(t_list_ls *list, t_d *d, char *path)
{
	if (d->nb_display == 1)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
	if (d->tab_option[4] == 1)
		return (long_list_format(list, d));
	if (d->width < d->len_max || d->tab_option[6])
		return (display_list_1(list, d, path));
	display_list(list, d, path);
}

void	display_list(t_list_ls *list, t_d *d, char *path)
{
	int		nb_name;
	int		tmp;

	if (d->denied == 1)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path);
		ft_putstr(": Permission denied");
		return ;
	}
	d->len_max++;
	nb_name = d->width / d->len_max;
	tmp = nb_name;
	while (list != NULL)
	{
		display_list_part_1(list, d);
		list = list->next;
		display_list_part_2(list, &tmp, nb_name);
	}
	ft_putchar('\n');
	d->len_max = 0;
}

void	display_list_1(t_list_ls *list, t_d *d, char *path)
{
	if (d->denied == 1)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path);
		ft_putstr(": Permission denied");
		return ;
	}
	while (list != NULL)
	{
		print_elem_in_color(list);
		ft_putchar('\n');
		list = list->next;
	}
}
