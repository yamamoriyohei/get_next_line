/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamamor <yyamamor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:51:37 by yyamamor          #+#    #+#             */
/*   Updated: 2026/05/10 18:10:19 by yyamamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_to_save(int fd, char *save)
{
	char	*buff;
	int		b;

	buff = malloc(BUFFER_SIZE + 1);
	b = 1;
	while (buff && !ft_strchr(save, '\n') && b != 0)
	{
		b = read(fd, buff, BUFFER_SIZE);
		if (b == -1)
			break ;
		buff[b] = '\0';
		save = ft_strjoin(save, buff);
		if (!save)
			break ;
	}
	if (!buff || b == -1)
	{
		free(save);
		save = NULL;
	}
	free(buff);
	return (save);
}

char	*ft_extract_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_clean_save(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = malloc(ft_strlen(save) - i + 1);
	if (!new_save)
	{
		free(save);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_to_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_extract_line(save);
	if (!line)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = ft_clean_save(save);
	return (line);
}