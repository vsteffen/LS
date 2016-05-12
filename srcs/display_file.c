/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/12 15:39:03 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_elem_in_color_file_norme(char *color1, char *color2)
{
	ft_putstr(color1);
	ft_putstr(color2);
}

void	print_elem_in_color_file(t_stat stat, char *path, char c_type)
{
	if (c_type == '-')
	{
		if (stat.st_mode & S_IXUSR || stat.st_mode & S_IXGRP ||
				stat.st_mode & S_IXOTH)
			ft_putstr(FG_RED);
		else
			ft_putstr(CS_RESET);
	}
	else if (c_type == 'd')
		ft_putstr(FG_LCYAN);
	else if (c_type == 'c')
		print_elem_in_color_file_norme(FG_BLUE, BG_YELLOW);
	else if (c_type == 'b')
		print_elem_in_color_file_norme(FG_BLUE, BG_CYAN);
	else if (c_type == 'f')
		ft_putstr(FG_YELLOW);
	else if (c_type == 'l')
		ft_putstr(FG_MAGENTA);
	else if (c_type == 's')
		ft_putstr(FG_GREEN);
	ft_putstr(path);
	ft_putstr(CS_RESET);
}

char	type_file_file(t_stat *stat, char *path)
{
	int				ret;

	if ((ret = lstat(path, stat)) == -1)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path);
		ft_putstr(": Permission denied\n");
		return (-1);
	}
	if (S_ISREG(stat->st_mode))
		return ('-');
	else if (S_ISDIR(stat->st_mode))
		return ('d');
	else if (S_ISCHR(stat->st_mode))
		return ('c');
	else if (S_ISBLK(stat->st_mode))
		return ('b');
	else if (S_ISFIFO(stat->st_mode))
		return ('f');
	else if (S_ISLNK(stat->st_mode))
		return ('l');
	else if (S_ISSOCK(stat->st_mode))
		return ('s');
	else
		return ('-');
}

void	left_side_file(t_stat *stat)
{
	struct passwd	*pw;
	struct group	*gr;

	ft_putchar((stat->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((stat->st_mode & S_IWUSR) ? 'w' : '-');
	stick3(stat->st_mode);
	ft_putchar((stat->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((stat->st_mode & S_IWGRP) ? 'w' : '-');
	stick6(stat->st_mode);
	ft_putchar((stat->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((stat->st_mode & S_IWOTH) ? 'w' : '-');
	stick9(stat->st_mode);
	ft_putnbr(stat->st_nlink);
	pw = getpwuid(stat->st_uid);
	gr = getgrgid(stat->st_gid);
	ft_putchar(' ');
	if (pw != NULL)
		ft_putstr(pw->pw_name);
	else
		ft_putnbr(stat->st_uid);
	ft_putchar(' ');
	if (gr != NULL)
		ft_putstr(gr->gr_name);
	else
		ft_putnbr(stat->st_gid);
}

void	major_minor_file(t_stat *stat)
{
	ft_putchar(' ');
	ft_putnbr(MAJOR(stat->st_rdev));
	ft_putstr(", ");
	ft_putnbr(MINOR(stat->st_rdev));
	ft_putchar(' ');
}
