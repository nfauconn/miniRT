/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:18:31 by noe               #+#    #+#             */
/*   Updated: 2023/01/12 16:36:32 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

static ssize_t	find_line_elem(char **line)
{
	ssize_t		i;
	static char	*elems[7] = {"A", "C", "L", "pl", "sp", "cy", 0};

	if (!**line)
		return (-1);
	i = 0;
	while (elems[i])
	{
		if ((i < 3 && !ft_strncmp(*line, elems[i], 1)
				&& ft_iswhitespace((*line)[1]))
				|| (i >= 3 && !ft_strncmp(*line, elems[i], 2)
				&& ft_iswhitespace((*line)[2])))
		{
			while (ft_isalpha(**line))
				(*line)++;
			while (ft_iswhitespace(**line))
				(*line)++;
			return (i);
		}
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

bool	lex_line(char *line, size_t i)
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

bool	parse_line(char *line, t_scene *scene)
{
	char		*start;
	bool		ret;
	size_t		i;
	ssize_t		elem_index;
	char		**params;

	if (!ft_strcmp(line, "\n") || !ft_strncmp(line, "#", 1))
		return (0);
	i = 0;
	start = line;
	elem_index = find_line_elem(&line);
	if (elem_index < 0 || lex_line(line, i))
		return (error_display("invalid line in file"));
	line = start;
	params = ft_split_whitespace(line);
	if (!params)
		return (error_display("malloc error"));
	ret = scene->fill_params[elem_index](scene, params);
	ft_strarrayclear(&params);
	return (ret);
}

bool	parse_file(char *file, t_scene *scene)
{
	int			fd;
	bool		ret;
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
	if (!ret && (!scene->amblight || !scene->cam))
		ret = error_display("scene needs at least ambiant light and camera");
	close(fd);
	return (ret);
}
