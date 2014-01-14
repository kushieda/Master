/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 05:09:51 by jyim              #+#    #+#             */
/*   Updated: 2014/01/12 07:23:10 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_line(t_env *e)
{
	e->lineheight = ABS((int)(HEIGHT / e->perpwalldist));
	e->drawstart = (-(e->lineheight) / 2) + (HEIGHT / 2);
	if (e->drawstart < 0)
		e->drawstart = 0;
	e->drawend = (e->lineheight / 2) + (HEIGHT / 2);
	if (e->drawend > HEIGHT)
		e->drawend = HEIGHT -1;
	if (e->map[e->mapy][e->mapx] == 1)
		e->color = RED;
	else if (e->map[e->mapy][e->mapx] == 2)
		e->color = BLUE;
	else if (e->map[e->mapy][e->mapx] == 3)
		e->color = GREEN;
	else if (e->map[e->mapy][e->mapx] == 4)
		e->color = BROWN;
	else
		e->color = YELLOW;
	if (e->side == 1)
		e->color /= 2;
}

void		ft_dda(t_env *e)
{
	while (e->hit == 0)
	{
		if (e->sidedistx < e->sidedisty)
		{
			e->sidedistx += e->deltadistx;
			e->mapx += e->stepx;
			e->side = 0;
		}
		else
		{
			e->sidedisty += e->deltadisty;
			e->mapy += e->stepy;
			e->side = 1;
		}
		if (e->map[e->mapy][e->mapx] > 0)
			e->hit = 1;
	}
	if (e->side == 0)
		e->perpwalldist = fabs(((double)e->mapx - e->rayposx + (double)(1 - e->stepx) / 2) / e->raydirx);
	else
		e->perpwalldist = fabs(((double)e->mapy - e->rayposy + (double)(1 - e->stepy) / 2) / e->raydiry);
}

void		ft_initray(t_env *e)
{
	e->camerax = (double)(2 * e->x) / (double)WIDTH - 1.0;
	e->rayposx = e->posx;
	e->rayposy = e->posy;
	e->raydirx = e->dirx + e->planex * e->camerax;
	e->raydiry = e->diry + e->planey * e->camerax;
	e->mapx = (int)(e->rayposx);
	e->mapy = (int)(e->rayposy);
	e->deltadistx = sqrt(1 + (e->raydiry * e->raydiry) / (e->raydirx * e->raydirx));
	e->deltadisty = sqrt(1 + (e->raydirx * e->raydirx) / (e->raydiry * e->raydiry));
	e->hit = 0;

	if (e->raydirx < 0)
	{
		e->stepx = -1;
		e->sidedistx = (e->rayposx - (double)e->mapx) * e->deltadistx;
	}
	else
	{
		e->stepx = 1;
		e->sidedistx = ((double)(e->mapx + 1.0) - e->rayposx) * e->deltadistx;
	}
	if (e->raydiry < 0)
	{
		e->stepy = -1;
		e->sidedisty = (e->rayposy - (double)e->mapy) * e->deltadisty;
	}
	else
	{
		e->stepy = 1;
		e->sidedisty = ((double)(e->mapy + 1.0) - e->rayposy) * e->deltadisty;
	}
}

void		ft_raycaster(t_env *e)
{
	e->x = 0;
	while (e->x < WIDTH)
	{
		ft_initray(e);
		ft_dda(e);
		ft_line(e);
		ft_draw(e);
		e->x++;
	}
}
