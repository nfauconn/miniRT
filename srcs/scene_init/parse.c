/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:18:31 by noe               #+#    #+#             */
/*   Updated: 2022/11/07 22:43:51 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	correct_filename(char *s)
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
		if ((i < 3 && !ft_strncmp(line, elems[i], 2))
			|| (i > 3 && !ft_strncmp(line, elems[i], 3)))
			return (i);
		i++;
	}
	return (-1);
}

t_bool	lex_line(char *line)
{
	while (*line)
	{
		while (ft_iswhitespace(*line))
			line++;
		if (!ft_isdigit(*line))
			return (1);
		while (ft_isdigit(*line) || *line == '.' || *line == ',')
			line++;
	}
	return (0);
}

t_bool	parse_line(char *line, t_scene *scene)
{
	ssize_t		elem_index;
	char		**params;

	elem_index = find_line_elem(line);
	if (elem_index < 0 && ft_strcmp(line, "\n"))
		return (1);
	if (lex_line(line))
		return (1);
	params = ft_split_whitespace(line);
	scene->fill_params[elem_index](scene, params);
	//call initializer with func ptr, taking scene as parameter
	return (0);
}

void	parse(char *file, t_scene *scene)
{
	int			fd;
	t_bool		ret;
	char		*line;

	if (!correct_filename(file))
		exit_clear(error_display("invalid scene file\nformat : *.rt"), scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_clear(error_display(strerror(errno)), scene);
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(line, scene);
		free(line);
		if (ret)
			exit_clear(error_display("parsing error\n"), scene);
		line = get_next_line(fd);
	}
	//if index ok
}
