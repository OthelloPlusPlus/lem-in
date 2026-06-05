/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_room_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:31:11 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/18 21:38:21 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include <libft.h>

bool	valid_room_name(const char* str)
{
	if (*str == MOVE_FLAG)
		return (false);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		++str;
	}
	return (true);
}
