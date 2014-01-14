/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 04:15:14 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 05:20:05 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_event(int keycode, t_env *e)
{
	double          oldirx;
	double          olplanex;

	if ((keycode == LEFT || keycode == 97))
		left_key(&oldirx, &olplanex, e);
	if ((keycode == RIGHT || keycode == 100))
		right_key(&oldirx, &olplanex, e);
	if ((keycode == UP || keycode == 119))
		up_key(e);
	if ((keycode == DOWN || keycode == 115))
		down_key(e);
	if (keycode == 65307)
		exit (0);
	ft_main_event(e);
	return (0);
}

void	ft_draw(t_env *e)
{
	int		in;

	while (e->drawstart < e->drawend)
	{
		in = (e->bpp >> 3) * ((e->drawstart * (e->sl >> 2)) + e->x);
		e->str[in + 0] = e->color & 0xff;
		e->str[in + 1] = (e->color & 0xff00) >> 8;
		e->str[in + 2] = (e->color & 0xff0000) >> 16;
		e->drawstart++;
	}
}

void	ft_initgame(t_env *e)
{
	e->map = ft_parse("a", e);
	e->posx = 22.0;
	e->posy = 12.0;
	e->dirx = -1.0;
	e->diry = 0.0;
	e->planex = 0;
	e->planey = 0.66;
	e->movespeed = 0.3;
	e->rotspeed = 0.1;
}

int		ft_main_event(t_env *e)
{
	e->x = 0;
	while (e->x < WIDTH)
	{
		e->drawstart = 0;
		e->drawend = HEIGHT / 2;
		e->color = CYAN;
		ft_draw(e);
		e->drawstart = HEIGHT / 2;
		e->drawend = HEIGHT - 1;
		e->color = GRAY;
		ft_draw(e);
		e->x++;
	}
	e->x = 0;
	ft_raycaster(e);
	mlx_put_image_to_window(e->init, e->win, e->img, 0, 0);
	return (0);
}

int		main(void)
{
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	e->init = mlx_init();
	e->win = mlx_new_window(e->init, WIDTH, HEIGHT, "wolf");
	e->img = mlx_new_image(e->init, WIDTH, HEIGHT);
	e->str = mlx_get_data_addr(e->img, &(e->bpp), &(e->sl), &(e->nd));
	ft_initgame(e);
	ft_raycaster(e);
	mlx_expose_hook(e->win, &ft_main_event, e);
	mlx_hook(e->win, 2, 3, &ft_event, e);
	mlx_loop(e->init);
	return (0);
}
