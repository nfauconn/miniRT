/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:45:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/04 19:05:12 by nfauconn         ###   ########.fr       */
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
		if ((i < 3 && !ft_strncmp(line, elems[i], 2))
			|| (i > 3 && !ft_strncmp(line, elems[i], 3)))
			return (i);
		i++;
	}
	return (-1);
}

bool	parse_line(t_scene *scene, char *line)
{
	bool		ret;
	ssize_t		elem_index;

	elem_index = find_line_elem(line);
	if (elem_index < 0 && ft_strcmp(line, "\n"))
		return(error_display("parsing error"));
	fill_parameters(line, elem_index);
	//call initializer with func ptr, taking scene as parameter
	return (0);
}

t_scene	parse(char *scene)
{
	int			fd;
	bool		ret;
	char		*line;
	t_scene		scene;

	if (!correct_filename(scene))
		exit(error_display("invalid scene file\nformat : *.rt"));
	fd = open(scene, O_RDONLY);
	if (fd < 0)
		exit(error_display(strerror(errno)));
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(&scene, line);
		free(line);
		if (ret < 0)
			exit(error_display("invalid line in file\n");
		line = get_next_line(fd);
	}
	return (scene);
	//if index ok
}

// NE PAS OUBLIER :
//	- verif que les 3 elements uniques sont contenus 1 seule fois

t_scene	set_caracteristics(t_scene *scene)
{

}

t_scene	scene_setup(char *file)
{
	t_scene		scene;
	float		width;
	float		height;

	width = WIDTH;
	height = HEIGHT;

	scene.ratio = width / height;
	scene.height_float = 2.0;
	scene.width_float = scene.ratio * scene.height_float;
	scene.focal_length = (float3){0, 0, 1.0};
	scene.origin = (float3){0, 0, 0};
	scene.width_vec = (float3){scene.width_float, 0, 0};
	scene.height_vec = (float3){0, scene.height_float, 0};
	scene.ll_corner = scene.origin - scene.width_vec/2 - scene.height_vec/2 - scene.focal_length;
	return (scene);
}
