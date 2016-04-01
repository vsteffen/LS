/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/01 22:43:51 by vsteffen         ###   ########.fr       */
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
typedef struct			s_list_ls
{
	char				*name;
	char				*path;
	int					dir;
	t_stat				*stat;
	struct s_list_ls	*next;
}						t_list_ls;

typedef struct			s_data
{
	char				*name;
	char				*path;
	int					arg;
	int					tab_arg[6];
	t_list_ls			*tab_node;
	t_list_ls			*lst_first;
	t_list_ls			*lst_last;
}						t_data;

int						main(int ac, char **av);

void					stat_function(int ac, char **av);
void					time_function(void);
char					human_function(float *nb);

int						check_av(int ac, char **av, t_data *data);
void					check_arg(int ac, char **av, t_data *data, int *ac_var);
int						check_arg_spe(char arg_tmp, t_data *data);
void					tab_arg_display(t_data *data);

void					display_list(t_list_ls *list);
void					tab_arg_display(t_data *data);
void					av_display(int ac, char **av);

#endif
