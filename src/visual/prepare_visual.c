/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_visual.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:05:17 by ohengelm          #+#    #+#             */
/*   Updated: 2026/06/05 21:24:14 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

void	prepare_visual(t_visual* visual)
{
	visual->mlx = NULL;
	visual->state.active = false;
	visual->state.mode = DONE;
	visual->state.step = visual->state.mode == AUTO;
	visual->img.background = NULL;
	visual->img.mode = NULL;
	visual->img.pause = NULL;
	visual->img.info_turns = NULL;
	visual->turns = 0;
	visual->img.info_ants = NULL;
}
