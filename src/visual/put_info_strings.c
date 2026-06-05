/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 20:37:37 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/19 20:42:43 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in_visual.h"

static mlx_image_t*	put_str_beneath(mlx_t* mlx, char* str, mlx_image_t* ref);

void	put_info_strings(t_visual* visual, t_farm* farm)
{
	put_info_mode(visual);
	put_info_pause(visual);
	put_info_ants(visual, farm->ants.count);
	put_info_turns(visual);
}

void	put_info_mode(t_visual* visual)
{
	char*	mode;

	mode = NULL;
	if (visual->state.mode == DONE)
		mode = ft_strdup("[ESC]   QUIT");
	else if (visual->state.mode == AUTO)
		mode = ft_strdup("[v]     AUTO");
	else if (visual->state.mode == STEP)
		mode = ft_strdup("[^][>]  STEP");
	if (mode != NULL)
	{
		if (visual->img.mode != NULL)
			mlx_delete_image(visual->mlx, visual->img.mode);
		visual->img.mode = put_str_beneath(visual->mlx, mode, NULL);
	}
	free(mode);
}

void	put_info_pause(t_visual* visual)
{
	if (visual->img.pause != NULL)
		mlx_delete_image(visual->mlx, visual->img.pause);
	if (visual->state.mode == DONE)
		visual->img.pause = put_str_beneath(visual->mlx, "", visual->img.mode);
	else if (visual->state.active)
		visual->img.pause = put_str_beneath(visual->mlx, "[SPACE] PAUSE", visual->img.mode);
	else
		visual->img.pause = put_str_beneath(visual->mlx, "[SPACE] PAUSED", visual->img.mode);
}

void	put_info_ants(t_visual* visual, u_int32_t num)
{
	char*	str;
	char*	count;

	count = ft_utoa_ultimate(num, "0123456789");
	if (count == NULL)
		error_exit(ERR_CALLOC);
	str = ft_strjoin("Ants:   ", count);
	free(count);
	if (str == NULL)
		error_exit(ERR_CALLOC);
	if (visual->img.info_ants != NULL)
		mlx_delete_image(visual->mlx, visual->img.info_ants);
	visual->img.info_ants = put_str_beneath(visual->mlx, str, visual->img.pause);
	free(str);
}

void	put_info_turns(t_visual* visual)
{
	char*	str;
	char*	turns;

	turns = ft_utoa_ultimate(visual->turns, "0123456789");
	if (turns == NULL)
		error_exit(ERR_CALLOC);
	str = ft_strjoin("Turns:  ", turns);
	free(turns);
	if (str == NULL)
		error_exit(ERR_CALLOC);
	if (visual->img.info_turns != NULL)
		mlx_delete_image(visual->mlx, visual->img.info_turns);
	visual->img.info_turns = put_str_beneath(visual->mlx, str, visual->img.info_ants);
	free(str);
}

static mlx_image_t*	put_str_beneath(mlx_t* mlx, char* str, mlx_image_t* ref)
{
	mlx_image_t*	img;
	int				posx;
	int				posy;

	if (str == NULL)
		return (NULL);
	posx = 1;
	posy = 1;
	if (ref != NULL)
	{
		posx = ref->instances[0].x;
		posy += ref->instances[0].y + ref->height;
	}
	img = mlx_put_string(mlx, str, posx, posy);
	return (img);
}
