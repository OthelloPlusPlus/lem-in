/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:01:50 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 19:02:43 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stddef.h>	// NULL

/*
printf("%s[%d]\n", __func__, __LINE__);
printf("%s["C_SET(__LINE__, 99, 99)"%d"C_RESET"]\n", __func__, __LINE__);
*/
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
// static void	print_for_debug(const time_t* now, const char* func, const int line)
// {
// 	struct tm*	t = localtime(now);
// 	ft_dprintf(2, "#%2i:%02i:%02i %s[%i]\n", t->tm_hour, t->tm_min, t->tm_sec, func, line);
// }

// time_t now = time(NULL);
// print_for_debug(&now, __func__, __LINE__);

int	main(void)
{
	t_farm		farm;
	t_paths*	paths;

	common_functions(&farm);
	paths = find_paths(&farm);
	print_farm(&farm);
	print_paths(paths->first);
	add_ants_to_farm(&farm);
	move_ants_through_farm(&farm, paths->first);
	destroy_farm(&farm);
	delete_paths(paths);
	return (0);
}
