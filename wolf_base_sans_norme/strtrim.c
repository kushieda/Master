
#include "wolf3d.h"

void		ft_strtrim2(char **s, char c)
{
	unsigned int	start;
	unsigned int	end;
	char			*tmp;

	start = 0;
	while ((*s)[start] && (*s)[start] == c)
		start++;
	end = ft_strlen(*s);
	if (start == end)
	{
		free(*s);
		*s = ft_strdup("");
	}
	else
	{
		end--;
		while (end && (*s)[end] == c)
			end--;
		end++;
		tmp = ft_strsub(*s, start, end - start);
		*s = tmp;
	}
}
