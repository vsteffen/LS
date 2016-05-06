/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 18:41:51 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 18:42:30 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_time(t_list_ls *list, t_d *d)
{
	char	*time_str;
	int		pos;

	time_str = ctime(&list->stat.st_mtime);
	pos = 4;
	while (pos < 10)
		get_time_print(time_str, &pos);
	if (list->stat.st_mtime > time(NULL) - 157788000)
	{
		while (pos < 16)
			get_time_print(time_str, &pos);
	}
	else
	{
		pos = 19;
		while (pos < 24)
			get_time_print(time_str, &pos);
	}
}

void	display_size(t_list_ls *list, t_d *d)
{
	char		type;
	float		nb;

	if (d->tab_option[10] == 0)
	{
		ft_putnbr(list->stat.st_size);
		ft_putchar(' ');
		return ;
	}
	else
	{
		nb = list->stat.st_size;
		type = human_function(&nb);
		ft_putnbr(nb);
		ft_putchar(type);
	}
}

void	long_list_format(t_list_ls *list, t_d *d, char *path)
{
	ft_putstr("total ");
	ft_putnbr(d->total);
	ft_putchar('\n');
	while (list != NULL)
	{
		ft_putchar(list->c_type);
		left_side(list, d);
		ft_putchar(' ');
		if (list->c_type == 'c' || list->c_type == 'b')
			major_minor(list, d);
		else
		{
			display_size(list, d);
			ft_putchar(' ');
		}
		get_time(list, d);
		ft_putchar(' ');
		print_elem_in_color(list, d);
		read_link(list, d);
		ft_putchar('\n');
		list = list->next;
	}
	return ;
}

void	display_list_part_1(t_list_ls *list, t_d *d)
{
	print_elem_in_color(list, d);
	while (list->len_name < d->len_max)
	{
		ft_putchar(' ');
		list->len_name++;
	}
}

void	display_list_part_2(t_list_ls *list, t_d *d, int *tmp, int nb_name)
{
	(*tmp)--;
	if (*tmp == 0 && list != NULL)
	{
		ft_putchar('\n');
		*tmp = nb_name;
	}
}
