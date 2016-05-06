/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bordel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 18:35:08 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 19:10:59 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			check_arg_spe2(char arg_tmp, t_d *d)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(arg_tmp);
	ft_putstr("\nusage: ls [-LRSahlrtu1]");
	ft_putstr(" [file ...]\n");
	exit(0);
	return (0);
}

void		detect_arg_true2(t_d *d, int tmp)
{
	ft_putstr("ls: ");
	ft_putstr(d->tab_arg[tmp].name);
	ft_putstr(": No such file or directory\n");
	del_elem_tab_arg(d, tmp);
}
