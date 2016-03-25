/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/25 16:40:23 by vsteffen         ###   ########.fr       */
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
	t_list_ls			*lst_first;
	t_list_ls			*lst_last;
}						t_data;

#endif
