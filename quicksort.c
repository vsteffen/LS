/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:54:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/30 17:00:12 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_quick_sort( int[], int, int);
int		partition( int[], int, int);


int		main(void)
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
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	}
	tmp = tab[left];
	tab[left] = tab[j];
	tab[j] = tmp;
	return (j);
}
