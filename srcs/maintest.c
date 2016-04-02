/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/02 19:22:25 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"





typedef t_list_ls *nodePtr;

struct Node{

	    int data;
		nodePtr next;
};

nodePtr globalHead;



void partition(nodePtr head, nodePtr *front, nodePtr *back)
{
	nodePtr fast;
	nodePtr slow;

	if (head == NULL || head->next == NULL)
	{

		*front = head; // &a
		*back = NULL; // &b

	}
	else
	{

		slow = head;
		fast = head->next;

		while(fast != NULL)
		{

			fast = fast->next;

			if(fast != NULL)
			{

				slow = slow->next;
				fast = fast->next;

			}

		}

		*front = head; // a
		*back = slow->next; // b
		slow->next = NULL;
	}

}

nodePtr mergeLists(nodePtr a, nodePtr b){

	nodePtr mergedList = NULL;

	if (a == NULL)
	{
		return b;
	}
	else if (b == NULL)
	{
		return a;
	}

	if (ft_strcmp(a->name, b->name) <= 0)
	{
		mergedList = a;
		mergedList->next = mergeLists(a->next, b);
	}
	else
	{
		mergedList = b;
		mergedList->next = mergeLists(a, b->next);
	}

	return mergedList;

}

void mergeSort(nodePtr *source)
{

	nodePtr head = *source;
	nodePtr a = NULL;
	nodePtr b = NULL;

	if(head == NULL || head->next == NULL)
	{

		return;

	}

	partition(head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*source = mergeLists(a, b);

}

























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

void		add_elem(t_list_ls *list, t_data *data, char *d_name)
{
	if (!list)
		return ;
	while (list->next)
		list = list->next;
	list->next = lst_new(d_name, data->path);
	data->lst_last = list->next;
}

t_list_ls	*add_elem_2(t_list_ls *list, t_data *data, char *d_name)
{
	t_list_ls *debut;

	if (!list)
	{
		list = lst_new(d_name, data->path);
		data->lst_last = list;
		data->lst_first = list;
		return (list);
	}
	debut = list;
	while (list->next)
		list = list->next;
	list->next = lst_new(ft_strdup(d_name), ft_strdup(data->path));
//	data->lst_last = list->next;
	return (debut);
}

void		list_dir(t_list_ls *list, t_data *data)
{
	DIR				*dir_s;
	struct dirent	*dir_file;
	t_list_ls 		*list_tmp;

	dir_s = NULL;
	dir_file = NULL;
	data->lst_last = list;
	if ((dir_s = opendir(data->path)) == NULL)
		ft_exit_prog("Fail to open directory, exit prog\n", 31, 0);
	while ((dir_file = readdir(dir_s)) != NULL)
		list = add_elem_2(list, data, dir_file->d_name);
//	data->lst_last = list;
	if (closedir(dir_s) == -1)
		ft_exit_prog("Fail to close directory stream\n", 31, 0);
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
*//*
	 void		ft_qsort_list_str(t_list_ls *array, int first, int last)
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
	 */
void		lst_functions(t_data *data)
{
//	data->lst_first = lst_new();
//	data->lst_last = data->lst_first;

	//	display_list(data->lst_first);
	//	add_elem(data->lst_first);


	list_dir(data->lst_last, data);
	display_list(data->lst_first);
	mergeSort(&data->lst_first);
	display_list(data->lst_first);
	
	//	ft_qsort_list_str(data->lst_first, data);
	
	data->path = "./libft";
	list_dir(data->lst_last, data);
//	mergeSort(&data->lst_last);
	display_list(data->lst_first);
}

void		struct_ini(t_data *data)
{
	int		i;

	data->path = "";
	data->arg = 1;
	i = 0;
	while (i < 6)
	{
		data->tab_arg[i] = 0;
		i++;
	}
	data->tab_arg[i] = '\0';
}

int			main(int ac, char **av)
{
	t_data		data;

	struct_ini(&data);
	check_av(ac, av, &data);
	av_display(ac, av);
	//	printf("data->path = %s\n", data.path);
	//	ls_core(av, &data);
	//	learning_function(ac, av);
	lst_functions(&data);
	return (EXIT_SUCCESS);
}
