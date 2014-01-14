/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wolf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 04:59:32 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 04:59:33 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_find_it(char *s, int *next, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	*next = i;
}

static void		ft_freetabstr(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

static void		ft_realloc(char ***tab, char *s)
{
	char		**tmp;
	int			i;

	i = 0;
	while ((*tab)[i])
		i++;
	tmp = (char**)malloc(sizeof(char*) * (i + 2));
	tmp[i + 1] = 0;
	i = 0;
	while ((*tab)[i])
	{
		tmp[i] = ft_strdup((*tab)[i]);
		i++;
	}
	tmp[i] = ft_strdup(s);
	ft_freetabstr(tab);
	*tab = tmp;
}

char			**ft_splitwolf(char *string, char c)
{
	char		**tabl;
	char		*tmp;
	int			next;

	tabl = (char**)malloc(sizeof(char*) * 1);
	tabl[0] = 0;
	ft_rm_char(&string, c);
	next = 0;
	while (*string)
	{
		ft_find_it(string, &next, c);
		tmp = ft_strsub(string, 0, next);
		ft_realloc(&tabl, tmp);
		free(tmp);
		tmp = ft_strdup(string + next);
		free(string);
		string = tmp;
		ft_rm_char(&string, c);
	}
	return (tabl);
}
