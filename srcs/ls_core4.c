/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 19:24:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/07 19:26:10 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_dir5(DIR *dir_s)
{
	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", FG_RED, 0);
}

t_list_ls	*list_dir(t_list_ls *list, t_d *d, char *path, t_list_ls *lst_deb)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	int				no_null;

	list_dir4(&dir_s, &dir_file, &no_null);
	if ((dir_s = opendir(path)) == NULL)
		return (list_dir2(d, path));
	while ((dir_file = readdir(dir_s)) != NULL)
		if (read_hidden(dir_file->d_name, d->tab_option[3]))
		{
			list = add_elem_4(list, d, dir_file->d_name, path);
			if (list == NULL)
				return (list_dir3(d));
			if (no_null == 0)
				lst_deb = list;
			no_null++;
		}
	if (no_null == 0)
	{
		list_dir5(dir_s);
		return (NULL);
	}
	list_dir5(dir_s);
	choose_sort_master(&lst_deb, d);
	return (lst_deb);
}

char		*ft_pathjoin(char const *s1, char const *s2)
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

void		free_element(t_list_ls *list)
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

void		ls_core2(t_d *d)
{
	if (d->line_feed == 1)
		ft_putchar('\n');
	d->line_feed = 1;
	d->total = 0;
}
