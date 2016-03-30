/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:46:10 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/30 19:32:30 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			check_arg_spe(char arg_tmp, t_data *data)
{
	if (arg_tmp == 'L')
		return (data->tab_arg[0] = 11);
	else if (arg_tmp == 'R')
		return (data->tab_arg[1] = 2);
	else if (arg_tmp == 'a')
		return (data->tab_arg[2] = 4);
	else if (arg_tmp == 'l')
		return (data->tab_arg[3] = 3);
	else if (arg_tmp == 'r')
		return (data->tab_arg[4] = 22);
	else if (arg_tmp == '1')
		return (data->tab_arg[5] = 2);
	else
	{
		printf("ls: illegal option -- %c\n", arg_tmp);
		printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1]");
		printf("[file ...]\n");
		exit(0);
	}
	return (0);
}

void		check_arg(int ac, char **av, t_data *data, int *ac_var)
{
	int		i;

	i = 1;
	if (av[*ac_var][0] == '-' && av[*ac_var][1] == '\0')
		data->path = ft_strjoin(data->path, "- ");
	else if (av[*ac_var][0] == '-')
	{
		while (av[*ac_var][i] != '\0')
		{
			check_arg_spe(av[*ac_var][i], data);
			i++;
		}
	}
	else
	{
		data->path = ft_strjoin(data->path, av[*ac_var]);
		data->path = ft_strjoin(data->path, " ");
	}
}

void		tab_arg_display(t_data *data)
{
	int		ac_var;

	ac_var = 0;
	while (ac_var != 6)
	{
		printf("data->tab_arg[%d] = %d\n", ac_var, data->tab_arg[ac_var]);
		ac_var++;
	}
}

void		ft_swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		ft_swap_char(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		ft_swap_int(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			arg_reorder(int ac, char **av, t_data *data)
{
	unsigned int	left;
	unsigned int	right;
	unsigned int	tp;
	unsigned char	*tmp;
	unsigned int	length;

	printf("ENTERING IN ARG_REORDER\n");
	while (1)
	{
		left = 1;
		right = 6;//ac;
		while (left != right)
		{
			if (data->tab_arg[left] > data->tab_arg[right])
			{
				ft_swap_int(&data->tab_arg[left], &data->tab_arg[right]);
				//				tp = right;
				//				left = right;
				//				right = tp;
				printf("BOUCLE left = %d /// right = %d\n", left, right);
				left++;
			}
			printf("BESIDE BOUCLE left = %d /// right = %d\n", left, right);
			right--;
		}
		if (right == 1 && left != 1)
			return (1);
		if (right == 1 && left == 1)
			return (0);
	}
}
/*
int		partition(int tab[], int left, int right)
{
	int		pivot;
	int		i;
	int		j;
	int		tmp;

	pivot = tab[left];
	i = left;
	j = right + 1;
	while (1)
	{
		++i;
		while (tab[i] <= pivot && i <= right)
			i++;
		--j;
		while (tab[j] > pivot)
			--j;
		if (i >= j)
			break ;
		ft_swap_int(&tab[i], &tab[j]);
	}
	ft_swap_int(&tab[left], &tab[j]);
	return (j);
}

void	ft_quick_sort(int tab[], int left, int right)
{
	int j;

	if (left < right)
	{
		j = partition(tab, left, right);
		ft_quick_sort(tab, left, j - 1);
		ft_quick_sort(tab, j + 1, right);
	}
}

int		test(void)
{
	int a[] = { 9, 12, 1, -2, 0, 15, 1, 11, 7};
	int i;

	printf("\n\nUnsorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
	ft_quick_sort(a, 0, 8);
	printf("\n\nSorted array is:  ");
	for (i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
	return (0);
}
*/

void ft_quick_sort(int array[], int first, int last)
{
	int left;
	int right;
	const int pivot;

	left = first - 1;
	right = last + 1;
	pivot = array[first];
	if (first >= last)
		return (0);
	while (1)
	{
		right--;
		while (array[right] > pivot)
			right--;
		left++;
		while (array[left] < pivot)
			left++;
		if (left < right)
			ft_swap_int(&array[left], &array[right]);
		else break;
	}
	ft_quick_sort(array, first, right);
	ft_quick_sort(array, right + 1, last);
}

int			check_av(int ac, char **av, t_data *data)
{
	int		ac_var;
	char	*value1 = "POUETTE";
	char	*value2 = "CACA";
	int		nb1 = 2;
	int		nb2 = 3;
	int		*p1 = &nb1;
	int 	*p2 = &nb2;
	int		ret;


	if (ac == 1)
	{
		data->arg = 0;
		data->path = ".";
		return (0);
	}
	ac_var = 1;
	ret = 1;
	//	while (arg_reorder(ac, av, data))
	//		nb1 = nb2;
	//	arg_reorder(ac, av, data);
	while (ac_var < ac)
	{
		check_arg(ac, av, data, &ac_var);
		ac_var++;
	}
	if (ft_strequ(data->path, "") == 1)
		data->path = ".";
	tab_arg_display(data);
	ft_putchar('\n');
	//	test();
	printf("\n\n");
	ft_quick_sort(data->tab_arg, 0, 5);
	//	ft_quick_sort(data->tab_arg, 0, 5);
	//	while (arg_reorder(ac, av, data))
	//		nb1 = nb2;
	tab_arg_display(data);
	return (0);
}
