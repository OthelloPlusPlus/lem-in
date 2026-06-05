/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:16:48 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:06:09 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

void	valid_farm(t_farm* farm)
{
	if (farm->ants.count <= 0)
		error_exit(ERR_ANTCOUNT(farm->ants.count));
	if (farm->rooms.list == NULL)
		error_exit(ERR_NO_ROOMS);
	if (farm->rooms.start == NULL)
		error_exit(ERR_NO_START);
	if (farm->rooms.end == NULL)
		error_exit(ERR_NO_END);
	if (farm->links == NULL)
		error_exit(ERR_NO_LINKS);
}
