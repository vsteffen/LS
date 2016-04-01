/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/01 21:51:24 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_list(t_list_ls *list)
{
	printf("\n");
	while (list != NULL)
	{
		printf("Nom = %s\n", list->name);
		list = list->next;
	}
	printf("\nEnd of linked list\n");
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
