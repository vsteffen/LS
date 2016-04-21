/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 18:09:51 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/21 16:48:35 by vsteffen         ###   ########.fr       */
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

void		qsort_array(t_d *d, int first, int last, int pd)
{
	int		right;

	d->left = first - 1;
	right = last + 1;
	pd = d->tab_arg[first].dir;
	d->pn = d->tab_arg[first].name;
	if (first >= last)
		return ;
	while (1)
	{
		right--;
		while (d->tab_arg[right].dir > pd || (ft_strcmp(d->tab_arg[right].name,
						d->pn) > 0 && d->tab_arg[right].dir == pd))
			right--;
		d->left++;
		while (d->tab_arg[d->left].dir < pd || (ft_strcmp(d->tab_arg[d->left].
						name, d->pn) < 0 && d->tab_arg[d->left].dir == pd))
			d->left++;
		if (d->left < right)
			swap_tab_arg(d, d->left, right);
		else
			break ;
	}
	qsort_array(d, first, right, 1);
	qsort_array(d, right + 1, last, 1);
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

void		detect_arg_true(t_d *d, int ret)
{
	int				tmp;
	struct stat		sb;

	tmp = 0;
	while (tmp < d->arg_true)
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
	{
		qsort_array(d, 0, d->arg_true - 1, 1);
		if (d->tab_option[5] == 1)
			revert_array(d);
	}
}
