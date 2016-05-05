/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/05/06 00:09:30 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ini_tab(t_d *d)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		d->tab_option[i] = 0;
		i++;
	}
	d->tab_option[i] = '\0';
}

void	struct_ini(t_d *d, int ac)
{
	struct winsize	w;

	d->path = ".";
	d->arg = 0;
	d->dash = 0;
	d->arg_true = 0;
	d->true_tmp = 0;
	d->ac = ac;
	d->nb_option = 0;
	d->line_feed = 0;
	d->denied = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	d->width = w.ws_col;
	d->len_max = 0;
	d->nb_display = 0;
	ini_tab(d);
}

int		norme_main_end(t_d *d)
{
	if (d->arg >= 1)
		free(d->tab_arg);
	return (EXIT_SUCCESS);
}

void	main_default(t_d *d, char *f_path)
{
	f_path = ft_strdup(".");
	ls_core(d, f_path);
	free(f_path);
}

int		main(int ac, char **av)
{
	t_d		d;
	int		arg_pos;
	int		width;
	char	*f_path;

	struct_ini(&d, ac);
	check_av(ac, av, &d);
	if (d.arg_true > 0)
	{
		arg_pos = 0;
		if (d.arg_true > 1)
			d.nb_display = 1;
		while (arg_pos < d.arg_true)
		{
			if (d.tab_arg[arg_pos].dir == 1)
				ls_core(&d, d.tab_arg[arg_pos].name);
			else
				display_file(&d, d.tab_arg[arg_pos].name, arg_pos);
			arg_pos++;
		}
	}
	else
		main_default(&d, f_path);
	return (norme_main_end(&d));
}
