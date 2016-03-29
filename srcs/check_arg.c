/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:46:10 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/29 22:37:40 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			check_arg_spe(char arg_tmp, t_data *data)
{
	if (arg_tmp == 'L')
		return (data->tab_arg[0] = 1);
	else if (arg_tmp == 'R')
		return (data->tab_arg[1] = 1);
	else if (arg_tmp == 'a')
		return (data->tab_arg[2] = 1);
	else if (arg_tmp == 'l')
		return (data->tab_arg[3] = 1);
	else if (arg_tmp == 'r')
		return (data->tab_arg[4] = 1);
	else if (arg_tmp == '1')
		return (data->tab_arg[5] = 1);
	else
	{
		printf("ls: illegal option -- %c\n", arg_tmp);
		printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]");
		printf("[file ...]\n");
		exit(0);
	}
	return (0);
}

void		check_arg(int ac, char **av, t_data *data, int *ac_var)
{
	int		i;

	i = 1;
	if (av[*ac_var][0] == '-' && av[*ac_var][1] == '\0')
		data->path = ft_strjoin(data->path, "- ");
	else if (av[*ac_var][0] == '-')
	{
		while (av[*ac_var][i] != '\0')
		{
			check_arg_spe(av[*ac_var][i], data);
			i++;
		}
	}
	else
	{
		data->path = ft_strjoin(data->path, av[*ac_var]);
		data->path = ft_strjoin(data->path, " ");
	}
}

void		tab_arg_display(t_data *data)
{
	int		ac_var;

	ac_var = 0;
	while (ac_var != 6)
	{
		printf("data->tab_arg[%d] = %d\n", ac_var, data->tab_arg[ac_var]);
		ac_var++;
	}
}

void		ft_swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			arg_reorder(int ac, char **av, t_data *data)
{
	unsigned int	left;
	unsigned int	right;
	unsigned int	tp;
	unsigned char	*tmp;
	unsigned int	length;

	while (1)
	{
		left = 1;
		right = ac;
		while (left != right)
		{
			if (left > right)
			{
				tp = right;
				left = right;
				right = tp;
				left++;
			}
			right++;
		}
		if (right == 1)
			return (0);
	}
}

int			check_av(int ac, char **av, t_data *data)
{
	int		ac_var;
	char	*value1 = "POUETTE";
	char	*value2 = "CACA";
	int		nb1 = 2;
	int		nb2 = 3;
	int		*p1 = &nb1;
	int 	*p2 = &nb2;


	if (ac == 1)
	{
		data->arg = 0;
		data->path = ".";
		return (0);
	}
	ac_var = 1;
//	arg_reorder(ac, av, data);
	while (ac_var < ac)
	{
		check_arg(ac, av, data, &ac_var);
		ac_var++;
	}
	if (ft_strequ(data->path, "") == 1)
		data->path = ".";
	return (0);
}
