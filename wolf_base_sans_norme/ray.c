
#include "wolf.h"
/*
static void		ft_divcolor(t_env *env)
{
	int		r;
	int		g;
	int		b;

	r = (((env->color & 0xff0000) >> 16) / 2) << 16;
	g = (((env->color & 0xff00) >> 8) / 2) << 8;
	b = ((env->color & 0xff) / 2);
	env->color = 0;
	env->color |= r;
	env->color |= g;
	env->color |= b;
}
*/
static void		ft_line(t_env *env)
{
	env->lineheight = ABS((int)(LON / env->perpwalldist));
	env->drawstart = -(env->lineheight) / 2 + LON / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = env->lineheight / 2 + LON / 2;
	if (env->drawend >= LON)
		env->drawend = LON - 1;
	env->tid = env->map[env->mapy][env->mapx] - 1;
	ft_drawtext(env);
	ft_drawfloor(env);
	/*
	if (env->map[env->mapy][env->mapx] == 1)
		env->color = BROWN;
	else if (env->map[env->mapy][env->mapx] == 2)
		env->color = FUSHIA;
	else if (env->map[env->mapy][env->mapx] == 3)
		env->color = GREEN;
	else if (env->map[env->mapy][env->mapx] == 4)
		env->color = BLUE;
	else if (env->map[env->mapy][env->mapx] == 5)
		env->color = 0xffffff;
	else
		env->color = YELLOW;
	if (env->side == 1)
		ft_divcolor(env);*/
}

void		ft_dda(t_env *env)
{
	while (env->hit == 0)
    {
        if (env->sidedistx < env->sidedisty)
        {
          env->sidedistx += env->ddistx;
          env->mapx += env->stepx;
          env->side = 0;
        }
        else
        {
          env->sidedisty += env->ddisty;
          env->mapy += env->stepy;
          env->side = 1;
        }
        if ((env->mapy < env->nb_l / 2 || env->mapx < env->nb_c / 2) || (env->mapy > 0 || env->mapx > 0))
			if (env->map[env->mapy][env->mapx] > 0) 
        		env->hit = 1;
    }
    if (env->side == 0)
    	env->perpwalldist = ABS((env->mapx - env->rayposx + (1 - env->stepx) / 2) / env->raydirx);
    else
    	env->perpwalldist = ABS((env->mapy - env->rayposy + (1 - env->stepy) / 2) / env->raydiry);
}

void		ft_init(t_env *env)
{
	env->camerax = 2 * (float)env->x / (double)LAR - 1;
	env->rayposx = env->posx;
	env->rayposy = env->posy;
	env->raydirx = env->dirx + env->planex * env->camerax;
	env->raydiry = env->diry + env->planey * env->camerax;
	env->mapx = (int)env->rayposx;
	env->mapy = (int)env->rayposy;
	env->ddistx = sqrt(1 + (env->raydiry * env->raydiry) / (env->raydirx * env->raydirx));
	env->ddisty = sqrt(1 + (env->raydirx * env->raydirx) / (env->raydiry * env->raydiry));
	env->hit = 0;
	if (env->raydirx < 0)
		env->stepx = -1;
	else
		env->stepx = 1;
	if (env->raydiry < 0)
		env->stepy = -1;
	else
		env->stepy = 1;
}

void	raycasting(t_env *env)
{
	env->x = 0;
	while (env->x < LAR)
	{
		ft_init(env);
		if (env->raydirx < 0)
			env->sidedistx = (env->rayposx - env->mapx) * env->ddistx;
		else
			env->sidedistx = (env->mapx + 1.0 - env->rayposx) * env->ddistx;
		if (env->raydiry < 0)
			env->sidedisty = (env->rayposy - env->mapy) * env->ddisty;
		else
			env->sidedisty = (env->mapy + 1.0 - env->rayposy) * env->ddisty;
		if ((env->mapy > env->nb_l || env->mapx > env->nb_c) || (env->mapy < 1 || env->mapx < 1))
        	break ;
		ft_dda(env);
		ft_line(env);
//		ft_draw(env);
		env->x++;
	}
}