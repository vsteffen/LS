/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/18 19:48:42 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include <time.h>
# include <sys/xattr.h>
# include "libft.h"

typedef struct stat		t_stat;

typedef struct			s_argv
{
	char				*name;
	int					dir;
	int					access;
}						t_argv;

typedef struct			s_list_ls
{
	char				*name;
	char				*path;
	int					dir;
	t_stat				*stat;
	struct s_list_ls	*next;
	struct s_list_ls	*prev;
}						t_list_ls;

typedef struct			s_d
{
	char				*name;
	char				*path;
	int					arg;
	int					dash;
	int					ac;
	unsigned int		lst_length;
	t_argv				*tab_arg;
	char				*pn;
	int					left;
	int					tab_option[7];
	int					nb_option;
	int					arg_true;
	t_list_ls			*lst_deb;
	t_list_ls			*lst_actual;
	t_list_ls			*lst_end;
}						t_d;

typedef struct			s_sortab
{
	t_list_ls           *list_ptr;
	char				*name;
}						t_sortab;

typedef t_list_ls *nodePtr;
nodePtr globalHead;

int						main(int ac, char **av);

void					stat_function(int ac, char **av);
void					time_function(void);
char					human_function(float *nb);

void					tab_arg_display(t_d *d);
void					display_list(t_list_ls *list);
void					tab_option_display(t_d *d);
void					av_display(int ac, char **av);

int						check_av(int ac, char **av, t_d *d);
void					check_arg(char **av, t_d *d, int *ac_var, int i);
int						check_arg_spe(char arg_tmp, t_d *d);
void					assign_name_value_arg(char **av, t_d *d, int *ac_var);
void					assign_double_dash(t_d *d);

void					detect_arg_true(t_d *d, int ret);
void					qsort_tab_argv(t_d *d, int first, int last, int p);
void					swap_tab_arg(t_d *d, int left, int right);
void					del_elem_tab_arg(t_d *d, int tmp);

void					ls_core(t_d *d);

void                    ft_merge_sort_list(nodePtr *source);
void					ft_merge_sortr_list(nodePtr *source);

#endif
