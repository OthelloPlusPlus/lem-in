/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:59:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:03:31 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static void	find_ant(t_move* move, t_ant* ant);

t_move*	create_move(t_ants* ants, int id, t_room* list, char* name)
{
	t_move*	move;

	if (ants == NULL || id < 0 || list == NULL || name == NULL)
		return (NULL);
	move = ft_calloc(1, sizeof(t_move));
	if (move == NULL)
		error_exit(ERR_CALLOC);
	move->id = id;
	find_ant(move, ants->ants);
	move->room = find_room_by_name(list, name);
	return (move);
}

static void	find_ant(t_move* move, t_ant* ant)
{
	while (ant != NULL && ant->id <= move->id)
		ant = ant->next;
	move->ant = ant;
}
