/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 04:56:58 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 04:56:59 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_rm_char(char **str, char c)
{
	unsigned int	start;
	unsigned int	end;
	char			*tmp;

	start = 0;
	while ((*str)[start] && (*str)[start] == c)
		start++;
	end = ft_strlen(*str);
	if (start == end)
	{
		free(*str);
		*str = ft_strdup("");
	}
	else
	{
		end--;
		while (end && (*str)[end] == c)
			end--;
		end++;
		tmp = ft_strsub(*str, start, end - start);
		*str = tmp;
	}
}
