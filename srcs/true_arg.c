/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:09:51 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/12 20:22:08 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		swap_tab_arg(t_d *d, int left, int right)
{
	int		tmp_dir;
	char	*tmp_name;

	tmp_name = d->tab_arg[left].name;
	d->tab_arg[left].name = d->tab_arg[right].name;
	d->tab_arg[right].name = tmp_name;
	tmp_dir = d->tab_arg[left].dir;
	d->tab_arg[left].dir = d->tab_arg[right].dir;
	d->tab_arg[right].dir = tmp_dir;
}

void		qsort_tab_argv(t_d *d, int first, int last, int p)
{
	int		r;

	d->l = first - 1;
	r = last + 1;
	d->pn = d->tab_arg[first].name;
	p = d->tab_arg[first].dir;
	if (first >= last)
		return ;
	while (1)
	{
		r--;
		while ((ft_strcmp(d->tab_arg[r].name, d->pn) > 0 &&
					d->tab_arg[r].dir <= p) || d->tab_arg[r].dir < p)
			r--;
		d->l++;
		while ((ft_strcmp(d->tab_arg[d->l].name, d->pn) < 0 &&
					d->tab_arg[d->l].dir >= p) || d->tab_arg[d->l].dir > p)
			d->l++;
		if (d->l < r)
			swap_tab_arg(d, d->l, r);
		else
			break ;
	}
	qsort_tab_argv(d, first, r, 2);
	qsort_tab_argv(d, r + 1, last, 2);
}

void		del_elem_tab_arg(t_d *d, int tmp)
{
	while (tmp < d->arg_true - 1)
	{
		d->tab_arg[tmp].name = d->tab_arg[tmp + 1].name;
		tmp++;
	}
	d->arg_true--;
}

void		detect_arg_true(t_d *d)
{
	int				tmp;
	int				ret;
	struct stat		sb;

	tmp = 0;
	while (tmp < d->arg_true - 1)
	{
		if ((ret = lstat(d->tab_arg[tmp].name, &sb)) == -1)
		{
			printf("ls: %s: No such file or directory\n",
					d->tab_arg[tmp].name);
			del_elem_tab_arg(d, tmp);
			continue ;
		}
		if (S_ISDIR(sb.st_mode))
			d->tab_arg[tmp].dir = 1;
		else
			d->tab_arg[tmp].dir = 0;
		tmp++;
	}
	if (d->arg_true > 1)
		qsort_tab_argv(d, 0, d->arg_true - 1, 2);
}
