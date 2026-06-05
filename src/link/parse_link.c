/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:19:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/18 21:41:37 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

static bool	valid_array(char** array);
// static bool	valid_string(char* str);

bool	parse_link(t_farm* farm, char *line)
{
	t_link*	link;
	char**	array;

	if (line[0] == MOVE_FLAG)
		return (false);
	array = ft_split(line, '-');
	if (!valid_array(array))
	{
		ft_free_array(&array);
		return (false);
	}
	link = create_link(array[0], array[1]);
	ft_free_array(&array);
	if (link == NULL)
		error_exit(ERR_CALLOC);
	add_link_to_farm(farm, link);
	return (true);
}

static bool	valid_array(char** array)
{
	if (array == NULL)
		return (false);
	if (ft_array_len((void**)array) != 2)
		return (false);
	return (valid_room_name(array[0]) && valid_room_name(array[1]));
}

// static bool	valid_string(char* str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (!ft_isalnum(str[i]))
// 			return (false);
// 		++i;
// 	}
// 	return (true);
// }
