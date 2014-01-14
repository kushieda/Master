/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 23:55:28 by ael-kadh          #+#    #+#             */
/*   Updated: 2013/12/30 23:56:38 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

void	ft_putyouwon(t_env *e)
{
	int		width;
	int		height;
	t_img	*xpm;

	xpm = mlx_xpm_file_to_image(e->mlx, "youwon.xpm", &width, &height);
	mlx_put_image_to_window(e->mlx, e->win, xpm, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, xpm, 0, 0);
	sleep(5);
}

void	ft_createplayer(t_env *e)
{
	int		width;
	int		height;
	t_img	*xpm;

	xpm = mlx_xpm_file_to_image(e->mlx, "pics/image.xpm", &width, &height);
	ft_putxpmtodisplay(e, LON - 750, LAR - 640, xpm);
}

int		ft_intdraw(t_env *e)
{
	if (e->posendx == (int)e->posx && e->posendy == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	else if (e->posendx + 1 == (int)e->posx && e->posendy == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	else if (e->posendx == (int)e->posx && e->posendy + 1 == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	else if (e->posendx + 1 == (int)e->posx && e->posendy + 1 == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	else if (e->posendx - 1 == (int)e->posx && e->posendy - 1 == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	else if (e->posendx == (int)e->posx && e->posendy - 1 == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	else if (e->posendx - 1 == (int)e->posx && e->posendy == (int)e->posy)
	{
		if (e->stage != 3)
		{
			e->stage++;
			//ft_putyouwon(e);
			free(e->map);
			init(e);
		}
		else
		{
			//ft_putyouwon(e);
			exit(0);
		}
	}
	/*
	while (e->x < LAR)
	{
		e->color = CYAN;
		e->drawstart = 0;
		e->drawend = LON / 2;
		ft_draw(e);
		e->color = GRAY;
		e->drawstart = LON / 2;
		e->drawend = LON;
		ft_draw(e);
		e->x++;
	} */
	e->x = 0;
    raycasting(e);
    ft_createplayer(e);
    ft_create_minimap(e);
    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
    return (0);
}

int		ft_expose_hook(t_env *e)
{
		e->draw = 1;
		return (0);
}

int		ft_main_hook(t_env *e)
{
	if (e->draw == 1  && e->bol != 1)
	{
		ft_intdraw(e);
		e->draw = 0;
	}
	return (0);
}

int		main(void)
{
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	e->mlx = mlx_init();
	if (e->mlx)
	{
		e->win = mlx_new_window(e->mlx, LAR, LON, "wolf 3D");
		if (e->win)
		{
	    	if ((e->img = mlx_new_image(e->mlx, LAR, LON)) == NULL)
	    		exit(0);
	    	e->str = mlx_get_data_addr(e->img, &(e->bpp), &(e->size_line), &(e->endian));
	    	if (!(e->str))
	    		exit(0);
	    	e->stage = 0;
			init(e);
			mlx_hook(e->win, MotionNotify, PointerMotionMask, mouse_hook, e);
			mlx_hook(e->win, 2, 3, key_hook, e);
	    	mlx_expose_hook(e->win, ft_expose_hook, e);
	    	mlx_mouse_hook(e->win, mouse_click_hook, e);
			mlx_loop_hook(e->mlx, ft_main_hook, e);
			mlx_loop(e->mlx);
		}
	}
	return (0);
}

static void		ft_inittext(t_env *data)
{
	int		height;
	int		width;

	data->text[0] = mlx_xpm_file_to_image(data->mlx, "pics/pierre16.xpm", \
			&width, &height);
	data->text[1] = mlx_xpm_file_to_image(data->mlx, "pics/pierre17.xpm", \
			&width, &height);
	data->text[2] = mlx_xpm_file_to_image(data->mlx, "pics/parquet03.xpm", \
			&width, &height);
	data->text[3] = mlx_xpm_file_to_image(data->mlx, "pics/pavage01.xpm", \
			&width, &height);
	data->text[4] = mlx_xpm_file_to_image(data->mlx, "pics/briques02.xpm", \
			&width, &height);
	data->text[5] = mlx_xpm_file_to_image(data->mlx, "pics/briques02.xpm", \
			&width, &height);
	data->text[6] = mlx_xpm_file_to_image(data->mlx, "pics/ceil.xpm", \
			&width, &height);
	data->text[7] = mlx_xpm_file_to_image(data->mlx, "pics/briques02.xpm", \
			&width, &height);
}

void	init(t_env *e)
{
	Cursor	c;
	char	**tab;

	c = XCreateFontCursor(((t_xvar*)(e->mlx))->display, XC_crosshair);
	XDefineCursor(((t_xvar*)(e->mlx))->display\
			, ((t_xvar*)(e->mlx))->win_list->window, c);
	tab = (char **)malloc(sizeof(char *));
	tab[0] = ft_strdup("a");
	tab[1] = ft_strdup("batman");
	tab[2] = ft_strdup("poney");
	tab[3] = ft_strdup("./map/map1");
	e->map = ft_parse(tab[e->stage], e);
    e->posx = e->posenterx;
    e->posy = e->posentery;
    e->dirx = -1;
    e->diry = 0;
    e->planex = 0;
    e->planey = 0.66;
    e->rotspeed = 0.1;
    e->draw = 1;
    e->bol = 0;
    ft_inittext(e);
}