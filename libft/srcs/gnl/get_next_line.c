/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:24:05 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/25 18:13:47 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nl_chr(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (NULL);
}

static char	*all(char **buf, char **rest)
{
	*buf = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!*buf)
		return (NULL);
	if (!*rest)
	{
		*rest = ft_strdup("");
		if (!*rest)
		{
			free(*buf);
			return (NULL);
		}
	}
	return (*rest);
}

static char	*fill_rest(char **rest, t_newstr *line)
{
	t_newstr	newrest;

	newrest.len = ft_strlen(*rest) - line->len;
	newrest.str = ft_substr(*rest, line->len + 1, newrest.len);
	if (!newrest.str)
		free(line->str);
	return (free_replace(rest, newrest.str));
}

static char	*fill_line(char **rest, char *nl_ptr)
{
	t_newstr	line;

	line.str = NULL;
	if (nl_ptr)
	{
		line.len = nl_ptr - *rest;
		line.str = ft_substr(*rest, 0, line.len + 1);
		if (!line.str)
			return (free_replace(rest, NULL));
		fill_rest(rest, &line);
		if (!rest)
			return (NULL);
	}
	else
	{
		line.str = ft_strdup(*rest);
		free_replace(rest, NULL);
		if (!line.str)
			return (NULL);
	}
	return (line.str);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*rest[PATH_MAX];
	char		*nl_ptr;
	ssize_t		ret;

	nl_ptr = NULL;
	ret = 1;
	while (ret && !nl_ptr)
	{
		if (fd < 0 || fd > PATH_MAX || BUFFER_SIZE < 1 || !all(&buf, &rest[fd]))
			return (NULL);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0 || (ret == 0 && !*rest[fd]))
		{
			free(buf);
			return (free_replace(&rest[fd], NULL));
		}
		buf[ret] = '\0';
		free_replace(&rest[fd], ft_strjoin(rest[fd], buf));
		free(buf);
		if (!rest[fd])
			return (NULL);
		nl_ptr = nl_chr(rest[fd]);
	}
	return (fill_line(&rest[fd], nl_ptr));
}
