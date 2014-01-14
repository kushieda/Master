

#include "wolf3d.h"

static void		ft_findnext(char *s, int *next, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	*next = i;
}

static void		ft_freetabstr(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

static void		ft_realloctabstr(char ***tab, char *s)
{
	char		**tmp;
	int			i;

	i = 0;
	while ((*tab)[i])
		i++;
	tmp = (char**)malloc(sizeof(char*) * (i + 2));
	tmp[i + 1] = 0;
	i = 0;
	while ((*tab)[i])
	{
		tmp[i] = ft_strdup((*tab)[i]);
		i++;
	}
	tmp[i] = ft_strdup(s);
	ft_freetabstr(tab);
	*tab = tmp;
}

char			**ft_strsplit2(char *s, char c)
{
	char		**tabstr;
	char		*tmp;
	int			next;

	tabstr = (char**)malloc(sizeof(char*) * 1);
	tabstr[0] = 0;
	ft_strtrim2(&s, c);
	next = 0;
	while (*s)
	{
		ft_findnext(s, &next, c);
		tmp = ft_strsub(s, 0, next);
		ft_realloctabstr(&tabstr, tmp);
		free(tmp);
		tmp = ft_strdup(s + next);
		free(s);
		s = tmp;
		ft_strtrim2(&s, c);
	}
	return (tabstr);
}
