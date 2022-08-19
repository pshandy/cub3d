/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c		                              :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/8/19 12:06:35 by pshandy            #+#    #+#             */
/*   Updated: 2022/8/19 12:06:36 by pshandy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check(char **list, char **line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (*(*list + i) != '\n')
	{
		if (!*(*list + i))
			return (0);
		i++;
	}
	tmp = ft_strdup(*list + i + 1);
	*(*list + i + 1) = '\0';
	*line = ft_strdup(*list);
	free(*list);
	*list = tmp;
	return (1);
}

static int	read_file(int fd, char **list, char **buffer, char **line)
{
	int		bread;
	char	*tmp;

	bread = read(fd, *buffer, BUFFER_SIZE);
	while (bread > 0)
	{
		*(*buffer + bread) = '\0';
		if (*list)
		{
			tmp = *list;
			*list = ft_strjoin(tmp, *buffer);
			free(tmp);
		}
		else
			*list = ft_strdup(*buffer);
		if (check(list, line))
		{
			break ;
		}
		bread = read(fd, *buffer, BUFFER_SIZE);
	}
	free(*buffer);
	return (bread);
}

char	*get_next_line(int fd)
{
	static char	*list[MAX_FD];
	char		*buffer;
	char		*line;

	line = NULL;
	if (fd < 0 || fd > MAX_FD || read(fd, list[fd], 0) < 0)
		return (NULL);
	if (list[fd])
		if (check(&list[fd], &line))
			return (line);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	ft_memset(buffer, 0, (BUFFER_SIZE + 1));
	if (read_file(fd, &list[fd], &buffer, &line) != 0
		|| list[fd] == NULL || list[fd][0] == '\n')
		return (line);
	if (list[fd][0] == '\0')
	{
		free(list[fd]);
		return (NULL);
	}
	line = list[fd];
	list[fd] = NULL;
	return (line);
}
