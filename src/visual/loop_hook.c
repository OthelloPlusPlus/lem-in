/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:21:12 by ohengelm          #+#    #+#             */
/*   Updated: 2026/06/05 21:31:43 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>	// malloc, free, exit

#include "lem_in_visual.h"

static int	move_ants(t_ant* ant, t_farm* farm, t_visual* visual);
static bool	move_ant(t_ant* ant, uint32_t step_size);
static void	check_ant_for_dest(t_ant* ant, t_farm* farm);
static void	start_new_dest(t_moves** moves);

// #define STEP_SIZE	16

void	loop_hook(void* param)
{
	t_ss*	ss;

	ss = (t_ss*)param;
	if (!ss->visual.state.active)
		return ;
	if (!move_ants(ss->farm.ants.ants, &ss->farm, &ss->visual))
	{
		if (ss->moves == NULL)
		{
			set_mode(&ss->visual, DONE);
			mlx_delete_image(ss->visual.mlx, ss->farm.ants.ants->img);
			// t_ant*	ant = ss->farm.ants.ants;
			// t_ant*	next;
			// while (ant != NULL)
			// {
			// 	next = ant;
			// 	mlx_delete_image(ss->visual.mlx, ant->img);
			// 	free(ant);
			// 	ant = next;
			// }
			ft_printf("# Turns taken: %u\n", ss->visual.turns);
		}
		else if (ss->visual.state.step == true)
		{
			start_new_dest(&ss->moves);
			++ss->visual.turns;
			put_info_turns(&ss->visual);
			ss->visual.state.step = ss->visual.state.mode == AUTO;
		}
	}
}

static int	move_ants(t_ant* ant, t_farm* farm, t_visual* visual)
{
	int	moves;

	moves = 0;
	while (ant != NULL)
	{
		if (ant->room)
		{
			moves += move_ant(ant, visual->step_size);
			check_ant_for_dest(ant, farm);
		}
		ant = ant->next;
	}
	put_info_ants(visual, farm->ants.count);
	return (moves);
}

static bool	move_ant(t_ant* ant, uint32_t step_size)
{
	int		dx;
	int		dy;
	double	angle;
	double	distance;

	if (ant->x == ant->room->x && ant->y == ant->room->y)
	{
		return (false);
	}
	dx = ant->room->x - ant->x;
	dy = ant->room->y - ant->y;
	angle = atan2(dy, dx);
	distance = sqrt(dx * dx + dy * dy);
	if (distance > step_size)
		distance = step_size;
	ant->x += cos(angle) * distance;
	ant->y += sin(angle) * distance;
	center_image(ant->img, 0, ant->x, ant->y);
	return (true);
}

static void	check_ant_for_dest(t_ant* ant, t_farm* farm)
{
	if (ant->x != ant->room->x || ant->y != ant->room->y)
		return ;
	if (ant->room == farm->rooms.end)
	{
		--farm->ants.count;
		ant->img->instances[ant->inst].enabled = false;
	}
	ant->room = NULL;
}

static void	start_new_dest(t_moves** moves)
{
	t_move*	move;

	move = (*moves)->moves;
	while (move != NULL)
	{
		move->ant->room = move->room;
		move->ant->img->enabled = true;
		ft_printf("L%u-%s ", move->ant->id, move->ant->room->name);
		move = move->next;
	}
	delete_moves_from_list(moves);
	ft_printf("\n");
}
