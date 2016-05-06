/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 18:22:59 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_elem_in_color(t_list_ls *list, t_d *d)
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

void	major_minor(t_list_ls *list, t_d *d)
{
	int		major;
	int		minor;

	ft_putchar(' ');
	ft_putnbr(MAJOR(list->stat.st_rdev));
	ft_putstr(", ");
	ft_putnbr(MINOR(list->stat.st_rdev));
	ft_putchar(' ');
}

void	left_side(t_list_ls *list, t_d *d)
{
	struct passwd	*pw;
	struct group	*gr;

	ft_putchar(list->c_type);
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

void	read_link(t_list_ls *list, t_d *d)
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

void	get_time(t_list_ls *list, t_d *d)
{
	char	*time_str;
	int		pos;

	time_str = ctime(&list->stat.st_mtime);
	pos = 4;
	while (pos < 10)
		get_time_print(time_str, &pos);
	if (list->stat.st_mtime > time(NULL) - 157788000)
	{
		while (pos < 16)
			get_time_print(time_str, &pos);
	}
	else
	{
		pos = 19;
		while (pos < 24)
			get_time_print(time_str, &pos);
	}
}

void	display_size(t_list_ls *list, t_d *d)
{
	char		type;
	float		nb;

	if (d->tab_option[10] == 0)
	{
		ft_putnbr(list->stat.st_size);
		ft_putchar(' ');
		return ;
	}
	else
	{
		nb = list->stat.st_size;
		type = human_function(&nb);
		ft_putnbr(nb);
		ft_putchar(type);
	}
}

void	long_list_format(t_list_ls *list, t_d *d, char *path)
{
	ft_putstr("total ");
	ft_putnbr(d->total);
	ft_putchar('\n');
	while (list != NULL)
	{
		left_side(list, d);
		ft_putchar(' ');
		if (list->c_type == 'c' || list->c_type == 'b')
			major_minor(list, d);
		else
		{
			display_size(list, d);
			ft_putchar(' ');
		}
		get_time(list, d);
		ft_putchar(' ');
		print_elem_in_color(list, d);
		read_link(list, d);
		ft_putchar('\n');
		list = list->next;
	}
	return ;
}

void	display_list_part_1(t_list_ls *list, t_d *d)
{
	print_elem_in_color(list, d);
	while (list->len_name < d->len_max)
	{
		ft_putchar(' ');
		list->len_name++;
	}
}

void	display_list_part_2(t_list_ls *list, t_d *d, int *tmp, int nb_name)
{
	(*tmp)--;
	if (*tmp == 0 && list != NULL)
	{
		ft_putchar('\n');
		*tmp = nb_name;
	}
}

void	display_choose(t_list_ls *list, t_d *d, char *path)
{
	if (d->nb_display == 1)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
	if (d->tab_option[4] == 1)
		return (long_list_format(list, d, path));
	if (d->width < d->len_max || d->tab_option[6])
		return (display_list_1(list, d, path));
	display_list(list, d, path);
}

void	display_list(t_list_ls *list, t_d *d, char *path)
{
	int		nb_name;
	int		tmp;

	if (d->denied == 1)
	{
		ft_putstr("ls: ");
		ft_putstr(path);
		ft_putstr(": Permission denied");
		return ;
	}
	d->len_max++;
	nb_name = d->width / d->len_max;
	tmp = nb_name;
	while (list != NULL)
	{
		display_list_part_1(list, d);
		list = list->next;
		display_list_part_2(list, d, &tmp, nb_name);
	}
	ft_putchar('\n');
	d->len_max = 0;
}

void	display_list_1(t_list_ls *list, t_d *d, char *path)
{
	if (d->denied == 1)
	{
		ft_putstr("ls: ");
		ft_putstr(path);
		ft_putstr(": Permission denied");
		return ;
	}
	while (list != NULL)
	{
		print_elem_in_color(list, d);
		ft_putchar('\n');
		list = list->next;
	}
}
