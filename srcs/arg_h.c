/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_h.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:37:36 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/08 16:59:55 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	human_function(float *nb)
{
	int		count;

	count = 0;
	while (*nb >= 1000 && count < 4)
	{
		count++;
		*nb = (*nb / 1000);
	}
	if (count == 0)
		return ('B');
	*nb = ft_rounded(*nb, 1);
	if (count == 1)
		return ('K');
	if (count == 2)
		return ('M');
	if (count == 3)
		return ('G');
	if (count == 4)
		return ('P');
	return (0);
}
