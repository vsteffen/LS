/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:46:10 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/11 17:58:19 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			check_arg_spe(char arg_tmp, t_d *d)
{
	if (arg_tmp == '-')
		return (d->tab_option[0] = 1);
	else if (arg_tmp == 'L')
		return (d->tab_option[1] = 1);
	else if (arg_tmp == 'R')
		return (d->tab_option[2] = 1);
	else if (arg_tmp == 'a')
		return (d->tab_option[3] = 1);
	else if (arg_tmp == 'l')
		return (d->tab_option[4] = 1);
	else if (arg_tmp == 'r')
		return (d->tab_option[5] = 1);
	else if (arg_tmp == '1')
		return (d->tab_option[6] = 1);
	else
	{
		printf("ls: illegal option -- %c\n", arg_tmp);
		printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]");
		printf("[file ...]\n");
		exit(0);
	}
	return (0);
}

void		assign_name_value_arg(char **av, t_d *d, int *ac_var)
{
	d->tab_arg[d->i].name = av[*ac_var];
	d->i++;
	d->dash = 1;
}

void		assign_double_dash(t_d *d)
{
	d->dash = 1;
	d->nb_option++;
}

void		check_arg(char **av, t_d *d, int *ac_var)
{
	int		i;

	i = 1;
	if (d->dash == 1)
	{
		d->tab_arg[d->i].name = av[*ac_var];
		d->i++;
	}
	else if (ft_strcmp(av[*ac_var], "--") == 0 && d->dash == 0)
		assign_double_dash(d);
	else if (av[*ac_var][0] == '-')
	{
		if (av[*ac_var][1] == '\0' && *ac_var < d->ac)
			assign_name_value_arg(av, d, ac_var);
		else
			while (av[*ac_var][i] != '\0')
			{
				check_arg_spe(av[*ac_var][i], d);
				d->nb_option++;
				i++;
			}
	}
	else
		assign_name_value_arg(av, d, ac_var);
}

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
	while (tmp < d->i - 1)
	{
		d->tab_arg[tmp].name = d->tab_arg[tmp + 1].name;
		tmp++;
	}
	d->i--;
}

void		detect_arg_true(t_d *d)
{
	int				tmp;
	int				ret;
	struct stat		sb;

	tmp = 0;
	while (tmp != d->i)
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
	if (d->i > 1)
		qsort_tab_argv(d, 0, d->i - 1, 2);
}

int			check_av(int ac, char **av, t_d *d)
{
	int		ac_var;
	int		dash;

	if (ac == 1)
	{
		d->arg = 0;
		d->path = ".";
		return (0);
	}
	d->tab_arg = malloc(ac * sizeof(t_argv));
	ac_var = 1;
	dash = 0;
	while (ac_var < ac)
	{
		check_arg(av, d, &ac_var);
		ac_var++;
	}
	if (d->nb_option + 1 != ac)
	{
		detect_arg_true(d);
		printf("DETECT ARG TRUE PASS WITH SUCCESS\n");
	}
	printf("d->tab_arg[0].name = %s ////  d->tab_arg[1].name = %s ////  d->tab_arg[2].name = %s\n\n",
			d->tab_arg[0].name, d->tab_arg[1].name, d->tab_arg[2].name);
	return (0);
}
