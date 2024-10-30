/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:01:28 by mdursun           #+#    #+#             */
/*   Updated: 2024/10/28 21:01:28 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <libc.h>

typedef struct s_file
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	ssize_t			buffer_i;
	ssize_t			buffer_size;
	struct s_file	*next;
}				t_file;

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strncpy(char *dst, char *src, size_t len);
void	ft_bzero(void *s, size_t n);

#endif