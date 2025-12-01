/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:11:47 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/03/21 14:15:24 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_and_free(char *buff, char *new)
{
	char	*temp;

	temp = ft_strjoin(buff, new);
	free(buff);
	return (temp);
}

/* Reads BUFFER_SIZE bytes and joins to buff 
until buff contains newline character*/
char	*read_til_newline(int fd, char *buff)
{
	char	*new_block;
	int		rd_bytes;

	if (!buff)
	{
		buff = (char *)malloc(1 * sizeof(char));
		buff[0] = '\0';
	}
	new_block = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_block)
		return (NULL);
	rd_bytes = 1;
	while (rd_bytes > 0 && !ft_strchr(buff, '\n'))
	{
		rd_bytes = read(fd, new_block, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(new_block);
			return (NULL);
		}
		new_block[rd_bytes] = '\0';
		buff = join_and_free(buff, new_block);
	}
	free(new_block);
	return (buff);
}

/* gets the first line from the static buffer */
char	*get_first_line(const char *buff)
{
	char	*new;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(*new) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		new[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		new[i] = buff[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*push_to_next(char *buff)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	new_buff = (char *)malloc(sizeof(*new_buff) * (ft_strlen(buff) - i + 1));
	if (!new_buff)
		return (NULL);
	i++;
	j = 0;
	while (buff[i])
		new_buff[j++] = buff[i++];
	new_buff[j] = '\0';
	free(buff);
	return (new_buff);
}

/* added an array of static strings to store multiple buffers*/
char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff[fd] = read_til_newline(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	newline = get_first_line(buff[fd]);
	buff[fd] = push_to_next(buff[fd]);
	return (newline);
}
