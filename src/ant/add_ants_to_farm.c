/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ants_to_farm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:10:46 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 19:02:54 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

void	add_ants_to_farm(t_farm* farm)
{
	t_ant*		ant;
	u_int32_t	id;

	id = farm->ants.count;
	while (id > 0)
	{
		ant = create_ant(id, farm->rooms.start);
		if (ant == NULL)
			break ;
		ant->next = farm->ants.ants;
		if (ant->next != NULL)
			ant->next->prev = ant;
		farm->ants.ants = ant;
		--id;
	}
}
