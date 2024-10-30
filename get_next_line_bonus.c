/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:59:35 by mdursun           #+#    #+#             */
/*   Updated: 2024/10/28 20:59:35 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_file	*get_file_fd(int fd, t_file **file_tracker)
{
	t_file	*current_file;
	t_file	*new_file;

	current_file = *file_tracker;
	while (current_file)
	{
		if (current_file->fd == fd)
			return (current_file);
		current_file = current_file->next;
	}
	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->fd = fd;
	new_file->buffer_i = 0;
	new_file->buffer_size = 0;
	new_file->next = *file_tracker;
	*file_tracker = new_file;
	return (new_file);
}

static ssize_t	read_the_file(t_file *f)
{
	ft_bzero(f->buffer, BUFFER_SIZE);
	f->buffer_size = read(f->fd, f->buffer, BUFFER_SIZE);
	f->buffer_i = 0;
	return (f->buffer_size);
}

static char	*append_line(char *line, char *buffer)
{
	char	*new_line;
	size_t	line_len;

	if (!line)
		line_len = 0;
	else
		line_len = ft_strlen(line);
	new_line = malloc(line_len + 2);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (line)
	{
		ft_strncpy(new_line, line, line_len);
		free(line);
	}
	new_line[line_len] = *buffer;
	new_line[line_len + 1] = '\0';
	return (new_line);
}

static void	clear_file(t_file **file_tracker, int fd)
{
	t_file	*current;
	t_file	*prev;

	current = *file_tracker;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*file_tracker = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	static t_file	*file_tracker;
	char			*line;
	t_file			*file;
	ssize_t			bytes_read;

	line = NULL;
	file = get_file_fd(fd, &file_tracker);
	if (!file)
		return (NULL);
	while (1)
	{
		if (file->buffer_i >= file->buffer_size)
		{
			bytes_read = read_the_file(file);
			if (bytes_read < 0)
				return (free(line), clear_file(&file_tracker, fd), NULL);
			if (bytes_read == 0)
				return (clear_file(&file_tracker, fd), line);
		}
		line = append_line(line, &file->buffer[file->buffer_i]);
		if (!line)
			return (clear_file(&file_tracker, fd), NULL);
		if (file->buffer[file->buffer_i++] == '\n')
			return (line);
	}
}
