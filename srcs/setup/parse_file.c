/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:18:31 by noe               #+#    #+#             */
/*   Updated: 2022/11/08 19:34:34 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static ssize_t	find_line_elem(char *line)
{
	ssize_t		i;
	static char	*elems[7] = {"A", "C", "L", "pl", "sp", "cy", 0};

	if (!*line)
		return (-1);
	i = 0;
	while (elems[i])
	{
		if ((i < 2 && !ft_strncmp(line, elems[i], 1)
			&& ft_iswhitespace(line[1]))
			|| (i > 2 && !ft_strncmp(line, elems[i], 2) 
			&& ft_iswhitespace(line[2])))
			return (i);
		i++;
	}
	return (-1);
}

static t_bool	check_id(char **line)
{
	if (**line == 'A' || **line == 'C' || **line == 'L')
		(*line)++;
	else
		(*line) += 2 * sizeof (char);
	if (!ft_iswhitespace(**line))
		return (1);
	return (0);
}

t_bool	lex_line(char *line)
{
	if (check_id(&line) == FAIL)
		return (1);
	while (*line)
	{
		if (*line == '\n')
			return (0);
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
	t_bool		ret;
	ssize_t		elem_index;
	char		**params;

	if (!ft_strcmp(line, "\n") || !ft_strncmp(line, "#", 1))
		return (0);
	elem_index = find_line_elem(line);
	if (elem_index < 0 || lex_line(line))
		return (error_display("invalid line in file"));
	params = ft_split_whitespace(line);
	if (!params)
		return(error_display("malloc error"));
	ret = scene->fill_params[elem_index](scene, params);
	ft_strarrayclear(&params);
	return (ret);
}

t_bool	parse_file(char *file, t_scene *scene)
{
	int			fd;
	t_bool		ret;
	char		*line;

	if (!ft_strend_cmp(file, ".rt"))
		return (error_display("invalid scene file\nformat : *.rt"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_display(strerror(errno)));
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(line, scene);
		free(line);
		if (ret)
			exit_clear(ret, scene);
		line = get_next_line(fd);
	}
	//if (all essential params ok)
		ret = 0;
	close(fd);
	return (ret);
}
