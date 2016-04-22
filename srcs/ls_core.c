/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:23:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/22 19:04:51 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list_ls	*lst_new(char *d_name, char *path)
{
	t_list_ls		*list;
	int				ret;
	struct stat     sb;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		ft_exit_prog("Failed to initialize the linked list.\n",FG_RED, 0);
	list->name = d_name;
	list->path = ft_pathjoin(path, d_name);
	if ((ret = lstat(list->path, &(list->stat))) == -1)
		ft_exit_prog("Don't have found file or directory in lst_new\n",FG_RED, 0);
	if (list->stat.st_mode & S_IFDIR)
		list->type = 1;
	else
		list->type = 0;
	//	printf("list->type = %d /// list->name = %s /// list->stat.st_mtime = %ld\n", list->type, list->name, list->stat.st_mtime);
	list->next = NULL;
	return (list);
}

t_list_ls	*add_elem_4(t_list_ls *list, t_d *d, char *d_name, char *path)
{
	if (!list)
	{
		list = lst_new(d_name, path);
		return (list);
	}
	list->next = lst_new(ft_strdup(d_name), ft_strdup(path));
	return (list->next);
}

t_list_ls	*add_elem_5(t_list_ls *list, t_d *d, char *d_name, char *path)
{
	t_list_ls	*tmp;
	//	printf("ADD ELEM 5\n");
	//	d->lst_length++;
	if (!list)
	{
		list = lst_new(d_name, path);
		return (list);
	}
	list->next = lst_new(ft_strdup(d_name), ft_strdup(path));
	return (list->next);
}


t_list_ls		*read_hidden2(t_list_ls *list, t_d *d, char *path, char *d_name)
{
	if (d->tab_option[3] == 1)
	{
		if (d_name[0] == '.')
			return (NULL);
		else
			return (add_elem_4(list, d, d_name, path));
	}
	else
		return (add_elem_4(list, d, d_name, path));
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



t_list_ls	*list_dir(t_list_ls *list, t_d *d, char *path, t_list_ls *lst_deb)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	//	t_list_ls 		*list_tmp;

	dir_s = NULL;
	dir_file = NULL;
	if ((dir_s = opendir(path)) == NULL)
	{
		//printf("ls: %s: Permission denied\n", path);
		d->denied = 1;
		return (NULL);
	}
	while ((dir_file = readdir(dir_s)) != NULL)
	{
		if (read_hidden(dir_file->d_name, d->tab_option[3]))
		{
			list = add_elem_4(list, d, dir_file->d_name, path);
			break ;
		}
	}
	lst_deb = list;
	while ((dir_file = readdir(dir_s)) != NULL)
		if (read_hidden(dir_file->d_name, d->tab_option[3]))
			list = add_elem_4(list, d, dir_file->d_name, path);

	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
	if (d->tab_option[5] == 0)
		ft_merge_sort_list(&lst_deb);
	else
		ft_merge_sortr_list(&lst_deb);
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

	if (d->line_feed == 1)
		printf("\n");
	d->line_feed = 1;
	d->denied = 0;
	lst_deb = list_dir(list, d, path, lst_deb);
	display_list(lst_deb, d, path);
	while (lst_deb != NULL && d->tab_option[2] == 1)//&& recur == 1)
		{
			//	printf("lst_deb.name = %s ////  lst_deb->type = %d\n", lst_deb->name, lst_deb->type);
			if (lst_deb->type == 1 && ft_strcmp("..", lst_deb->name) != 0 && ft_strcmp(".", lst_deb->name) != 0) //&& ft_strcmp(".git", lst_deb->name))
				ls_core(d, lst_deb->path);//, recur);
			lst_deb = lst_deb->next;
		}

	//if (!lst_deb)
	//	ft_lstdel(lst_deb, "next");
}
