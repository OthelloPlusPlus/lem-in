/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:39:42 by ohengelm          #+#    #+#             */
/*   Updated: 2026/06/04 19:06:40 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

/*
printf("%s[%d]\n", __func__, __LINE__);
printf("%s["C_SET(__LINE__, 99, 99)"%d"C_RESET"]\n", __func__, __LINE__);
*/

int	main(void)
{
	t_ss		ss;

// parse from FD (STDIN)
	common_functions(&ss.farm);
	ss.moves = NULL;
	parse_remnant_visual(&ss);
	if (ss.moves == NULL)
		error_exit(ERR_NO_MOVES);
// Generate mlx visuals
	prepare_visual(&ss.visual);
	start_mlx(&ss.visual);
	add_rooms_to_visual(&ss.farm.rooms, &ss.visual);
	draw_links(&ss.farm, &ss.visual.img);
	add_ants_to_farm(&ss.farm);
	add_ants_to_moves(&ss.farm, ss.moves);
	add_ants_to_visual(&ss.farm, &ss.visual);
	set_mode(&ss.visual, AUTO);
	put_info_strings(&ss.visual, &ss.farm);
// generate and run MLX loop
	mlx_key_hook(ss.visual.mlx, key_hook, &ss.visual);
	mlx_loop_hook(ss.visual.mlx, loop_hook, &ss);
	mlx_loop(ss.visual.mlx);
// Cleanup
	delete_visuals(&ss.visual, &ss.farm.ants);
	delete_all_moves(ss.moves);
	delete_all_ants(&ss.farm.ants);
	destroy_farm(&ss.farm);
	mlx_terminate(ss.visual.mlx);
	return (0);
}
