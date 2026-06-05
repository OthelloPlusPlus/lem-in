/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:06 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/24 21:07:54 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static void	adjust_state(t_state* state, t_mode mode);

void	set_mode(t_visual* visual, t_mode mode)
{
	adjust_state(&visual->state, mode);
	put_info_mode(visual);
	if (visual->state.mode == DONE)
	{
		mlx_delete_image(visual->mlx, visual->img.pause);
		visual->img.pause = NULL;
	}
}

static void	adjust_state(t_state* state, t_mode mode)
{
	if (mode < DONE)
		return ;
	if (mode >= MODE_SIZE)
		return ;
	state->mode = mode;
	state->step = state->mode == AUTO;
	if (mode == DONE)
		state->active = false;
}
