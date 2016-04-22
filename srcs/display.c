/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/22 22:22:44 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		verif_recur_one_arg(t_list_ls *list, t_d *d)
{
	t_list_ls	*list_tmp;

	list_tmp = list;
	while (list_tmp != NULL)
	{
		if (list_tmp->type == 1)
			return (1);
		list_tmp = list_tmp->next;
	}
	return (0);
}

void	display_list(t_list_ls *list, t_d *d, char *path)
{
	int		nb_name;
	int		tmp;

	d->len_max++;
	nb_name = d->width / d->len_max;
	if (d->tab_option[2] == 1 && d->nb_display == 1 && d->ok == 1)
		d->ok = verif_recur_one_arg(list, d);
	if (d->width < d->len_max || d->tab_option[6])
			return (display_list1(list, d, path));
	tmp = nb_name;
	if ((d->tab_option[2] == 1 && d->arg_true == 0) || d->arg_true > 1 || (d->tab_option[2] == 1 && d->ok == 0))
		printf("%s:\n", path);
	if (d->denied == 1)
		printf("ls: %s: Permission denied", path);
	while (list != NULL)
	{
		printf("%s", list->name);
		while (list->len_name < d->len_max)
		{
			printf(" ");
			list->len_name++;
		}
		list = list->next;
		tmp--;
		if (tmp == 0 && list != NULL)
		{
			printf("\n");
			tmp = nb_name;
		}
	}
	printf("\n");
	d->len_max = 0;
}

void	display_list1(t_list_ls *list, t_d *d, char *path)
{
	if (d->tab_option[2] == 1 && d->nb_display == 1 && d->ok == 1)
		d->ok = verif_recur_one_arg(list, d);
//	printf("d->ok =%d\n", d->ok);
	if ((d->tab_option[2] == 1 && d->arg_true == 0) || d->arg_true > 1 || (d->tab_option[2] == 1 && d->ok == 0))
		printf("%s:\n", path);
	if (d->denied == 1)
		printf("ls: %s: Permission denied", path);
	while (list != NULL)
	{
		//if (list->name[0] != '.')
		printf("%s\n", list->name);
		list = list->next;
	}
	//	printf("\n");
}

void	display_file(t_d *d, int arg_pos, t_argv *tab_arg)
{
	printf("%s\n\n", tab_arg[arg_pos].name);
}

void		tab_option_display(t_d *d)
{
	int		ac_var;

	ac_var = 0;
	while (ac_var != 7)
	{
		printf("d->tab_option[%d] = %d\n", ac_var, d->tab_option[ac_var]);
		ac_var++;
	}
}

void		av_display(int ac, char **av)
{
	int		ac_var;

	ac_var = 0;
	printf("\n");
	while (ac_var != ac)
	{
		printf("argv[%d] = %s\n", ac_var, av[ac_var]);
		ac_var++;
	}
}
