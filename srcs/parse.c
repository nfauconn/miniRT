/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:45:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/03 18:40:40 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
}

bool	parse_line(t_scene *scene, char *line)
{
	bool	ret;

	*elem_index = find_line_elem(line);
	if (*elem_index < 0 && ft_strcmp(line, "\n"))
		return(error_display("parsing error"));
	return (0);
}

t_scene	parse(char *scene)
{
	int			fd;
	char		*line;
	ssize_t		elem_index;
	t_scene		scene;

	if (!correct_filename(scene))
		exit(error_display("invalid scene file\nformat : *.rt"));
	fd = open(scene, O_RDONLY);
	if (fd < 0)
		exit(error_display(strerror(errno)));
	line = get_next_line(fd);
	elem_index = -1;
	while (line)
	{
		parse_line(&scene, line);
		free(line);
		line = get_next_line(fd);
	}
	return (scene);
	//if index ok
}

// NE PAS OUBLIER :
//	- verif que les 3 elements uniques sont contenus 1 seule fois