/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:23:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 19:32:15 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			type_file(t_list_ls *list, t_d *d)
{
	int				ret;

	if ((ret = lstat(list->path, &(list->stat))) == -1)
	{
		ft_putstr("ls: ");
		ft_putstr(list->name);
		ft_putstr(": Permission denied\n");
		return (-1);
	}
	if (S_ISREG(list->stat.st_mode))
		return ('-');
	else if (S_ISDIR(list->stat.st_mode))
		return ('d');
	else if (S_ISCHR(list->stat.st_mode))
		return ('c');
	else if (S_ISBLK(list->stat.st_mode))
		return ('b');
	else if (S_ISFIFO(list->stat.st_mode))
		return ('f');
	else if (S_ISLNK(list->stat.st_mode))
		return ('l');
	else if (S_ISSOCK(list->stat.st_mode))
		return ('s');
	else
		return ('-');
}

t_list_ls	*lst_new(char *d_name, char *path, t_d *d)
{
	t_list_ls		*list;
	int				ret;
	struct stat		sb;
	int				size_name;
	int				type;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		ft_exit_prog("Failed to initialize the linked list.\n", FG_RED, 0);
	list->name = d_name;
	list->len_name = ft_strlen(d_name);
	if (list->len_name > d->len_max)
		d->len_max = list->len_name;
	list->path = ft_pathjoin(path, d_name);
	type = type_file(list, d);
	if (type == -1)
		return (NULL);
	list->c_type = type;
	d->total = d->total + list->stat.st_blocks;
	list->next = NULL;
	return (list);
}

t_list_ls	*add_elem_4(t_list_ls *list, t_d *d, char *d_name, char *path)
{
	if (!list)
	{
		list = lst_new(ft_strdup(d_name), path, d);
		return (list);
	}
	list->next = lst_new(ft_strdup(d_name), path, d);
	return (list->next);
}

int			read_hidden(char *d_name, int status)
{
	if (status == 0)
	{
		if (d_name[0] == '.')
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

void		choose_sort(t_list_ls **lst_deb, t_d *d)
{
	if (d->tab_option[5] == 0)
	{
		if (d->tab_option[7] == 0)
		{
			ft_merge_sort_list(lst_deb);
			return ;
		}
		else
		{
			ft_merge_sort_time(lst_deb);
			return ;
		}
	}
	else
	{
		if (d->tab_option[7] == 0)
		{
			ft_merge_sortr_list(lst_deb);
			return ;
		}
		else
			ft_merge_sortr_time(lst_deb);
	}
}

void		choose_sort2(t_list_ls **lst_deb, t_d *d)
{
	if (d->tab_option[5] == 0)
	{
		if (d->tab_option[8] == 1)
		{
			ft_merge_sort_time_u(lst_deb);
			return ;
		}
		else
		{
			ft_merge_sort_size(lst_deb);
			return ;
		}
	}
	else
	{
		if (d->tab_option[8] == 1)
		{
			ft_merge_sortr_time_u(lst_deb);
			return ;
		}
		else
			ft_merge_sortr_size(lst_deb);
	}
}

t_list_ls	*list_dir(t_list_ls *list, t_d *d, char *path, t_list_ls *lst_deb)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	int				no_null;

	dir_s = NULL;
	dir_file = NULL;
	no_null = 0;
	if ((dir_s = opendir(path)) == NULL)
	{
		ft_putstr("ls:");
		ft_putstr(path);
		ft_putstr(": ");
		ft_putstr(strerror(errno));
		ft_putchar('\n');
		d->denied = 1;
		return (NULL);
	}
	while ((dir_file = readdir(dir_s)) != NULL)
		if (read_hidden(dir_file->d_name, d->tab_option[3]))
		{
			list = add_elem_4(list, d, dir_file->d_name, path);
			if (list == NULL)
			{
				d->denied = 1;
				return (NULL);
			}
			if (no_null == 0)
				lst_deb = list;
			no_null++;
		}
	if (no_null == 0)
	{
		if (closedir(dir_s) == -1)
			ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
	}
	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
	if (d->tab_option[8] == 0 && d->tab_option[9] == 0)
		choose_sort(&lst_deb, d);
	else
		choose_sort2(&lst_deb, d);
	return (lst_deb);
}

char	*ft_pathjoin(char const *s1, char const *s2)
{
	size_t	len_t;
	size_t	len_s1;
	char	*str_null;

	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_t = len_s1 + ft_strlen(s2) + 1;
		if (s1[0] == '/' && len_s1 == 1)
		{
			str_null = ft_strnew(len_t - 1);
			str_null[0] = '/';
			str_null = ft_strcat(str_null, s2);
			return (str_null);
		}
		str_null = ft_strnew(len_t);
		if (str_null)
		{
			str_null = ft_strcpy(str_null, s1);
			str_null[len_s1] = '/';
			str_null = ft_strcat(str_null, s2);
			return (str_null);
		}
	}
	return (NULL);
}

void	free_element(t_list_ls *list)
{
	t_list_ls	*tmp;

	while (list != NULL)
	{
		free(list->name);
		free(list->path);
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	ls_core2(t_d *d)
{
	if (d->line_feed == 1)
		ft_putchar('\n');
	d->line_feed = 1;
	d->total = 0;
}

void	ls_core3(t_d *d, t_list_ls *lst_deb)
{
	d->denied = 0;
	free_element(lst_deb);
	return ;
}

void	ls_core(t_d *d, char *path)
{
	t_list_ls	*list;
	t_list_ls	*lst_deb;
	char		*test;

	list = NULL;
	ls_core2(d);
	lst_deb = list_dir(list, d, path, lst_deb);
	if (d->denied == 0)
		display_choose(lst_deb, d, path);
	else
		return (ls_core3(d, lst_deb));
	d->nb_display = 1;
	list = lst_deb;
	while (list != NULL && d->tab_option[2] == 1)
	{
		if (list->c_type == 'd' && ft_strcmp("..", list->name) != 0
				&& ft_strcmp(".", list->name) != 0)
		{
			test = ft_strdup(list->path);
			ls_core(d, test);
			free(test);
		}
		list = list->next;
	}
	free_element(lst_deb);
}
