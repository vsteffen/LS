/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/25 19:17:54 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list_ls *lst_new(void)
{
	t_list_ls	*list;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		ft_exit_prog("Failed to initialize the linked list.\n", 31, 0);
	list->name = NULL;
	list->path = NULL;
	list->dir = 0;
	list->stat = NULL;
	list->next = NULL;
	return (list);
}

void	add_elem(t_list_ls *list)
{
	if (!list)
		return ;
	while (list->next)
		list = list->next;
	list->next = lst_new();
}

void	list_dir(t_list_ls *list, t_data *data)
{
	DIR* dir_s = NULL;
	struct dirent* dir_file = NULL;

	if ((dir_s = opendir(data->path)) == NULL)
		ft_exit_prog("Fail to open directory, exit prog\n", 31, 0);
	while ((dir_file = readdir(dir_s)) != NULL)
	{
		list->name = dir_file->d_name;
		printf("%s add to linked list\n", dir_file->d_name);
		add_elem(list);
		list = list->next;
	}
	data->lst_last = list;
	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", 31, 0);
}

void	display_list(t_list_ls *list)
{
	while (list != NULL)
	{
		printf("Nom = %s\n", list->name);
		list = list->next;
	}
	printf("\nEnd of linked list\n");
}

void	lst_functions(void)
{
	t_data		data;

	data.lst_first = lst_new();
	add_elem(data.lst_first);
	display_list(data.lst_first);
	data.path = ".";
	list_dir(data.lst_first, &data);
	data.path = "./libft";
	list_dir(data.lst_first, &data);
	display_list(data.lst_first);
	//return (data);
}


void	learning_function(int ac, char **av)
{
	float		nb;
	char		type;
	int			x;

	nb = 999;

	printf("\n\t-----------------\n");
	time_function();
	printf("\n\t-----------------\n");
	stat_function(ac, av);
	printf("\n\t-----------------\n");
	printf("\n\t-----------------\n");
	printf("   nb = %0.2f\n", nb);
	//nb = ((int)(nb * 100 + .5) / 100.0);
	//printf("   nb = %f\n", nb);
	type = human_function(&nb);
	printf("nb = %0.2f %c\n", nb, type);
	printf("\n\t-----------------\n");
	printf("\n\t-----------------\n");
	lst_functions();
}

int		check_arg(int ac, char **av, t_data *data)
{
	data->path = av[0];
	printf("data->path = %s\n", data->path);
	return (0);	
}

int		main(int ac, char **av)
{
	t_data      data;
	check_arg(ac, av, &data);
	printf("data->path = %s\n", data.path);
//	learning_function(ac, av);
	return (EXIT_SUCCESS);
}
