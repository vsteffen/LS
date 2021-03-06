/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:46:10 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 15:36:33 by vsteffen         ###   ########.fr       */
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
	else if (arg_tmp == 't')
		return (d->tab_option[7] = 1);
	else if (arg_tmp == 'u')
		return (d->tab_option[8] = 1);
	else if (arg_tmp == 'S')
		return (d->tab_option[9] = 1);
	else if (arg_tmp == 'h')
		return (d->tab_option[10] = 1);
	return (check_arg_spe2(arg_tmp));
}

void		assign_name_value_arg(char **av, t_d *d, int *ac_var)
{
	d->tab_arg[d->arg_true].name = av[*ac_var];
	d->arg_true++;
	d->dash = 1;
}

void		assign_double_dash(t_d *d)
{
	d->dash = 1;
	d->nb_option++;
}

void		check_arg(char **av, t_d *d, int *ac_var, int i)
{
	i = 1;
	if (d->dash == 1)
	{
		d->tab_arg[d->arg_true].name = av[*ac_var];
		d->arg_true++;
	}
	else if (ft_strcmp(av[*ac_var], "--") == 0 && d->dash == 0)
		assign_double_dash(d);
	else if (av[*ac_var][0] == '-')
	{
		if (av[*ac_var][1] == '\0' && *ac_var < d->ac)
			assign_name_value_arg(av, d, ac_var);
		else
		{
			while (av[*ac_var][i] != '\0')
			{
				check_arg_spe(av[*ac_var][i], d);
				i++;
			}
			d->nb_option++;
		}
	}
	else
		assign_name_value_arg(av, d, ac_var);
}

int			check_av(int ac, char **av, t_d *d)
{
	int		ac_var;
	int		dash;

	if (ac == 1)
		return (0);
	if ((d->tab_arg = malloc(ac * sizeof(t_argv))) == NULL)
		ft_exit_prog("Fail to malloc d->tab_arg\n", FG_RED, 0);
	ac_var = 1;
	dash = 0;
	while (ac_var < ac)
	{
		check_arg(av, d, &ac_var, 0);
		if (av[ac_var][0] == '\0')
			ft_exit_prog("ft_ls: fts_open: No such file or directory\n"
					, CS_RESET, 1);
		ac_var++;
	}
	if (d->nb_option + 1 != ac)
	{
		detect_arg_true(d, 0);
		d->arg = 1;
		if (d->arg_true == 0)
			exit(0);
	}
	return (0);
}
