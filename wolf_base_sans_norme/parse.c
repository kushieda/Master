/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 04:28:58 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 04:30:52 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_tablen2(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	ft_freetab(char ***tab)
{
	int		i;

	i = 0;
	if (!*tab)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void		ft_convert(int ***imap, char **tab, t_env *map)
{
	int		i;
	int		j;
	char	**line;

	map->nb_l = ft_tablen2(tab);
	(*imap) = (int**)malloc(sizeof(int*) * map->nb_l);
	i = 0;
	while (i < map->nb_l)
	{
		line = ft_strsplit2(tab[i], ' ');
		map->nb_c = ft_tablen2(line);
		(*imap)[i] = (int*)malloc(sizeof(int) * map->nb_c);
		j = 0;
		while (j < map->nb_c)
		{
			(*imap)[i][j] = ft_atoi(line[j]);
			j++;
		}
		i++;
		ft_freetab(&line);
	}
}

void		ft_realloctabstr(char ***tab, char *nline)
{
	char	**newtab;
	int		i;

	i = ft_tablen2(*tab);
	newtab = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while ((*tab)[i])
	{
		newtab[i] = ft_strdup((*tab)[i]);
		i++;
	}
	newtab[i] = ft_strdup(nline);
	newtab[i + 1] = 0;
	ft_freetab(tab);
	*tab = newtab;
}

int			**ft_parse(char *file, t_env *map)
{
	int		file;
	int		**imap;
	char	**cmap;
	char	*line;

	if ((file = open(file, O_RDONLY)) == -1)
		exit(0);
	cmap = 0;
	while (get_next_line(file, &line) > 0)
	{
		if (!cmap)
		{
			cmap = (char**)malloc(sizeof(char*) * 2);
			cmap[1] = 0;
			cmap[0] = ft_strdup(line);
		}
		else
			ft_realloctabstr(&cmap, line);
		free(line);
	}
	ft_convert(&imap, cmap, map);
	ft_freetab(&cmap);
	close(file);
	return (imap);
}
