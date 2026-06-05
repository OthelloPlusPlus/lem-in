/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 19:31:33 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:19:39 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in_visual.h"

void	delete_move_list(t_move* move)
{
	t_move*	next;

	while (move != NULL)
	{
		next = move->next;
		free(move);
		move = next;
	}
}

void	delete_moves_from_list(t_moves** moves)
{
	t_moves*	rm;

	rm = *moves;
	delete_move_list(rm->moves);
	*moves = rm->next;
	free(rm);
}

void	delete_all_moves(t_moves* moves)
{
	while (moves != NULL)
		delete_moves_from_list(&moves);
}
