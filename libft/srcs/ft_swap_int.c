/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 19:40:14 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/30 19:40:36 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_swap_int(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}