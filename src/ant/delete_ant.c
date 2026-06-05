/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_ant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:54:08 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:44:01 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

void	delete_ant(t_ants* ants, t_ant* ant)
{
	if (ant == NULL)
		return ;
	if (ant->prev)
		ant->prev->next = ant->next;
	if (ant->next)
		ant->next->prev = ant->prev;
	if (ant->room && ant->room->ant == ant)
		ant->room->ant = NULL;
	if (ants != NULL && ants->ants == ant)
		ants->ants = ant->next;
	free(ant);
}

void	delete_all_ants(t_ants* ants)
{
	while (ants->ants != NULL)
		delete_ant(ants, ants->ants);
}
