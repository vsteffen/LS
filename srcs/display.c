/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:37:42 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/25 17:15:04 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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


void		print_elem_in_color(t_list_ls *list, t_d *d)
{
	if (list->type == 0)
		printf(CS_RESET);
	else if (list->type == 1)
		printf(FG_LCYAN);
	else if (list->type == 2)
		printf("%s%s", FG_BLUE, BG_YELLOW);
	else if (list->type == 3)
		printf("%s%s", FG_BLUE, BG_CYAN);
	else if (list->type == 4)
		printf(FG_YELLOW);
	else if (list->type == 5)
		printf(FG_MAGENTA);
	else if (list->type == 6)
		printf(FG_GREEN);
	printf("%s", list->name);
	printf(CS_RESET);
}










void	display_list(t_list_ls *list, t_d *d, char *path)
{
	int		nb_name;
	int		tmp;
	char		*time;
	int		white_sp;



	printf("total %ld\n", d->total);

	while (list != NULL)
	{
		printf("-");
		printf((list->stat.st_mode & S_IRUSR) ? "r" : "-");
		printf((list->stat.st_mode & S_IWUSR) ? "w" : "-");
		printf((list->stat.st_mode & S_IXUSR) ? "x" : "-");
		printf((list->stat.st_mode & S_IRGRP) ? "r" : "-");
		printf((list->stat.st_mode & S_IWGRP) ? "w" : "-");
		printf((list->stat.st_mode & S_IXGRP) ? "x" : "-");
		printf((list->stat.st_mode & S_IROTH) ? "r" : "-");
		printf((list->stat.st_mode & S_IWOTH) ? "w" : "-");
		printf((list->stat.st_mode & S_IXOTH) ? "x" : "-");
//		printf(list->c_type);
		printf(" %d", list->stat.st_nlink);
		printf(" %d", list->stat.st_uid);
		printf(" %d", list->stat.st_gid);
		printf(" %lld ", list->stat.st_size);
/*		while (white_sp > 1)
		{
			printf(ctime[pos]);
			white_sp--;
		}
		if (timestamp > timeactual - 5ans)
		{
			afficher heure
		}
		else
		{
			afficher year
		}
		printf("%c%c%c", time[4], time[5], time[6]);
		(



*/
		print_elem_in_color(list, d);
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
