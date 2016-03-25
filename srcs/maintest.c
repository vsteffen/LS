/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/25 16:44:08 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exitProg(char *status)
{
	ft_putstr(status);
	exit(0);
}

float		rounded(float number, int decimal)
{
	return (number >= 0) ? ((int)(number * decimal + 0.5) / (decimal * 1.0))
		: ((int)(number * decimal - 0.5) / (decimal * 1.0));
}

char	human_function(float *nb)
{
	int		count;
	int		decimal;
	float	float_nb = 1000;
	double	round;

	count = 0;
	while (*nb >= 1000 && count < 4)
	{
		count++;
		*nb = (*nb / 1000);
	}
	if (count == 0)
		return ('B');	
	*nb = rounded(*nb, 10);
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

void	listxattr_function(int argc, char *argv[])
{

}

void	stat_function(int ac, char **av)
{
	struct	stat sb;
	int		ret;

	//	DIR *dirp;
	//	struct dirent *dp;
	//
	//	if ((dirp = opendir("/dev")) == NULL)
	//		exitProg("Couldn't open '.'");

	//ret = stat("/nfs/2015/v/vsteffen/LS/Makefile", &sb);
	ret = lstat("/dev/disk0", &sb);
	printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);

	printf("Mode :                             %lo (octal)\n",
			(unsigned long) sb.st_mode);

	printf("Nombre de liens :                  %ld\n", (long) sb.st_nlink);
	printf("Propriétaires :                    UID=%ld   GID=%ld\n",
			(long) sb.st_uid, (long) sb.st_gid);

	printf("Taille de bloc d’E/S :             %ld octets\n",
			(long) sb.st_blksize);
	printf("Taille du fichier :                %lld octets\n",
			(long long) sb.st_size);
	printf("Blocs alloués :                    %lld\n",
			(long long) sb.st_blocks);

	printf("Dernier changement d’état :        %s", ctime(&sb.st_ctime));
	printf("Dernier accès au fichier :         %s", ctime(&sb.st_atime));
	printf("Dernière modification du fichier:  %s", ctime(&sb.st_mtime));


	printf("File Permissions: \t");
	printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
	printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
	printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
	printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
	printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
	printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
	printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
	printf( (sb.st_mode & S_IROTH) ? "r" : "-");
	printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
	printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");

	printf("The file %s a directory\n", (S_ISDIR(sb.st_mode)) ? "is" : "is not");
	printf("The file %s a symbolic link\n", (S_ISLNK(sb.st_mode)) ? "is" : "is not");
	printf("The file %s a block special file\n", (S_ISBLK(sb.st_mode)) ? "is" : "is not");
	printf("The file %s a character special file\n", (S_ISCHR(sb.st_mode)) ? "is" : "is not");
	printf("The file %s a pipe or FIFO special file\n", (S_ISFIFO(sb.st_mode)) ? "is" : "is not");
	printf("The file %s a regular file\n", (S_ISREG(sb.st_mode)) ? "is" : "is not");
	printf("The file %s a socket\n", (S_ISSOCK(sb.st_mode)) ? "is" : "is not");
}

void	time_function(void)
{
	time_t temps;

	time(&temps);
	printf("%s", ctime(&temps));
}

t_list_ls *lst_new(void)
{
	t_list_ls	*list;

	if (!(list = (t_list_ls*)malloc(sizeof(t_list_ls))))
		exitProg("Failed to initialize the linked list.\n");
	list->name = NULL;
	list->path = NULL;
	list->dir = 0;
	list->stat = NULL;
	list->next = NULL;
	return (list);
}

void	add_elem(t_list_ls *list)
{
	if (!list)
		return ;
	while (list->next)
		list = list->next;
	list->next = lst_new();
}

void	list_dir(t_list_ls *list, t_data *data)
{
	DIR* dir_s = NULL;
	struct dirent* dir_file = NULL;

	if ((dir_s = opendir(data->path)) == NULL)
		exitProg("Fail to open directory, exit prog\n");
	while ((dir_file = readdir(dir_s)) != NULL)
	{
		list->name = dir_file->d_name;
		printf("%s add to linked list\n", dir_file->d_name);
		add_elem(list);
		list = list->next;
	}
	data->lst_last = list;
	if (closedir(dir_s) == -1)
		exitProg("Fail to close directory stream\n");
}

void	display_list(t_list_ls *list)
{
	while (list != NULL)
	{
		printf("Nom = %s\n", list->name);
		list = list->next;
	}
	printf("\nEnd of linked list\n");
}

void	lst_functions(void)
{
	t_data		data;

	data.lst_first = lst_new();
	add_elem(data.lst_first);
	display_list(data.lst_first);
	data.path = ".";
	list_dir(data.lst_first, &data);
	data.path = "./libft";
	list_dir(data.lst_first, &data);
	display_list(data.lst_first);
	//return (data);
}


void	learning_function(int ac, char **av)
{
	float		nb;
	char		type;
	int			x;

	nb = 999;

	printf("\n\t-----------------\n");
	time_function();
	printf("\n\t-----------------\n");
	stat_function(ac, av);
	printf("\n\t-----------------\n");
	listxattr_function(ac, av);
	printf("\n\t-----------------\n");
	printf("   nb = %0.2f\n", nb);
	//nb = ((int)(nb * 100 + .5) / 100.0);
	//printf("   nb = %f\n", nb);
	type = human_function(&nb);
	printf("nb = %0.2f %c\n", nb, type);
	printf("\n\t-----------------\n");
	printf("\n\t-----------------\n");
	lst_functions();
}

int		main(int ac, char **av)
{
	learning_function(ac, av);
	return (EXIT_SUCCESS);
}
