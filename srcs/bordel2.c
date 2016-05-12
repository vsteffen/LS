/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bordel2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 15:01:08 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 15:20:43 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	stick9(mode_t mode)
{
	if (mode & S_ISVTX && !(mode & S_IXOTH))
	{
		ft_putstr("T ");
		return ;
	}
	else if (mode & S_ISVTX && (mode & S_IXOTH))
	{
		ft_putstr("t ");
		return ;
	}
	else if (!(mode & S_ISVTX) && (mode & S_IXOTH))
	{
		ft_putstr("x ");
		return ;
	}
	else
	{
		ft_putstr("- ");
		return ;
	}
}

void	long_list_format_1(t_d *d)
{
	ft_putstr("total ");
	ft_putnbr(d->total);
	ft_putchar('\n');
}
