/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yomoon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 22:12:14 by yomoon            #+#    #+#             */
/*   Updated: 2020/09/19 23:31:55 by yomoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				check_return(char **backup, char **line)
{
	char		*enter_point;
	char		*tmp;

	enter_point = ft_strchr(*backup, '\n');
	if (enter_point != 0)
	{
		*line = ft_strndup(*backup, enter_point - *backup);
		tmp = ft_strndup(enter_point + 1, ft_strlen(enter_point + 1));
		if (*backup != 0)
			free(*backup);
		*backup = tmp;
		return (1);
	}
	else
	{
		*line = ft_strndup(*backup, ft_strlen(*backup));
		free(*backup);
		*backup = 0;
		return (0);
	}
}

int				get_next_line(int fd, char **line)
{
	static char	*backup[OPEN_MAX];
	char		*store;
	char		*tmp;
	int			read_size;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	store = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!store)
		return (-1);
	while ((read_size = read(fd, store, BUFFER_SIZE)) >= 0)
	{
		store[read_size] = '\0';
		tmp = ft_strjoin(backup[fd], store);
		if (backup[fd])
			free(backup[fd]);
		backup[fd] = tmp;
		if (ft_strchr(backup[fd], '\n') || read_size == 0)
			break ;
	}
	free(store);
	store = 0;
	if (read_size < 0)
		return (-1);
	return (check_return(&backup[fd], line));
}
