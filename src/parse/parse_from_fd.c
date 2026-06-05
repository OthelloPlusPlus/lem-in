/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_from_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:04:43 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/19 20:37:17 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

static void	trim_line(char* line);
static void	parse_command(t_farm* farm, char* line, int fd);
static void	parse_special_room(t_farm* farm, t_room** special, int fd);
static bool	parse_array(t_farm* farm, char** array);

void	parse_from_fd(int fd, t_farm* farm)
{
	char*	line;
	char**	array;
	// static int count = 0;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trim_line(line);
		if (line && line[0])
		{
			if (line[0] == '#')
				parse_command(farm, line, fd);
			else
			{
				array = ft_split(line, ' ');
				if (parse_array(farm, array))
					ft_free_array(&array);
				else
					store_for_later(farm, array);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}

static void	trim_line(char* line)
{
	char*	ptr;

	if (line == NULL)
		return ;
	ptr = ft_strchr(line, '\n');
	if (ptr != NULL)
		ptr[0] = '\0';
	if (ft_strncmp(line, "##", 2) == 0)
		return ;
	ptr = ft_strchr(line, '#');
	if (ptr != NULL)
		ptr[0] = '\0';
}

static void	parse_command(t_farm* farm, char* line, int fd)
{
	if (ft_strcmp(&line[2], "start") == 0)
		parse_special_room(farm, &farm->rooms.start, fd);
	else if (ft_strcmp(&line[2], "end") == 0)
		parse_special_room(farm, &farm->rooms.end, fd);
}

static void	parse_special_room(t_farm* farm, t_room** special, int fd)
{
	char*	line;
	char**	array;
	int		len;

	line = get_next_line(fd);
	if (line == NULL)
		return ;
	trim_line(line);
	array = ft_split(line, ' ');
	free(line);
	if (array == NULL)
		error_exit(ERR_CALLOC);
	len = ft_array_len((void**)array);
	if (len != 3 || !parse_room(farm, array, special))
		error_exit(ERR_ROOM_SPECIAL(array[0]));
	ft_free_array(&array);
}

static bool	parse_array(t_farm* farm, char** array)
{
	int	len;

	len = ft_array_len((void **)array);
	if (len == 1 && parse_ant(farm, array[0]))
		return (true);
	if (len == 3 && parse_room(farm, array, NULL))
		return (true);
	if (len == 1 && parse_link(farm, array[0]))
		return (true);
	return (false);
}
