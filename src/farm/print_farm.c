/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:07:34 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/24 17:14:28 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	print_ant(t_ants* ants);

void	print_farm(t_farm* farm)
{
	print_ant(&farm->ants);
	print_rooms(&farm->rooms);
	print_links(farm->links);
}

static void	print_ant(t_ants* ants)
{
	ft_printf("%u\n", ants->count);
}
