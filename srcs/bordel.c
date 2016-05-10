/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bordel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 18:35:08 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/10 19:13:35 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			check_arg_spe2(char arg_tmp)
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

int			proper_link2(t_d *d, int tmp)
{

	if ((d->tab_arg[tmp].name[0] == '/' && d->tab_option[4] == 0)
			|| d->tab_option[1] == 1)
	{
		d->tab_arg[tmp].dir = 1;
		return (1);
	}
	return (0);
}

void    stick3(mode_t mode)
{
	if (mode & S_ISUID && !(mode & S_IXUSR))
	{
		ft_putchar('S');
		return ;
	}
	else if (mode & S_ISUID && (mode & S_IXUSR))
	{
		ft_putchar('s');
		return ;
	}
	else if (!(mode & S_ISUID) && (mode & S_IXUSR))
	{
		ft_putchar('x');
		return ;
	}
	else
	{
		ft_putchar('-');
		return ;
	}
}

void    stick6(mode_t mode)
{
	if (mode & S_ISGID && !(mode & S_IXGRP))
	{
		ft_putchar('S');
		return ;
	}
	else if (mode & S_ISGID && (mode & S_IXGRP))
	{
		ft_putchar('s');
		return ;
	}
	else if (!(mode & S_ISGID) && (mode & S_IXGRP))
	{
		ft_putchar('x');
		return ;
	}
	else
	{
		ft_putchar('-');
		return ;
	}
}

void    stick9(mode_t mode)
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
