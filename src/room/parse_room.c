/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:24:43 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/19 20:37:26 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

static bool	st_str_is_integer(char* str);
// static bool	st_str_is_alnum(char* str);

bool	parse_room(t_farm* farm, char** array, t_room** dst)
{
	t_room*	room;

	if (!st_str_is_integer(array[1]) || !st_str_is_integer(array[2]))
		return (false);
	// if (!st_str_is_alnum(array[0]))
	if (!valid_room_name(array[0]))
		error_exit(ERR_ROOM_NAME(array[0]));
	if (array[0][0] == MOVE_FLAG)
		error_exit(ERR_ROOM_NAME_L(array[0]));
	room = create_room(array[0], ft_atoi(array[1]), ft_atoi(array[2]));
	if (room != NULL)
		add_room_to_farm(farm, room, dst);
	return (true);
}

// static bool	st_str_is_alnum(char* str)
// {
// 	while (*str)
// 	{
// 		if (!ft_isalnum(*str) && *str != '_')
// 			return (false);
// 		++str;
// 	}
// 	return (true);
// }

static bool	st_str_is_integer(char* str)
{
	u_int32_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		++i;
	}
	return (true);
}
