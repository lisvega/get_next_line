/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisriver <lisriver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:47:39 by lisriver          #+#    #+#             */
/*   Updated: 2024/04/14 15:15:44 by lisriver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*liner(char **result)
{
	char	*new_line;
	int		len;

	len = 0;
	if ((*result)[len] == 0)
		return (NULL);
	while ((*result)[len] != '\n' && (*result)[len] != '\0')
		len++;
	len++;
	new_line = ft_substr(*result, 0, len);
	if (new_line == NULL)
	{
		free(*result);
		*result = NULL;
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
	static char	*result;
	char		*new_line;
	int			err;

	err = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (result)
		{
			free(result);
			result = NULL;
		}
		return (NULL);
	}
	result = read_file(fd, result);
	if (!result)
		return (NULL);
	new_line = liner(&result);
	result = next_line(result, &err);
	if (err == 1)
		return (free(new_line), NULL);
	return (new_line);
}
/*  int main()
{
	int fd;
	char *result;
	int i;
	
	i = 0;
	fd = open("multiple_nl.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	result = get_next_line(fd);
	while (result != NULL)
	{
		printf("linea %d %s", i + 1, result);
		free(result);
		i++;
		result = get_next_line(fd);
	}

	close(fd);
	return (0);
} */