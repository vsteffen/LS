/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/12 20:41:07 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list_ls	*lst_new(char *d_name, char *path)
{
	t_list_ls	*list;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		ft_exit_prog("Failed to initialize the linked list.\n", 31, 0);
	list->name = d_name;
	list->path = path;
	//	list->dir = 0;
	//	list->stat = NULL;
	list->next = NULL;
	return (list);
}

t_list_ls	*add_elem_4(t_list_ls *list, t_d *d, char *d_name)
{	
	t_list_ls	*tmp;
//	printf("ADD ELEM 4\n");
//	d->lst_length++;
	if (!list)
	{
		list = lst_new(d_name, d->path);
		d->lst_deb = list;
		d->lst_actual = list;
		d->lst_end = list;
		return (list);
	}
	tmp = list;
	list->next = lst_new(ft_strdup(d_name), ft_strdup(d->path));
	d->lst_actual = list->next;
	return (list->next);
}

t_list_ls	*add_elem_5(t_list_ls *list, t_d *d, char *d_name)
{	
	t_list_ls	*tmp;
//	printf("ADD ELEM 5\n");
//	d->lst_length++;
	if (!list)
	{
		list = lst_new(d_name, d->path);
		d->lst_deb = list;
		d->lst_actual = list;
		d->lst_end = list;
		return (list);
	}
	tmp = list;
	list->next = lst_new(ft_strdup(d_name), ft_strdup(d->path));
	return (list->next);
}

/*
void		ft_qsort_list_str(char **array, int first, int last)
{
	int		left;
	int		right;
	char	*pivot;

	left = first - 1;
	right = last + 1;
	pivot = array[first];
	if (first >= last)
		return ;
	while (1)
	{
		right--;
		while (ft_strcmp(array[right], pivot) > 0)
			right--;
		left++;
		while (ft_strcmp(array[left], pivot) < 0)
			left++;
		if (left < right)
			ft_swap_str(&array[left], &array[right]);
		else
			break ;
	}
	ft_qsort_list_str(array, first, right);
	ft_qsort_list_str(array, right + 1, last);
}


void		qsort_lst(t_d *d, t_list_ls *list)
{
	char			**tab[d->lst_length];
	unsigned int	i;
	i = 0;

	while (list->next)
	{
		tab[i] = &list->name;
		list = list->next;
		i++;
	}
	tab[i] = &list->name;
	ft_qsort_list_str(tab[d->lst_length], 0, (i - 2));
	printf("tab[9] = %s\n", *tab[9]);

}
*/

void		list_dir(t_list_ls *list, t_d *d)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	t_list_ls 		*list_tmp;

	dir_s = NULL;
	dir_file = NULL;
//	printf("IN LIST_ DIR : data->path = \"%s\"\n", d->path);
	if ((dir_s = opendir(d->path)) == NULL)
		ft_exit_prog("Fail to open directory, exit prog\n", 31, 0);	
	if ((dir_file = readdir(dir_s)) != NULL)
		d->lst_end = add_elem_4(d->lst_end, d, dir_file->d_name);
	while ((dir_file = readdir(dir_s)) != NULL)
		d->lst_end = add_elem_5(d->lst_end, d, dir_file->d_name);
	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", 31, 0);
	if (d->tab_option[5] == 0)
		ft_merge_sort_list(&d->lst_deb);
	else
		ft_merge_sort_list(&d->lst_deb);
	//	qsort_lst(d, d->lst_actual);
}
/*
// Quick Sort List
void QuickSortList(IntegerList *pLeft, IntegerList *pRight)
{
IntegerList *pStart;
IntegerList *pCurrent; 
int nCopyInteger;

// If the left and right pointers are the same, then return
if (pLeft == pRight) return;

// Set the Start and the Current item pointers
pStart = pLeft;
pCurrent = pStart->pNext;

// Loop forever (well until we get to the right)
while (1)
{
// If the start item is less then the right
if (pStart->nInteger < pCurrent->nInteger)
{
// Swap the items
nCopyInteger = pCurrent->nInteger;
pCurrent->nInteger = pStart->nInteger;
pStart->nInteger = nCopyInteger;
}	

// Check if we have reached the right end
if (pCurrent == pRight) break;

// Move to the next item in the list
pCurrent = pCurrent->pNext;
}

// Swap the First and Current items
nCopyInteger = pLeft->nInteger;
pLeft->nInteger = pCurrent->nInteger;
pCurrent->nInteger = nCopyInteger;

// Save this Current item
IntegerList *pOldCurrent = pCurrent;

// Check if we need to sort the left hand size of the Current point
pCurrent = pCurrent->pPrev;
if (pCurrent != NULL)
{
if ((pLeft->pPrev != pCurrent) && (pCurrent->pNext != pLeft))
QuickSortList(pLeft, pCurrent);
}

// Check if we need to sort the right hand size of the Current point
pCurrent = pOldCurrent;
pCurrent = pCurrent->pNext;
if (pCurrent != NULL)
{
if ((pCurrent->pPrev != pRight) && (pRight->pNext != pCurrent))
QuickSortList(pCurrent, pRight);
}
}
*/

void		lst_functions(t_d *d)
{
	list_dir(d->lst_end, d);
	display_list(d->lst_deb);
	printf("list->name = %s\n", d->lst_actual->name);
	printf("list->path = %s\n\n", d->lst_actual->path);
//	printf("list->lst_length = %u\n\n", d->lst_length);
	ft_merge_sortr_list(&d->lst_deb);
//	display_list(d->lst_deb);
	//	ft_qsort_list_str(d->lst_deb, d);
/*
	d->path = "./libft";
	list_dir(d->lst_end, d);
	display_list(d->lst_deb);
	printf("list->name = %s\n", d->lst_actual->name);
	printf("list->path = %s\n", d->lst_actual->path);
//	printf("list->lst_length = %u\n\n", d->lst_length);
	//mergeSort(&d->lst_deb);
	//	display_list(d->lst_deb);
*/
}

void		struct_ini(t_d *d, int ac)
{
	int		i;

	d->path = ".";
	d->arg = 0;
	d->dash = 0;
	d->arg_true = 0;
	d->ac = ac;
	d->nb_option = 0;
	i = 0;
	while (i < 6)
	{
		d->tab_option[i] = 0;
		i++;
	}
	d->tab_option[i] = '\0';
}

int			main(int ac, char **av)
{
	t_d		d;
	
	struct_ini(&d, ac);
	check_av(ac, av, &d);
//	av_display(ac, av);
//	tab_option_display(&d);
	lst_functions(&d);
	display_list(d.lst_deb);

//	printf("d.arg = %d //// d.arg_true = %d\n", d.arg, d.arg_true);
//	printf("name = %s\n",d.lst_deb->name);
	if (d.arg >= 1)
		free(d.tab_arg);
	return (EXIT_SUCCESS);
}
