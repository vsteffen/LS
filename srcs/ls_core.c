/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:23:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/20 21:46:18 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void		list_dir(t_list_ls *list, t_d *d, char *path)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	t_list_ls 		*list_tmp;

	if ((dir_s = opendir(path)) == NULL)
	{
		printf("ls: %s: Permission denied\n", path);
		return ;
	}
	dir_s = NULL;
	dir_file = NULL;
	if ((dir_file = readdir(dir_s)) != NULL)
		d->lst_end = add_elem_4(d->lst_end, d, dir_file->d_name);
	while ((dir_file = readdir(dir_s)) != NULL)
		d->lst_end = add_elem_5(d->lst_end, d, dir_file->d_name);
	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n",FG_RED, 0);
	if (d->tab_option[5] == 0)
		ft_merge_sort_list(&d->lst_deb);
	else
		ft_merge_sortr_list(&d->lst_deb);
}

char	*ft_pathjoin(char const *s1, char const *s2)
{
	size_t	len_t;
	size_t	len_s1;
	char	*str_null;

	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_t = len_s1 + ft_strlen(s2);
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

void	ls_core(t_d *d, char *path)
{
	t_list_ls   *list;
	t_list_ls   *lst_deb;

	lst_deb = list;
	list_dir(list, d, path);
	display_list(lst_deb);
	while (list != NULL)
	{
		if (list->dir == 1 && ft_strcmp("..", list->name) != 0 && ft_strcmp(".", list->name) != 0)
			ls_core(d, ft_pathjoin(path, list->name));
		list = list->next;
	}
	if (!lst_deb)
		ft_lstdel(lst_deb);
}
