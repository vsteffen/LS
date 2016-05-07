/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/07 20:59:10 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <math.h>
# include <time.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include "../libft/include/libft.h"
# define MAJOR(x)    ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)    ((int32_t)((x) & 0xffffff))
# define MAKEDEV(x,y)    ((dev_t)(((x) << 24) | (y)))

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
	char				c_type;
	t_stat				stat;
	int					len_name;
	struct s_list_ls	*next;
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
	int					tab_option[11];
	int					nb_option;
	int					arg_true;
	int					true_tmp;
	t_list_ls			*lst_deb;
	t_list_ls			*lst_actual;
	t_list_ls			*lst_end;
	int					denied;
	int					line_feed;
	int					width;
	int					len_max;
	int					nb_display;
	unsigned long int	total;
	int					ok;
}						t_d;

typedef struct			s_sortab
{
	t_list_ls			*list_ptr;
	char				*name;
}						t_sortab;

typedef	t_list_ls		*t_node_ptr;

int						main(int ac, char **av);

char					human_function(float *nb);

void					display_choose(t_list_ls *list, t_d *d, char *path);
void					display_list(t_list_ls *list, t_d *d, char *path);
void					display_list_1(t_list_ls *list, t_d *d, char *path);
void					display_file(t_d *d, char *path, int arg_pos);

int						check_av(int ac, char **av, t_d *d);
void					check_arg(char **av, t_d *d, int *ac_var, int i);
int						check_arg_spe(char arg_tmp, t_d *d);
void					assign_name_value_arg(char **av, t_d *d, int *ac_var);
void					assign_double_dash(t_d *d);

void					detect_arg_true(t_d *d, int ret);
void					qsort_tab_argv(t_d *d, int first, int last, int p);
void					swap_tab_arg(t_d *d, int left, int right);
void					del_elem_tab_arg(t_d *d, int tmp);

int						revert_file(t_d *d);
void					revert_array(t_d *d);

void					print_elem_in_color(t_list_ls *list, t_d *d);
void					major_minor(t_list_ls *list, t_d *d);
void					left_side(t_list_ls *list, t_d *d);
void					read_link(t_list_ls *list, t_d *d);
void					get_time_print(char *time_str, int *pos);
void					get_time(t_list_ls *list, t_d *d);
void					long_list_format(t_list_ls *list, t_d *d, char *path);
void					display_list_part_1(t_list_ls *list, t_d *d);
void					display_list_part_2(t_list_ls *list, t_d *d,
		int *tmp, int nb_name);

void					ft_merge_sort_list(t_node_ptr *source);
void					ft_merge_sortr_list(t_node_ptr *source);
void					ft_merge_sort_time(t_node_ptr *source);
void					ft_merge_sortr_time(t_node_ptr *source);
void					ft_merge_sort_time_u(t_node_ptr *source);
void					ft_merge_sortr_time_u(t_node_ptr *source);
void					ft_merge_sort_size(t_node_ptr *source);
void					ft_merge_sortr_size(t_node_ptr *source);

void					ini_tab(t_d *d);

void					print_elem_in_color(t_list_ls *list, t_d *d);
void					major_minor(t_list_ls *list, t_d *d);
void					left_side(t_list_ls *list, t_d *d);
void					read_link(t_list_ls *list, t_d *d);
void					get_time_print(char *time_str, int *pos);
void					get_time(t_list_ls *list, t_d *d);
void					display_size(t_list_ls *list, t_d *d);
void					long_list_format(t_list_ls *list, t_d *d, char *path);
void					display_list_part_1(t_list_ls *list, t_d *d);
void					display_list_part_2(t_list_ls *list, t_d *d,
		int *tmp, int nb_name);
void					display_choose(t_list_ls *list, t_d *d, char *path);
void					display_list(t_list_ls *list, t_d *d, char *path);
void					display_list_1(t_list_ls *list, t_d *d, char *path);

void					print_elem_in_color_file_norme(char *color1,
		char *color2);
void					print_elem_in_color_file(t_d *d, t_stat stat,
		char *path,
		char c_type);

char					type_file_file(t_d *d, t_stat *stat, char *path);
void					left_side_file(t_d *d, t_stat *stat, char c_type);
void					major_minor_file(t_d *d, t_stat *stat);
void					get_time_print_file(char *time_str, int *pos);
void					get_time_file(t_d *d, t_stat stat);
void					read_link_file(t_d *d, t_stat stat, char *path,
		int c_type);
void					long_list_format_file(t_d *d, char *path);
void					display_file(t_d *d, char *path, int arg_pos);

int						check_arg_spe2(char arg_tmp, t_d *d);
void					detect_arg_true2(t_d *d, int ret);

int						type_file(t_list_ls *list, t_d *d);
t_list_ls				*lst_new(char *d_name, char *path, t_d *d);
t_list_ls				*add_elem_4(t_list_ls *list, t_d *d, char *d_name,
		char *path);
int						read_hidden(char *d_name, int status);
void					choose_sort(t_list_ls **lst_deb, t_d *d);
void					choose_sort2(t_list_ls **lst_deb, t_d *d);
void					*list_dir2(t_d *d, char *path);
void					*list_dir3(t_d *d);
void					list_dir4(DIR **dir_s, struct dirent **dir_file,
		int *no_null);
void					choose_sort_master(t_list_ls **lst_deb, t_d *d);
void					list_dir5(DIR *dir_s);
t_list_ls				*list_dir(t_list_ls *list, t_d *d, char *path,
		t_list_ls *lst_deb);
char					*ft_pathjoin(char const *s1, char const *s2);
void					free_element(t_list_ls *list);
void					ls_core2(t_d *d);
void					ls_core3(t_d *d, t_list_ls *lst_deb);
void					ls_core(t_d *d, char *path);
#endif
