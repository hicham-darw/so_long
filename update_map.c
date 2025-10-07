#include "libso_long.h"
#include <stdlib.h>

char	**update_map(char **map, int *px, int *py, int key)
{
	int	i;
	char	*pl;

	if (!map || !*map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		if ((pl = ft_strchr(map[i], 'P')))
		{
			*pl = '0';
			if (key == 'A' || key == 'a')
				map[*py][--*px] = 'P';
			else if (key == 'W' || key == 'w')
				map[--*py][*px] = 'P';
			else if (key == 'D' || key == 'd')
				map[*py][++*px] = 'P';
			else
				map[++*py][*px] = 'P';
			break;
		}
		i++;
	}
	return (map);
}
