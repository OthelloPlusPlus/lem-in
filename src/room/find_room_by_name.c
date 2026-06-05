/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_room_by_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:21:26 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:08:42 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

t_room*	find_room_by_name(t_room* list, char* name)
{
	while (list != NULL)
	{
		if (ft_strcmp(name, list->name) == 0)
			break ;
		list = list->next;
	}
	return (list);
}
