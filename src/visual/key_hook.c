/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 20:37:16 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/24 20:57:56 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static void	adjust_mode(t_visual* visual, keys_t key);
static void	trigger_pause(t_visual* visual);

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_visual*	visual;

	visual = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(visual->mlx);
	if (visual->state.mode == DONE)
		return ;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
		trigger_pause(visual);
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN) && \
		keydata.action == MLX_RELEASE)
		adjust_mode(visual, keydata.key);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		visual->state.step = true;
}

static void	adjust_mode(t_visual* visual, keys_t key)
{
	if (key == MLX_KEY_DOWN && visual->state.mode > 1)
		set_mode(visual, visual->state.mode - 1);
	else if (key == MLX_KEY_UP && visual->state.mode < MODE_SIZE - 1)
		set_mode(visual, visual->state.mode + 1);
}

static void	trigger_pause(t_visual* visual)
{
	visual->state.active ^= true;
	put_info_pause(visual);
}
