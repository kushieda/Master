/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 04:15:14 by jyim              #+#    #+#             */
/*   Updated: 2014/01/14 00:55:20 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int		ft_event(int keycode, t_env *e)
{
	double				oldirx;
	double				olplanex;
	static int			i;

	if (keycode == 32)
		e->test2 = e->test2 == 0 ? 1 : 0;
	if (e->test2 == 1)
	{
	if (keycode == 65505)
		i = i == 0 ? 1 : 0;
	e->test = i == 0 ? 0 : 1;
	printf("keycode = %d\n", keycode);
	if ((keycode == LEFT || keycode == 97))
		left_key(&oldirx, &olplanex, e);
	if ((keycode == RIGHT || keycode == 100))
		right_key(&oldirx, &olplanex, e);
	if ((keycode == UP || keycode == 119))
		up_key(e, i);
	if ((keycode == DOWN || keycode == 115))
		down_key(e);
	}
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
	static	int		i;

	i = 0;
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
	if (e->test2 == 0)
		mlx_put_image_to_window(e->init, e->win, e->img3, 0, 0);
	else
	{
	mlx_put_image_to_window(e->init, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->init, e->win, e->img2, 0, 950);
	}
	if (e->test == 1)
		mlx_string_put(e->init, e->win, 10, 980, RED, "SPEED : ON");
	else
		mlx_string_put(e->init, e->win, 10, 980, RED, "SPEED : OFF");
	return (0);
}

int		main(void)
{
	t_env	*e;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	e = (t_env *)malloc(sizeof(t_env));
	e->init = mlx_init();
	e->win = mlx_new_window(e->init, 1000, 1000, "wolf");
	e->img = mlx_new_image(e->init, WIDTH, HEIGHT);
	e->img2 = mlx_new_image(e->init, 200, 50);
	e->img3 = mlx_xpm_file_to_image(e->init, "terre", &i, &i2);
	mlx_put_image_to_window(e->init, e->win, e->img3, 0, 0);
	e->str = mlx_get_data_addr(e->img, &(e->bpp), &(e->sl), &(e->nd));
	ft_initgame(e);
	ft_raycaster(e);
	mlx_expose_hook(e->win, &ft_main_event, e);
	mlx_put_image_to_window(e->init, e->win, e->img3, 0, 0);
	mlx_hook(e->win, 2, 3, &ft_event, e);
	mlx_loop(e->init);
	return (0);
}
