/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 22:16:57 by jyim              #+#    #+#             */
/*   Updated: 2014/01/13 05:25:18 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <libft.h>
# include <math.h>
# include <fcntl.h>
# define ABS(x) ((x >= 0) ? x : -(x))
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define WIDTH 1000
# define HEIGHT 1000
# define BLUE 0x0000cc
# define GREEN 0x00cc00
# define BROWN 0xcc6600
# define GRAY 0x999999
# define FUSHIA 0xcc00cc
# define YELLOW 0xcccc00
# define CYAN 0xccffff
# define WHITE 0xffffff
# define RED 0xff0000

typedef struct				s_env
{
	void		*init;
	void		*win;
	void		*img;
	char		*str;
	int			bpp;
	int			sl;
	int			nd;

	/* position et direction du joueur */
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;

	/* MAP */
	int			**map;
	int			mapx;
	int			mapy;
	int			nb_l;
	int			nb_c;

	/* rayon */
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	double		perpwalldist;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	double		camerax;

	/* DRAW */
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
	/* BOLEAN */
	int			hit;
	int			side;
	int			stepx;
	int			stepy;

	/* comteur de pixel jusquq lq largeur max */
	int			x;

	/* event */
	double		movespeed;
	double		rotspeed;
}							t_env;

void	ft_draw(t_env *e);
void	ft_initgame(t_env *e);
void	ft_line(t_env *e);
void	ft_dda(t_env *e);
void	ft_initray(t_env*e);
void	ft_raycaster(t_env *e);
int		**ft_parse(char *file, t_env *map);
char	**ft_splitwolf(char *s, char c);
int		ft_main_event(t_env *e);
void	ft_rm_char(char **str, char c);
void	left_key(double *o, double *op, t_env *e);
void	right_key(double *o, double *op, t_env *e);
void	up_key(t_env *e);
void	down_key(t_env *e);
#endif
