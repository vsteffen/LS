/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/21 18:43:16 by vsteffen         ###   ########.fr       */
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

typedef struct		data_s
{
	char				*name;

	unsigned long long	total_size;
	
}			data_t;

#endif

/*
 *
 *		 STRUCTURE MERE : -> name --> structure stat
 *		 				  -> max_length
 *		 				  -> 
 *
 *
 *
 *
 *
 *
 *
