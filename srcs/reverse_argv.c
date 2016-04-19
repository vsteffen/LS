/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:39:53 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/19 15:43:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			revert_file(t_d *d)
{
	int		deb;
	int		end;
	int		tmp;

	deb = 0;
	end = 0;
	while (d->tab_arg[end].dir == 0 && end < d->arg_true)
		end++;
	if (end > deb)
		end--;
	tmp = end;
	if (end > deb)
	{
		while (end > deb)
		{
			swap_tab_arg(d, deb, end);
			deb++;
			end--;
		}
	}
	return (tmp + 1);
}

void		revert_array(t_d *d)
{
	int		file_end;
	int		end_array;

	file_end = revert_file(d);
	if (file_end >= d->arg_true)
		return ;
	end_array = d->arg_true - 1;
	while (end_array > file_end)
	{
		swap_tab_arg(d, file_end, end_array);
		file_end++;
		end_array--;
	}
}
