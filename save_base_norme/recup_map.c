/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 04:46:36 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 04:51:54 by jyim             ###   ########.fr       */
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

void		ft_convertisseur(int ***imap, char **tab, t_env *map)
{
	int		i;
	int		j;
	char	**line;

	map->nb_l = ft_tablen2(tab);
	(*imap) = (int**)malloc(sizeof(int*) * map->nb_l);
	i = 0;
	while (i < map->nb_l)
	{
		line = ft_splitwolf(tab[i], ' ');
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

void		ft_realloctab(char ***tab, char *xline)
{
	char	**tmp;
	int		i;

	i = ft_tablen2(*tab);
	tmp = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while ((*tab)[i])
	{
		tmp[i] = ft_strdup((*tab)[i]);
		i++;
	}
	tmp[i] = ft_strdup(xline);
	tmp[i + 1] = 0;
	ft_freetab(tab);
	*tab = tmp;
}

int			**ft_parse(char *file, t_env *map)
{
	int		file2;
	int		**map2;
	char	**map3;
	char	*line;

	if ((file2 = open(file, O_RDONLY)) == -1)
		exit(0);
	map3 = 0;
	while (get_next_line(file2, &line) > 0)
	{
		if (!map3)
		{
			map3 = (char**)malloc(sizeof(char*) * 2);
			map3[1] = 0;
			map3[0] = ft_strdup(line);
		}
		else
			ft_realloctab(&map3, line);
		free(line);
	}
	ft_convertisseur(&map2, map3, map);
	ft_freetab(&map3);
	close(file2);
	return (map2);
}
