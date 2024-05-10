/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisriver <lisriver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:38:53 by lisriver          #+#    #+#             */
/*   Updated: 2024/04/06 15:21:52 by lisriver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*joinandfree(char *result, char *buffer)
{
	char	*line;

	line = ft_strjoin(result, buffer);
	free(result);
	return (line);
}

char	*read_file(int fd, char *result)
{
	int		byte_read;
	char	*buffer;

	if (!result)
		result = ft_calloc(1, sizeof(char));
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
	{
		free(result);
		return (NULL);
	}
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		buffer[byte_read] = '\0';
		result = joinandfree(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*liner(char **buffer)
{
	char	*new_line;
	int		len;

	len = 0;
	if ((*buffer)[len] == 0)
		return (NULL);
	while ((*buffer)[len] != '\n' && (*buffer)[len] != '\0')
		len++;
	len++;
	new_line = ft_substr(*buffer, 0, len);
	if (new_line == NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (new_line);
}

char	*next_line(char *buffer, int *err)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	if (buffer == NULL)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	next = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!next)
	{
		*err = 1;
		return (free(buffer), NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		next[j++] = buffer[i++];
	next[j] = '\0';
	free(buffer);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*result[1024];
	char		*new_line;
	int			err;

	err = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (result[fd])
		{
			free(result[fd]);
			result[fd] = NULL;
		}
		return (NULL);
	}
	result[fd] = read_file(fd, result[fd]);
	if (!result[fd])
		return (NULL);
	new_line = liner(&result[fd]);
	result[fd] = next_line(result[fd], &err);
	if (err == 1)
		return (free(new_line), NULL);
	return (new_line);
}
