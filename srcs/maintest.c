/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/03/17 19:14:07 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
   void listdir(const char *name, int level)
   {
   DIR *dir;
   struct dirent *entry;

   if (!(dir = opendir(name)))
   return;
   if (!(entry = readdir(dir)))
   return;

   do {
   if (entry->d_type == DT_DIR) {
   char path[1024];
   int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
   path[len] = 0;
   if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
   continue;
   printf("%*s[%s]\n", level*2, "", entry->d_name);
   listdir(path, level + 1);
   }
   else
   printf("%*s- %s\n", level*2, "", entry->d_name);
   } while (entry = readdir(dir));
   closedir(dir);
   }*/

void	stat_function()
{
	struct	stat sb;
	int		ret;

	DIR *dirp;
	struct dirent *dp;

	if ((dirp = opendir(".")) == NULL)
		exitProg("Couldn't open '.'");

	ret = stat("/nfs/2015/v/vsteffen/LS/Makefile", &sb);

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

	if ((dp = readdir(dirp)) != NULL) {
		if (strcmp(dp->d_name, arg) != 0)
			continue;


		(void) printf("found %s\n", arg);
		(void) closedir(dirp);
		exitProg
	}

	void	time_function(void)
	{
		time_t temps;

		time(&temps);
		printf("%s", ctime(&temps));
	}

	void	learning_function()
	{
		printf("\n\t-----------------\n");
		time_function();
		printf("\n\t-----------------\n");
		stat_function();
		printf("\n\t-----------------\n");
		//	listdir(".", 0);
	}


	int		main(int ac, char **av)
	{
		learning_function();
		return (EXIT_SUCCESS);
	}
