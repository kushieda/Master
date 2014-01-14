/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 05:08:48 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 07:40:30 by jyim             ###   ########.fr       */
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

void		up_key(t_env *e, int keycode)
{
	double		i;

	if (keycode == 0)
		i = 0.0;
	else if (keycode == 1)
		i = 0.3;
	if (e->map[(int)e->posy][(int)(e->posx + e->dirx
				* (e->movespeed + 0.3))] == 0)
		e->posx += e->dirx * (e->movespeed + i);
	if (e->map[(int)(e->posy + e->diry
				* (e->movespeed + 0.3))][(int)e->posx] == 0)
		e->posy += e->diry * (e->movespeed + i);
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
