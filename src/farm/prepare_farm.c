/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_farm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:06:45 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:06:00 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

void	prepare_farm(t_farm* farm)
{
	farm->ants.count = 0;
	farm->ants.ants = NULL;
	farm->rooms.list = NULL;
	farm->rooms.start = NULL;
	farm->rooms.end = NULL;
	farm->links = NULL;
	farm->storage = NULL;
}
