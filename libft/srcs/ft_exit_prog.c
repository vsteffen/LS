/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 16:54:41 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/25 17:32:29 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit_prog(char *status, int color, int debug)
{
	ft_colors(color);
	ft_putstr(status);
	ft_colors(0);
	if (debug == 0)
		perror("\nperror message ");
	exit(0);
}
