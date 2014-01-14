/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 05:08:48 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 05:19:50 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		left_key(double *oldirx, double *olplanex, t_env *e)
{
	*oldirx = e->dirx;
	e->dirx = e->dirx * cos(e->rotspeed) - e->diry * sin(e->rotspeed);
	e->diry = *oldirx * sin(e->rotspeed) + e->diry * cos(e->rotspeed);
	*olplanex = e->planex;
	e->planex = e->planex * cos(e->rotspeed) - e->planey * sin(e->rotspeed);
	e->planey = *olplanex * sin(e->rotspeed) + e->planey * cos(e->rotspeed);
}

void		right_key(double *oldirx, double *olplanex, t_env *e)
{
	*oldirx = e->dirx;
	e->dirx = e->dirx * cos(-(e->rotspeed)) - e->diry * sin(-(e->rotspeed));
	e->diry = *oldirx * sin(-(e->rotspeed)) + e->diry * cos(-(e->rotspeed));
	*olplanex = e->planex;
	e->planex = e->planex * cos(-(e->rotspeed))
		- e->planey * sin(-(e->rotspeed));
	e->planey = *olplanex * sin(-(e->rotspeed))
		+ e->planey * cos(-(e->rotspeed));
}

void		up_key(t_env *e)
{
	if (e->map[(int)e->posy][(int)(e->posx + e->dirx
				* (e->movespeed + 0.3))] == 0)
		e->posx += e->dirx * e->movespeed;
	if (e->map[(int)(e->posy + e->diry
				* (e->movespeed + 0.3))][(int)e->posx] == 0)
		e->posy += e->diry * e->movespeed;
}

void		down_key(t_env *e)
{
	if (e->map[(int)e->posy][(int)(e->posx - e->dirx
				* (e->movespeed + 0.3))] == 0)
		e->posx -= e->dirx * e->movespeed;
	if (e->map[(int)(e->posy - e->diry
				* (e->movespeed + 0.3))][(int)e->posx] == 0)
		e->posy -= e->diry * e->movespeed;
}
