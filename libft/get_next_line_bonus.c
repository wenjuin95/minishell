/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:38:28 by welow             #+#    #+#             */
/*   Updated: 2024/01/28 23:04:37 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *line, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	free(line);
	return (tmp);
}

char	*create_line(int fd, char *line)
{
	char	*buffer;
	int		read_byte;

	if (!line)
	{
		line = malloc(1);
		line[0] = '\0';
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (!ft_strchr(line, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		line = ft_strjoin_free(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_only_next_line(char *line)
{
	int		i;
	char	*line_with_nl;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line [i] != '\n')
		i++;
	line_with_nl = ft_substr(line, 0, i + 1);
	if (!line_with_nl)
	{
		free(line_with_nl);
		return (NULL);
	}
	return (line_with_nl);
}

char	*new_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line[fd], 0) < 0)
		return (NULL);
	line[fd] = create_line(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	next_line = get_only_next_line(line[fd]);
	line[fd] = new_line(line[fd]);
	return (next_line);
}
