/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/24 23:04:02 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		struct_ini(t_d *d, int ac)
{
	int				i;
	struct winsize	w;

//	if (!(d = (t_d*)malloc(sizeof(t_d))))
//		ft_exit_prog("Fail to malloc data structure\n", FG_RED, 0);
	d->path = ".";
	d->arg = 0;
	d->dash = 0;
	d->arg_true = 0;
	d->true_tmp = 0;
	d->ac = ac;
	d->nb_option = 0;
	d->line_feed = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	d->width = w.ws_col;
	d->len_max = 0;
	d->nb_display = 0;
//	d->ok = 1;
	i = 0;
	while (i < 7)
	{
		d->tab_option[i] = 0;
		i++;
	}
	d->tab_option[i] = '\0';
}

int			main(int ac, char **av)
{
	t_d		d;
	int		arg_pos;
	int		width;
	
	struct_ini(&d, ac);
	check_av(ac, av, &d);
//	printf("len_max = %d", d.len_max);
	//	av_display(ac, av);
	//	tab_option_display(&d);
	//	printf("******************************************** AFTER ALL\n[0].name = %s ///// [1].name = %s //// [2].name = %s ///// [3].name = %s\n", d.tab_arg[0].name, d.tab_arg[1].name, d.tab_arg[2].name, d.tab_arg[3].name);
	//	lst_functions(&d);
	//	display_list(d.lst_deb);
	//	printf("\n\n0 --> name = %s and dir = %d\n", d.tab_arg[0].name, d.tab_arg[0].dir);
	if (d.arg_true > 0)
	{
		arg_pos = 0;
		while (arg_pos < d.arg_true)
		{
			if (d.tab_arg[arg_pos].dir == 1)
				ls_core(&d, d.tab_arg[arg_pos].name);//, d.tab_option[2]);
			else
				display_file(&d, arg_pos, d.tab_arg);
			arg_pos++;
		}
	}
	else
		ls_core(&d, ".");// d.tab_option[2]);
	//	printf("d.arg = %d //// d.arg_true = %d\n", d.arg, d.arg_true);
	//	printf("name = %s\n",d.lst_deb->name);
//	printf("d.len_max = %d\n", d.len_max);
	if (d.arg >= 1)
		free(d.tab_arg);
	return (EXIT_SUCCESS);
	exit(0);
}
