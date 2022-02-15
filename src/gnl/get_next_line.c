/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:01:58 by tbaharat          #+#    #+#             */
/*   Updated: 2022/02/15 19:56:19 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*remnant_read(char **remnant)
{
	size_t	i;
	char	*line;

	i = 0;
	while ((*remnant)[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while ((*remnant)[i] != '\n')
	{
		line[i] = (*remnant)[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	*remnant = remtrim(*remnant);
	return (line);
}

char	*eof_remnant(char **remnant)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!(*remnant) || !ft_strlen(*remnant))
		return (NULL);
	line = (char *)malloc(sizeof(char) * (ft_strlen(*remnant) + 1));
	if (!line)
		return (NULL);
	while ((*remnant)[i])
	{
		line[i] = (*remnant)[i];
		i++;
	}
	line[i] = '\0';
	free(*remnant);
	*remnant = NULL;
	return (line);
}

char	*fd_read(int fd, char **remnant)
{
	int		rd;
	char	*line;
	char	buf[BUFFER_SIZE + 1];

	rd = 1;
	while (rd)
	{
		if (is_newline(*remnant))
		{
			line = remnant_read(remnant);
			return (line);
		}
		rd = read(fd, buf, BUFFER_SIZE);
		buf[rd] = '\0';
		if (rd < 0)
			return (NULL);
		if (rd > 0)
			*remnant = remstr(buf, *remnant);
	}
	line = eof_remnant(remnant);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remnant[FOPEN_MAX + 1];

	line = NULL;
	if (fd >= 0)
		line = fd_read(fd, &remnant[fd]);
	if (line == NULL)
	{
		free(remnant[fd]);
		remnant[fd] = NULL;
		return (NULL);
	}
	return (line);
}
