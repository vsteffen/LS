/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 19:28:04 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/16 15:49:49 by vsteffen         ###   ########.fr       */
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

#include <time.h>

#include <sys/xattr.h>

# include "libft.h"

typedef struct		data_s
{
	int		b;
}			data_t;

#endif
