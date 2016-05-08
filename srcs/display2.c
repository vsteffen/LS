/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 18:40:32 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/08 17:11:28 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_elem_in_color(t_list_ls *list)
{
	if (list->c_type == '-')
	{
		if (list->stat.st_mode & S_IXUSR || list->stat.st_mode & S_IXGRP ||
				list->stat.st_mode & S_IXOTH)
			ft_putstr(FG_RED);
		else
			ft_putstr(CS_RESET);
	}
	else if (list->c_type == 'd')
		ft_putstr(FG_LCYAN);
	else if (list->c_type == 'c')
		print_elem_in_color_file_norme(FG_BLUE, BG_YELLOW);
	else if (list->c_type == 'b')
		print_elem_in_color_file_norme(FG_BLUE, BG_CYAN);
	else if (list->c_type == 'f')
		ft_putstr(FG_YELLOW);
	else if (list->c_type == 'l')
		ft_putstr(FG_MAGENTA);
	else if (list->c_type == 's')
		ft_putstr(FG_GREEN);
	ft_putstr(list->name);
	ft_putstr(CS_RESET);
}

void	major_minor(t_list_ls *list)
{
	ft_putchar(' ');
	ft_putnbr(MAJOR(list->stat.st_rdev));
	ft_putstr(", ");
	ft_putnbr(MINOR(list->stat.st_rdev));
	ft_putchar(' ');
}

void	left_side(t_list_ls *list)
{
	struct passwd	*pw;
	struct group	*gr;

	ft_putchar((list->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((list->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((list->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((list->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((list->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((list->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((list->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((list->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putstr((list->stat.st_mode & S_IXOTH) ? "x " : "- ");
	ft_putnbr(list->stat.st_nlink);
	pw = getpwuid(list->stat.st_uid);
	gr = getgrgid(list->stat.st_gid);
	ft_putchar(' ');
	if (pw != NULL)
		ft_putstr(pw->pw_name);
	else
		ft_putnbr(list->stat.st_uid);
	ft_putchar(' ');
	if (gr != NULL)
		ft_putstr(gr->gr_name);
	else
		ft_putnbr(list->stat.st_gid);
}

void	read_link(t_list_ls *list)
{
	char		buf[1024];
	ssize_t		len;

	if (list->c_type == 'l')
	{
		if ((len = readlink(list->path, buf, sizeof(buf) - 1)) != -1)
			buf[len] = '\0';
		ft_putstr(" -> ");
		ft_putstr(buf);
	}
}

void	get_time_print(char *time_str, int *pos)
{
	ft_putchar(time_str[*(pos)]);
	(*pos)++;
}
