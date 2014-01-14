/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 07:18:05 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 07:19:34 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	run_key(t_env *e)
{
	if (e->map[(int)e->posy][(int)(e->posx + e->dirx
				* (e->movespeed + 1))] == 0)
		e->posx += e->dirx * e->movespeed;
	if (e->map[(int)(e->posy + e->diry
				* (e->movespeed + 1))][(int)e->posx] == 0)
		e->posy += e->diry * e->movespeed;
}
