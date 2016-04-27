/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:23:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/27 22:36:37 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			type_file(t_list_ls *list, t_d *d)
{
	int				ret;

	if ((ret = lstat(list->path, &(list->stat))) == -1)
	{
		printf("1 - Don't have found \"%s\" in lst_new\n", list->path);
		if ((ret = lstat(list->path, &(list->stat))) == -1)
		{
 		ft_exit_prog("Don't have found file or directory in lst_new\n", FG_RED, 0);
		}	
	}
	if (S_ISREG(list->stat.st_mode))
		return ('-');
//		return (0);
	else if (S_ISDIR(list->stat.st_mode))
		return ('d');
//		return (1);
	else if (S_ISCHR(list->stat.st_mode))
		return ('c');
//		return (2);
	else if (S_ISBLK(list->stat.st_mode))
		return ('b');
//		return (3);
	else if (S_ISFIFO(list->stat.st_mode))
		return ('f');
//		return (4);
	else if (S_ISLNK(list->stat.st_mode))
		return ('l');
//		return (5);
	else if (S_ISSOCK(list->stat.st_mode))
		return ('s');
//		return (6);
	else
		return ('-');
//		return (0);
}

t_list_ls	*lst_new(char *d_name, char *path, t_d *d)
{
	t_list_ls		*list;
	int				ret;
	struct stat     sb;
	int				size_name;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		ft_exit_prog("Failed to initialize the linked list.\n", FG_RED, 0);
	list->name = d_name;
	list->len_name = ft_strlen(d_name);
	if (list->len_name > d->len_max)
		d->len_max = list->len_name;
	list->path = ft_pathjoin(path, ft_strdup(d_name));
	list->c_type = type_file(list, d);
	//	printf("list->type = %d /// list->name = %s /// list->stat.st_mtime = %ld\n", list->type, list->name, list->stat.st_mtime);
	d->total = d->total + list->stat.st_blocks;
//	printf("d->total = %lld\n", d->total);
//	printf("list->stat.st_blocks = %d\n", list->stat.st_blocks);
	list->next = NULL;
	return (list);
}

t_list_ls	*add_elem_4(t_list_ls *list, t_d *d, char *d_name, char *path)
{
	if (!list)
	{
		list = lst_new(d_name, path, d);
		return (list);
	}
	list->next = lst_new(ft_strdup(d_name), ft_strdup(path), d);
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

t_list_ls	*list_dir(t_list_ls *list, t_d *d, char *path, t_list_ls *lst_deb)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	int				no_null;	
//	t_list_ls 		*list_tmp;

	dir_s = NULL;
	dir_file = NULL;
	no_null = 0; // sert a savoir lst_deb ne va pas etre null et ne va pas segfault dans display
	if ((dir_s = opendir(path)) == NULL)
	{
		printf("ls: %s: Empty or permission denied ?", path);
		if (closedir(dir_s) == -1)
                ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
		d->denied = 1;
		return (NULL);
	}
	while ((dir_file = readdir(dir_s)) != NULL)
	{
		if (read_hidden(dir_file->d_name, d->tab_option[3]))
		{
			list = add_elem_4(list, d, dir_file->d_name, path);
			no_null++;
			break ;
		}
	}
	if (no_null == 0)
		return (NULL);
		lst_deb = list;
	while ((dir_file = readdir(dir_s)) != NULL)
		if (read_hidden(dir_file->d_name, d->tab_option[3]))
			list = add_elem_4(list, d, dir_file->d_name, path);

	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
	choose_sort(&lst_deb, d);
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

t_list_ls   *test_function(t_list_ls *list, t_d *d, char *path, t_list_ls *lst_deb)
{
	lst_deb = list_dir(list, d, path, lst_deb);
	return (lst_deb);
}

void	ls_core(t_d *d, char *path)//, int recur)
{
	t_list_ls   *list;
	t_list_ls   *lst_deb;
	char		*test;

	if (d->line_feed == 1)
		printf("\n");
	d->line_feed = 1;
	d->denied = 0;
	d->total = 0;
	lst_deb = list_dir(list, d, ft_strdup(path), lst_deb);
	display_list(lst_deb, d, ft_strdup(path));
//	exit(0);
	d->nb_display = 1;	
	while (lst_deb != NULL && d->tab_option[2] == 1)//&& recur == 1)
	{
		//	printf("lst_deb.name = %s ////  lst_deb->type = %d\n", lst_deb->name, lst_deb->type);
		test = ft_strdup(lst_deb->path);	
			if (lst_deb->c_type == 'd' && ft_strcmp("..", lst_deb->name) != 0 && ft_strcmp(".", lst_deb->name) != 0) //&& ft_strcmp(".git", lst_deb->name))
			ls_core(d, test);//lst_deb->path);//, recur);
		list = lst_deb;
		lst_deb = lst_deb->next;
		//free(list);
	}
//	exit(0);
}
