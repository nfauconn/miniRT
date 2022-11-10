/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:18:31 by noe               #+#    #+#             */
/*   Updated: 2022/11/10 17:08:59 by noe              ###   ########.fr       */
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
		if ((i < 3 && !ft_strncmp(line, elems[i], 1)
			&& ft_iswhitespace(line[1]))
			|| (i >= 3 && !ft_strncmp(line, elems[i], 2)
			&& ft_iswhitespace(line[2])))
			return (i);
		i++;
	}
	return (-1);
}

static size_t	go_trough_whitespaces(char *line, size_t i)
{
	while (ft_iswhitespace(line[i]))
		i++;
	return (i);
}

static t_bool	check_id(char *line, size_t *i)
{
	if (line[*i] == 'A' || line[*i] == 'C' || line[*i] == 'L')
		(*i)++;
	else
	{
		(*i)++;
		if (line[*i])
			(*i)++;
		else
			return (1);
	}
	if (!ft_iswhitespace(line[*i]))
		return (1);
	(*i) = go_trough_whitespaces(line, *i);
	return (0);
}

t_bool	lex_line(char *line, size_t i)
{
	while (ft_isdigit(line[i]) || line[i] == '-')
	{
		if (ft_isdigit(line[i]))
			i++;
		if (line[i] == '.' || line[i] == ',')
		{
			i++;
			if (!ft_isdigit(line[i]) && line[i] != '-')
				return (1);
		}
		if (line[i] == '-')
		{
			if (!ft_iswhitespace(line[i - 1]) && line[i - 1] != ',')
				return (1);
			i++;
			if (!ft_isdigit(line[i]))
				return (1);
		}
		i = go_trough_whitespaces(line, i);
	}
	if (line[i] && line[i] != '\n')
		return (1);
	return (0);
}

t_bool	parse_line(char *line, t_scene *scene)
{
	t_bool		ret;
	size_t		i;
	ssize_t		elem_index;
	char		**params;

	if (!ft_strcmp(line, "\n") || !ft_strncmp(line, "#", 1))
		return (0);
	i = 0;
	elem_index = find_line_elem(line);
	if (elem_index < 0 || check_id(line, &i) || lex_line(line, i))
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
	ret = 0;
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(line, scene);
		free(line);
		if (ret)
			break ;
		line = get_next_line(fd);
	}
	if (!ret && (!scene->A || !scene->C))
		ret = error_display("scene needs at least ambiant light and camera");
	close(fd);
	return (ret);
}
