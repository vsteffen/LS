/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/02 21:38:25 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_elem_in_color(t_list_ls *list, t_d *d)
{
	if (list->c_type == '-')
	{
		if (list->stat.st_mode & S_IXUSR || list->stat.st_mode & S_IXGRP ||
				list->stat.st_mode & S_IXOTH)
			printf(FG_RED);
		else
			printf(CS_RESET);
	}
	else if (list->c_type == 'd')
		printf(FG_LCYAN);
	else if (list->c_type == 'c')
		printf("%s%s", FG_BLUE, BG_YELLOW);
	else if (list->c_type == 'b')
		printf("%s%s", FG_BLUE, BG_CYAN);
	else if (list->c_type == 'f')
		printf(FG_YELLOW);
	else if (list->c_type == 'l')
		printf(FG_MAGENTA);
	else if (list->c_type == 's')
		printf(FG_GREEN);
	printf("%s", list->name);
	printf(CS_RESET);
}

void	major_minor(t_list_ls *list, t_d *d)
{
	int		major;
	int		minor;

	printf(" %d, %d ", MAJOR(list->stat.st_rdev), MINOR(list->stat.st_rdev));
}

void	left_side(t_list_ls *list, t_d *d)
{
	struct passwd	*pw;
	struct group	*gr;

	printf("%c", list->c_type);
	printf((list->stat.st_mode & S_IRUSR) ? "r" : "-");
	printf((list->stat.st_mode & S_IWUSR) ? "w" : "-");
	printf((list->stat.st_mode & S_IXUSR) ? "x" : "-");
	printf((list->stat.st_mode & S_IRGRP) ? "r" : "-");
	printf((list->stat.st_mode & S_IWGRP) ? "w" : "-");
	printf((list->stat.st_mode & S_IXGRP) ? "x" : "-");
	printf((list->stat.st_mode & S_IROTH) ? "r" : "-");
	printf((list->stat.st_mode & S_IWOTH) ? "w" : "-");
	printf((list->stat.st_mode & S_IXOTH) ? "x" : "-");
	printf(" %d", list->stat.st_nlink);
	pw = getpwuid(list->stat.st_uid);
	gr = getgrgid(list->stat.st_gid);
	printf(" %s", pw->pw_name);
	printf(" %s", gr->gr_name);
}

void	read_link(t_list_ls *list, t_d *d)
{
	char		buf[1024];
	ssize_t		len;

	if (list->c_type == 'l')
	{
		if ((len = readlink(list->path, buf, sizeof(buf) - 1)) != -1)
			buf[len] = '\0';
		printf(" -> %s", buf);
	}
}

void	get_time_print(char *time_str, int *pos)
{
	printf("%c", time_str[*(pos)]);
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

void	long_list_format(t_list_ls *list, t_d *d, char *path)
{
	printf("total %ld\n", d->total);
	while (list != NULL)
	{
		left_side(list, d);
		if (list->c_type == 'c' || list->c_type == 'b')
			major_minor(list, d);
		else
			printf(" %lld ", list->stat.st_size);
		get_time(list, d);
		printf(" ");
		print_elem_in_color(list, d);
		read_link(list, d);
		printf("\n");
		list = list->next;
	}
	return ;
}

void	display_list_part_1(t_list_ls *list, t_d *d)
{
	print_elem_in_color(list, d);
	while (list->len_name < d->len_max)
	{
		printf(" ");
		list->len_name++;
	}
}

void	display_list_part_2(t_list_ls *list, t_d *d, int *tmp, int nb_name)
{
	(*tmp)--;
	if (*tmp == 0 && list != NULL)
	{
		printf("\n");
		*tmp = nb_name;
	}
}

void	display_choose(t_list_ls *list, t_d *d, char *path)
{
	if (d->nb_display == 1)
		printf("%s:\n", path);
//	if (list != NULL)
//		printf("\n");
//	else
//		return ;
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
		printf("ls: %s: Permission denied FUCK", path);
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
	printf("\n");
	d->len_max = 0;
}

void	display_list_1(t_list_ls *list, t_d *d, char *path)
{
	if (d->denied == 1)
	{
		printf("ls: %s: Permission denied FUCK", path);
		return ;
	}
	while (list != NULL)
	{
		//printf("list->stat.st_mtime = %ld\t", list->stat.st_mtime);
		print_elem_in_color(list, d);
		printf("\n");
		list = list->next;
	}
}

void	display_file(t_d *d, int arg_pos, t_argv *tab_arg)
{
	printf("%s\n\n", tab_arg[arg_pos].name);
}

void	tab_option_display(t_d *d)
{
	int		ac_var;

	ac_var = 0;
	while (ac_var != 8)
	{
		printf("d->tab_option[%d] = %d\n", ac_var, d->tab_option[ac_var]);
		ac_var++;
	}
}

void	av_display(int ac, char **av)
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
