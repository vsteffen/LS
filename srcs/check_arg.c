/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:46:10 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/01 17:42:34 by vsteffen         ###   ########.fr       */
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

void		ft_qsort_tab_str(char **array, int first, int last)
{
	int		left;
	int		right;
	char	*pivot;

	left = first - 1;
	right = last + 1;
	pivot = array[first];
	if (first >= last)
		return ;
	while (1)
	{
		right--;
		while (ft_strcmp(array[right], pivot) > 0)
			right--;
		left++;
		while (ft_strcmp(array[left], pivot) < 0)
			left++;
		if (left < right)
			ft_swap_str(&array[left], &array[right]);
		else
			break ;
	}
	ft_qsort_tab_str(array, first, right);
	ft_qsort_tab_str(array, right + 1, last);
}

int			check_av(int ac, char **av, t_data *data)
{
	int		ac_var;

	if (ac == 1)
	{
		data->arg = 0;
		data->path = ".";
		return (0);
	}
	ac_var = 1;
	while (ac_var < ac)
	{
		check_arg(ac, av, data, &ac_var);
		ac_var++;
	}
	if (ft_strequ(data->path, "") == 1)
		data->path = ".";
	ft_qsort_tab_str(av, 1, (ac - 1));
	return (0);
}
