#include "libso_long.h"

char	**get_map(char *filename, int height)
{
	char	**map;
	char	*line;
	int	fd;
	int	i;

	if (!filename)
		return (NULL);
	map = (char **)ft_memalloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Open failed!\n");
		return (NULL);
	}
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map[i] = ft_strdup(line);
		free(line);
		i += 1;
	}
	map[i] = NULL;
	close (fd);
	return (map);
}
