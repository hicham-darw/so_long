#include "libso_long.h"
#include <stdlib.h>

char	**update_map(char **map, int next_px, int next_py)
{
	int	i;
	char	*pl;

	if (!map || !*map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		if (pl = ft_strchr(map[i], 'P'))
		{
			*pl = '0';
			map[next_py][next_px] = 'P';
			break;
		}
		i++;
	}
	return (map);
}
