/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/27 22:36:40 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
int		verif_recur_one_arg(t_list_ls *list, t_d *d)
{
	t_list_ls	*list_tmp;

	list_tmp = list;
	while (list_tmp != NULL)
	{
		if (list_tmp->type == 1)
			return (1);
		list_tmp = list_tmp->next;
	}
	return (0);
}
*/

void		print_elem_in_color(t_list_ls *list, t_d *d)
{
	if (list->c_type == '-')
	{
		if (list->stat.st_mode & S_IXUSR || list->stat.st_mode & S_IXGRP || list->stat.st_mode & S_IXOTH)
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


/*
static inline __int32_t  major_ls(__uint32_t _x)
{
	return (__int32_t)(((__uint32_t)_x >> 24) & 0xff);
}
		
static inline __int32_t  minor_ls(__uint32_t _x)
{
	return (__int32_t)((_x) & 0xffffff);
}
		
static inline dev_t  makedev_ls(__uint32_t _major_var, __uint32_t _minor_var)
{
    return (dev_t)(((_major_var) << 24) | (_minor_var));
}
*/



void	display_list(t_list_ls *list, t_d *d, char *path)
{
	int		nb_name;
	int		tmp;
	char		*time_str;
	int		white_sp;
	int		pos;
	struct passwd *pw;
	struct group  *gr;

	char buf[1024];
	ssize_t len;

	dev_t	make_dev;
	int		major;
	int		minor;


	printf("total %ld\n", d->total);

	while (list != NULL)
	{	
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
		printf(" %s", pw->pw_name);//getgrgid(list->stat.st_gid));//list->stat.st_gid);
		printf(" %s", gr->gr_name);//getgrgid(list->stat.st_gid));//list->stat.st_uid);
		if (list->c_type == 'c' || list->c_type == 'b')
		{	
	//		make_dev = makedev(list->stat.st_rdev, list->stat.st_rdev);//makedev_ls(major_ls(list->stat.st_rdev), minor_ls(list->stat.st_rdev)));
			printf(" %d,", MAJOR(list->stat.st_rdev));//MAKEDEV(MAJOR(list->stat.st_rdev), MINOR(list->stat.st_rdev)));
		}
		printf(" %lld ", list->stat.st_size);
		time_str = ctime(&list->stat.st_mtime);
		pos = 4;
		while (pos < 10)
		{
			printf("%c", time_str[pos]);
			pos++;
		}
		white_sp = 1;
		if (list->stat.st_mtime > time(NULL) - 157788000)
		{
			while (pos < 16)
			{
				printf("%c", time_str[pos]);
				pos++;
			}
		}
		else
		{
			pos = 19;
			while (pos < 24)
			{
				printf("%c", time_str[pos]);
				pos++;
			}
		}
		printf(" ");
//		printf("%c%c%c", time[4], time[5], time[6]);
		print_elem_in_color(list, d);
		if (list->c_type == 'l')
		{
			if ((len = readlink(list->path, buf, sizeof(buf)-1)) != -1)
				    buf[len] = '\0';
			printf(" -> %s", buf);
		}
		printf("\n");
		list = list->next;
	}
	return ;





	d->len_max++;
	nb_name = d->width / d->len_max;
//if (d->tab_option[2] == 1 && d->nb_display == 1 && d->ok == 1)
//		d->ok = verif_recur_one_arg(list, d);
	if (d->width < d->len_max || d->tab_option[6])
			return (display_list1(list, d, path));
	tmp = nb_name;
	if (d->nb_display == 1)
		printf("%s:\n", path);
	if (d->denied == 1)
		printf("ls: %s: Permission denied FUCK", path);
	while (list != NULL)
	{
		print_elem_in_color(list, d);
//		printf("%s", list->name);
		while (list->len_name < d->len_max)
		{
			printf(" ");
			list->len_name++;
		}
		list = list->next;
		tmp--;
		if (tmp == 0 && list != NULL)
		{
			printf("\n");
			tmp = nb_name;
		}
	}
	printf("\n");
	d->len_max = 0;
}

void	display_list1(t_list_ls *list, t_d *d, char *path)
{
//	if (d->tab_option[2] == 1 && d->nb_display == 1 && d->ok == 1)
//		d->ok = verif_recur_one_arg(list, d);
//	printf("d->ok =%d\n", d->ok);
	if (d->nb_display == 1)//(d->tab_option[2] == 1 && d->arg_true == 0) || d->arg_true > 1 || (d->tab_option[2] == 1 && d->ok == 0))
		printf("%s:\n", path);
	if (d->denied == 1)
		printf("ls: %s: Permission denied", path);
	while (list != NULL)
	{
		//if (list->name[0] != '.')
		printf("%s\n", list->name);
		list = list->next;
	}
	//	printf("\n");
}

void	display_file(t_d *d, int arg_pos, t_argv *tab_arg)
{
	printf("%s\n\n", tab_arg[arg_pos].name);
}

void		tab_option_display(t_d *d)
{
	int		ac_var;

	ac_var = 0;
	while (ac_var != 8)
	{
		printf("d->tab_option[%d] = %d\n", ac_var, d->tab_option[ac_var]);
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
