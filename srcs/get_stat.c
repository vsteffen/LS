/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:39:41 by vsteffen          #+#    #+#             */
/*   Updated: 2016/04/24 20:38:52 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	stat_function(int ac, char **av)
{
	struct	stat sb;
	int		ret;

	DIR *dirp;
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
