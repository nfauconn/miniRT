/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:11:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/25 18:22:35 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	correct_filename(char *s)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (!ft_strend_cmp(s, ".rt"))
		return (0);
	i = 0;
	while (s[i] && i < len - 3)
	{
		if (!is_identifier(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static ssize_t	find_line_elem(char *line)
{
	ssize_t		i;
	static char	*elems[7] = {"A ", "C ", "L ", "pl ", "sp ", "cy ", 0};

	if (!*line)
		return (-1);

	i = 0;
	while (elems[i])
	{
		if (i < 3 && !ft_strncmp(line, elems[i], 2))
			return (i);
		else if (i > 3 && !ft_strncmp(line, elems[i], 3))
			return (i);
		i++;
	}
	return (-1);
	//verifier que pas 2fois
}

void	parse(char *scene)
{
	int		fd;
	char	*line;
	ssize_t	elem_index;

	if (!correct_filename(scene))
		exit(error_display("invalid scene file -> format : *.rt"));
	fd = open(scene, O_RDONLY);
	if (fd < 0)
		exit(error_display(strerror(errno)));
	line = get_next_line(fd);
	while (line)
	{
		//index permettant de savoir si les 5 elements sont contenus
		elem_index = find_line_elem(line);
		if (elem_index < 0 && ft_strcmp(line, "\n"))
			exit(error_display("parsing error"));
		line = get_next_line(fd);
	}
	//if index ok
}
