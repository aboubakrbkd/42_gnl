/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 23:48:09 by aboukdid          #+#    #+#             */
/*   Updated: 2023/11/30 17:26:16 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_next_line(char *buff)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (buff[i] == '\0')
	{
		free(buff);
		return (NULL);
	}
	next = malloc(ft_strlen(buff) - i + 1);
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (buff[i] != '\0')
		next[j++] = buff[i++];
	next[j] = '\0';
	free(buff);
	return (next);
}

char	*ft_get_line(char *buff)
{
	int		i;
	char	*str;

	i = 0;
	if (!*buff)
		return (NULL);
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	while (buff[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
	{
		str[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_read_line(int fd, char *buff)
{
	char	*str;
	int		line;

	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	line = 1;
	while (line > 0)
	{
		line = read(fd, str, BUFFER_SIZE);
		if (line == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		str[line] = '\0';
		buff = ft_strjoin(buff, str);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(str);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd > OPEN_MAX)
		return (NULL);
	buff[fd] = ft_read_line(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = ft_get_line(buff[fd]);
	buff[fd] = ft_next_line(buff[fd]);
	return (line);
}
