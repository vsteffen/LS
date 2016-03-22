/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/22 21:43:42 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


#include <math.h>


#include <time.h>

#include <sys/xattr.h>

# include "libft.h"

/*
typedef struct		files_s
{
	char			*name;
	int				pouet;
}					files_t;
*/

typedef struct			data_s
{
	unsigned long int	index_d;
	char				*path;
}						data_t;

typedef struct	s_files
{
	char			*name;
	long long		size;
	int				real;
}				t_files;

//struct files_t **index_f;

//struct index_f *index_d;
#endif
